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

double avgVar; //global variables for storing the results
int minVar;
int maxVar;
int num;

int main(int argc, char ** argv)
{
	pthread_t threads[3]; //array of thread IDs
	pthread_attr_t attrs[3]; //array of thread attribute structs
	int i, set[argc - 1]; //array for storing user input 
	num = argc - 1; 
	if(argc <= 1){  
		printf("Usage: stats num1 ... numn\n");
		return 1;
	}
	for(i = 1; i < argc; ++i){ //get user input and put it into an array
		int nextInt = atoi(argv[i]);
		if(nextInt == 0){
			printf("Usage: stats num1 ... numn\n");
			return 1;	
		}
		set[i - 1] = nextInt;
	} 
	for(i = 0; i < 3; ++i){ //initialize thread attribute structs
		if(pthread_attr_init(&attrs[i]) != 0){
			perror("Error creating thread attributes");
			return 1;
		}
	}
	if(pthread_create(&threads[0], &attrs[0], average, set) != 0){ //create thread to average numbers
		perror("Error creating thread");
		return 1;
	}
	if(pthread_create(&threads[1], &attrs[1], min, set) != 0){ //create thread to find min
		perror("Error creating thread");
		return 1;		
	}
	if(pthread_create(&threads[2], &attrs[2], max, set) != 0){ //create thread to find max
		perror("Error creating thread");
		return 1;
	}
	for(i = 0; i < 3; ++i){ //wait until all threads are finished executing
		if(pthread_join(threads[i], NULL) != 0){
			perror("Error joining thread");
			return 1;
		}
	}
	printf("The average of these numbers is: %.2f\nThe minimum is: %d\nThe maximum is: %d\n", avgVar, minVar, maxVar);
	return 0;
}

void * average(void * set){
	int i, total = 0, *temp;
	temp = (int *) set;
	for(i = 0; i < num; ++i)
		total += temp[i];
	avgVar = (double) total / num;
}

void * min(void * set){
	int i, minTemp, *temp;
	temp = (int *) set;
	minTemp = *temp;
	for(i = 0; i < num; ++i){
		if(temp[i] < minTemp)
			minTemp = temp[i];
	}
	minVar = minTemp;
}

void * max(void * set){
	int i, maxTemp, *temp;
	temp = (int *) set;
	maxTemp = *temp;
	for(i = 0; i < num; ++i){
		if(temp[i] > maxTemp)
			maxTemp = temp[i];
	}
	maxVar = maxTemp;
}













