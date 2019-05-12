//*********************************************************
//
// Mehmet Ozkan
// Operating Systems
// Project #2 PART A: Computing Fibonacci Numbers With Threads
// October 25, 2017
// Instructor: Dr. Ajay K. Katangur
//*********************************************************

//*********************************************************
//
// Includes and Defines
//
//*********************************************************

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;


void fibonacci_display();
void *fibonacci_thread(void *fiblength);

struct Struct_Fib
{
	int length;
	int *order;
};


int main(int argc, char* argv[])
 {

	cout << "\n**** Displaying Fibonacci Numbers With Threads****"<<endl;
	
	fibonacci_display();
	
	return 0;
}



//********************************************************************
//
// Displaying Fibonacci Numbers Function
//
//This function displays the Fibonacci series by using the pThreads library byusing the pThreads library.
//When user enters on the command line then number of Fibonacci numbers that the program will generate. 
//This function creates a separate thread that will generate the Fibonacci numbers
//placing the sequence in data that is shared by the threads. 
//
// Local Variables
// ---------------
// length      int	length of the fibonacci sequence
// rtrnvalue   int	return value of the pthread_create() function


void fibonacci_display() {
	
	struct Struct_Fib fib;
	pthread_t thread;
	int length, rtrnvalue;
	
	
	cout << "Enter the number of fibonacci series as an integer"<<endl;
	cout<<"->";
	
	while (!(cin >> length) || length <= 0) 
	{
		cout << "!!Please enter a positive integer value!!"<< endl;
		cout<<"->";
	}
	//Allocating free space for the array structure type
	
	fib.order = (int*)malloc(sizeof(int*)*length);
	fib.length = length;
	
	
	rtrnvalue = pthread_create(&thread, NULL, fibonacci_thread,(void*)&fib);
	
	//If successful, the pthread_create() function returns zero. Otherwise, an error number is returned to indicate the error.
	if (rtrnvalue)
	{
		printf("ERROR, return value from pthread_create() function is %d\n", rtrnvalue);
		exit(0);
	}

	pthread_join(thread, NULL);
 
	for (int i = 0; i < fib.length; i++) 
	{
	cout << "Fib[" << i << "]: "<< fib.order[i]<< endl;
	}
	
	
}
	
//********************************************************************
//
// Generating Fibonacci Numbers Function
//
// This function generates the Fibonacci series with respect to length by user.
// Local Variables
// ---------------
// length      int	length of the fibonacci sequence
// rtrnvalue   int	return value of the pthread_create() function

void *fibonacci_thread(void *arg) 
{
	//Converting void type to struct type
	struct Struct_Fib *fib = (struct Struct_Fib*)arg;

	fib->order[0] = 0;
	fib->order[1] = 1;

	for (int i = 2; i <fib->length; i++) 
	{
		fib->order[i] = fib->order[i - 1] + fib->order[i - 2];
	}

	pthread_exit(NULL);
}