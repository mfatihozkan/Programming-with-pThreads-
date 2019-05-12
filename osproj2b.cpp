//*********************************************************
//
// Mehmet Ozkan
// Operating Systems
// Project #2 PART B: Printing Words With sched_yield()
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


struct Struct_Word 
{
	int count;
	char** pointers;
}; 



void PrintWords(int argc, char* argv[]);
void *vows(void *val);
void *cons(void *val);
bool ifVowel(char ch);

//Initializing wordcounter to 1 for reading words by user after ./osproj2b command 
int wordcounter = 1;




int main(int argc, char* argv[])
 {

// Displaying Printing Words Function 
	PrintWords(argc, argv);
	
	return 0;
}

//********************************************************************
//
// 	Printing Words Function 
//
// This function creates two threads to print outputs of the vowel and consonant functions
//
// Value Parameters
// ---------------
// argc		int		argument counter 
// argv[]	char*	pointer of argument value array
//
// Local Variables
// ---------------
// NUM_THREADS		int		number of threads
// returnvalue		int		return value of pthread_create functions

void PrintWords(int argc, char* argv[]) 
{
	const int NUM_THREADS = 2;
	pthread_t threads[NUM_THREADS];
	int returnvalue;
	
	
	//Initializing struct of words for passing into pthread_create function
	
	Struct_Word words;
	words.count = argc;
	words.pointers = argv;

	
	// Creating a new thread for cons function pointer
	returnvalue= pthread_create(&threads[0], NULL, cons, (void*)&words);
	
	if (returnvalue)
	{
		printf("!!ERROR!!Return value from pthread_create() function is%d\n", returnvalue);
		exit(0);
	}

	// Creating a new thread for vows function pointer
	returnvalue = pthread_create(&threads[1], NULL, vows, (void*)&words);
	
	if (returnvalue)
	{
		printf("!!ERROR!!Return value from pthread_create() function is %d\n", returnvalue);
		exit(0);
	}
	
	// Creating pthread_join function for each thread to wait until thread returns
	
	for (int i = 0; i < NUM_THREADS; i++) 
	{
		pthread_join(threads[i], NULL);
	}
}

//********************************************************************
//
// 	Vowel pointer function 
//
// This function checks each words' from the command line initial character is vowel.
// If the initial character is not vowel, use sched_yield() function for new thread gets to run.
//
// Value Parameters
// ---------------
// initialchr	void	pointer of the initial character of the word

void *vows(void *initialchr)
 {
	 
	//Converting void type to struct type 
	Struct_Word *wordsPtr = (Struct_Word*)initialchr;
	Struct_Word words = *wordsPtr;

	for (wordcounter; wordcounter < words.count;)
	{
		if (ifVowel(words.pointers[wordcounter][0])) 
		{
			cout << "vows: " << words.pointers[wordcounter] << endl;
			wordcounter++;
		}
		else 
		{
		//The thread is moved to the end of the queue for its static priority and a
		//new thread gets to run.
			sched_yield();
		}
	}
	pthread_exit(NULL);
}

//********************************************************************
//
// Consonant pointer function 
//
// This function checks each words' from the command line initial character is consonant.
// If the initial character is not consonant, use sched_yield() function for new thread gets to run.
//
// Value Parameters
// ---------------
// initialchr	void	pointer of the initial character of the word

void *cons(void *initialchr) 
{
	//Converting void type to struct type 
	Struct_Word *wordsPtr = (Struct_Word*)initialchr;
	Struct_Word words = *wordsPtr;

	for (wordcounter; wordcounter < words.count;)
	{
		if (!ifVowel(words.pointers[wordcounter][0])) 
		{
			cout << "cons: " << words.pointers[wordcounter] << endl;
			wordcounter++;
		}
		else
		{
		//The thread is moved to the end of the queue for its static priority and a
		//new thread gets to run.
			sched_yield();
		}
	}

	pthread_exit(NULL);
}

//********************************************************************
//
// Boolean Vowel function 
//
// This function checks whether or not first character of the word is vowel
// If the first character of the word is vowel, it returns true otherwise false.
//
// Return Value
// ------------
// bool                         True/False if first character of the word is vowel
//
// Value Parameters
// ---------------
// ch		char	first character of the word

bool ifVowel(char ch)
 {
	if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'|| ch == 'A'|| ch == 'E'|| ch == 'I'|| ch == 'O'|| ch == 'U' ) 
	{
		return true;
	}
	else
	{
		return false;
	}
}

