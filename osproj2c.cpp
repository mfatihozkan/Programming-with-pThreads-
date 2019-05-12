//*********************************************************
//
// Mehmet Ozkan
// Operating Systems
// Project #2 PART C: Efficiency of threads
// October 25, 2017
// Instructor: Dr. Ajay K. Katangur
//*********************************************************

//*********************************************************
//
// Includes and Defines
//
//*********************************************************



#include <pthread.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sys/time.h>
using namespace std;

void Efficiency_of_Threads(int argc, char* argv[]);
void *Minimum(void* arg);
void *Maximum(void* arg);
void *Average(void* arg);
 


struct Struct_Efficiency 
{
	double avg_str;
	int min_str, max_str, size_str;
	int *values;
	
};

int main(int argc, char* argv[])
 {
// Displaying Efficiency of Threads Function
	Efficiency_of_Threads(argc, argv);
	
	return 0;
}


//********************************************************************
//
// Displaying Efficiency of Threads Function
//
// This function displays the efficiency of threads.It opens the file and generate 50000 random numbers 
// between -200 and 200 and saves them into file, calculates min,max and avg values by creating three threads and without threads
// and computes execution times of threads and without threads parts to display efficiency of threads.
// 
// Local Variables
// ----------------
// avg				double	average of the generated numbers
// time_thr 		double  time of execution for threads
// time_woutthr		double	time of execution for without threads
// avgwothr			double	average of numbers in without threads part
// number			int		random numbers for storing in vector structure	
// minwothr			int		minumum number of generated random numbers in withouts threads part
// maxwothr			int		maximum number of generated random numbers in without threads part
// numpointer		int		pointer of min,max and avg numbers 
// count			int		counter of numbers in file
// beginthr			struct	timeval of starting time in threads part
// begin			struct	timeval of starting time in without threads part
// endthr			struct	timeval of ending time in threads part
// end				struct	timeval of ending time in without threads part
//
// Value Parameters
// ---------------
// argc		int		argument counter 
// argv[]	char*	pointer of argument value array


void Efficiency_of_Threads(int argc, char* argv[])
{

	vector<int> numbers;
	const int NUM_THREADS = 3;
	double time_thr, time_woutthr;
	double avgwothr;
	int number, minwothr, maxwothr;
	int *numpointer;
	int count = 0;
	pthread_t threads[NUM_THREADS];

	// Decleration of timeval variables
	struct timeval beginthr,endthr,end,begin;
	
	// Decleration of input file
	ifstream inputfile;
	
	// Decleration of output file
	ofstream outputfile;
	
	// Opening the file 
	outputfile.open("test.txt");
	srand(time(NULL));
	
	//Creating 50000 random numbers between -200 and 200
	for (int i = 0; i < 50000; ++i) 
	{
    float randomnum = rand()% 401 + (-200); 
    outputfile << randomnum <<endl;
    }
	outputfile.close();

	// Open the file from command line argument
	
	inputfile.open(argv[1], fstream::in);
	
	if (!(inputfile.is_open()))
	{
		cout << "!!ERROR, file could not be opened!!"<<endl;
		exit(EXIT_FAILURE);
	}

	
	
	while (inputfile>> number)
	{
		numbers.push_back(number);
		count++;
	}

	// Allocate memory to the argument structure
	Struct_Efficiency args;
	args.values = (int*)malloc(sizeof(int*) *count);
	args.size_str = count;
	
	
	for (int i = 0; i < count; i++) 
	{
	args.values[i] = numbers.at(i);
	}

	//Starting Timer
	gettimeofday(&beginthr, NULL);
	
	//Creating Threads
	pthread_create(&threads[0], NULL, Minimum, (void*)&args);
	pthread_create(&threads[1], NULL, Maximum, (void*)&args);
	pthread_create(&threads[2], NULL, Average, (void*)&args);
	
	//Join Threads
	for (int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_join(threads[i], NULL);
	}
	
	//Stop Timer
	gettimeofday(&endthr, NULL);
	
	//Calculation of execution time
	time_thr = (double) ((endthr.tv_sec * 1000000 + endthr.tv_usec) - (beginthr.tv_sec * 1000000 + beginthr.tv_usec)) / 1000000.0;
	
	//Displaying with threads results
	cout << "\nWith Threads:\n";
	cout << "---------------\n";
	cout << "The minimum is: " << args.min_str << endl;
	cout << "The maximum is: " << args.max_str << endl;
	cout << "The average is: " << args.avg_str << endl;
	cout << "Time taken is: " << time_thr  << " seconds\n";
	cout << "---------------\n";

	// Without Threads
	

	// Starting Timer
	gettimeofday(&begin, NULL);
	
	// Calculation of Minimum Values of the Numbers
	numpointer = min_element(args.values, (args.values + args.size_str));
	minwothr = *numpointer;

	// Calculation of Maximum Values of the Numbers
	numpointer = max_element(args.values, (args.values + args.size_str));
	maxwothr = *numpointer;

	// Calculation of Average Values of the Numbers
	avgwothr = 0;
	
	for (int i = 0; i < args.size_str; i++)
	{
		avgwothr += numbers[i];
	}

	avgwothr /= numbers.size();

	// Stop Timer
	gettimeofday(&end, NULL);
	
	//Calculation of execution time
	time_woutthr = (double) ((end.tv_sec * 1000000 + end.tv_usec) - (begin.tv_sec * 1000000 + begin.tv_usec)) / 1000000.0;
	
	//Displaying without threads results
	
	cout << "\nWithout Threads:\n";
	cout << "---------------\n";
	cout << "The minimum is: " << minwothr << endl;
	cout << "The maximum is: " << maxwothr << endl;
	cout << "The average is: " << avgwothr << endl;
	cout << "Time taken is: " << time_woutthr << " seconds\n";
	cout << "---------------\n";
	
	if(time_woutthr < time_thr)
	{
		cout<<"The solution with Without Threads is better"<<endl;
	}
	else
		cout<<"The solution with With Threads is better"<<endl;
	
}
//********************************************************************
//
// Minimum Pointer function 
//
// This function calculates the minimum number of generated numbers
// 
// Value Parameters
// ----------------
// arg		void	pointer of the arg

void *Minimum(void* arg)
{

	// Converting void* to Struct_Efficiency* as a struct type
	Struct_Efficiency *args = (Struct_Efficiency*)arg;

	// Calculation of Minimum
	int *numpointer = min_element(args->values,(args->values + args->size_str));
	args->min_str = *numpointer;

	pthread_exit(NULL);
}
//********************************************************************
//
// Maximum Pointer function 
//
// This function calculates the maximum number of generated numbers
// 
// Value Parameters
// ----------------
// arg		void	pointer of the arg

void *Maximum(void* arg)
{

	// Convert void* to Struct_Efficiency* as a struct type
	Struct_Efficiency *args = (Struct_Efficiency*)arg;

	// Calculation of Maximum
	int *numpointer = max_element(args->values,(args->values + args->size_str));
	args->max_str = *numpointer;

	pthread_exit(NULL);
}

//********************************************************************
//
// Average Pointer function 
//
// This function calculates the average of generated numbers
// 
// Local Variables
// ----------------
// avg		double	average of the generated numbers
// Value Parameters
// ----------------
// arg		void	pointer of the arg

void *Average(void* arg)
{	
	double avg;

	// Convert void* to Struct_Efficiency*
	Struct_Efficiency *args = (Struct_Efficiency*)arg;

	// Calculation of Average
	for (int i = 0; i < args->size_str; i++) 
	{
	 avg += args->values[i];
	}

	avg /= args->size_str;

	args->avg_str = avg;

	pthread_exit(NULL);
}
