/*
This program takes a series of integers from the command line, then calculates
the average, minimum and maximum of the numbers, using 3 worker threads. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void * average(void * set);
void * min(void * set);
void * max(void * set);

double avgVar; //global variables for storing the results
int minVar;
int maxVar;
int num;

int main(int argc, char ** argv)
{
	return 0;
}

void * average(void * set){

}

void * min(void * set){

}

void * max(void * set){

}












