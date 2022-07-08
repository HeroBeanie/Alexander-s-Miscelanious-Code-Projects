#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

//Global Array To be Sorted
int unsorted[]={62, 45, 60, 85, 37, 5, 30, 4, 77, 16, 72, 1, 22, 41, 18, 98, 73, 80, 9, 39};
//Defines Max constant to have all sizes of Array 
#define MAX ( sizeof(unsorted)/sizeof(unsorted[0]))
int sorted[MAX];

//Struct used to pass parameters to Threads
typedef struct{
//start index
int start;
//end index
int end;
}parameters;

//Bubble Sort Function uses void pointers for threads to pass indexes
void* sort(void* cool){
	int j,k,temp;
	parameters* local= (parameters *)cool;
	//loop to iterate though array so each swap loop can be performed
	for(j=local->start;j<=local->end-1;j++){
		//Swapping loop for each itteration swaps values if needed
		for(k=local->start;k<=local->end-1;k++){
			if(unsorted[k]>unsorted[1+k]){
				temp = unsorted[k+1];
				unsorted[k+1]=unsorted[k];
				unsorted[k]=temp;
			}
		}
	}
	//Terminated Thread Execution
	pthread_exit(0);
}
//Merges the two sorted halfs Unsorted and places values in Sorted
void* merge(void* s){
	int begining = 0;
	int half =(MAX/2);
	int halfpointer = half;
	int m;
	for(m=0;m<=MAX-1;m++){
		//If begining anf half dont overlap
		if(begining<half && halfpointer<MAX){
			//Checks if value at begining is less than value of halfpointer places in Sorted
			if(unsorted[begining]<unsorted[halfpointer]){
				sorted[m]= unsorted[begining];
				begining++;
			}
			//Does Vice Versa of Above if
			else{
				sorted[m] = unsorted[halfpointer];
				halfpointer++;
			}
		}
		//If Begining passes half the array, the rest of sorted is the rest of second halfp
		else if(begining>=half && halfpointer<MAX){
			sorted[m] = unsorted[halfpointer];
			halfpointer++;
		}
		//Does the Vice Versa of above else if
		else if(halfpointer>=MAX && begining<half){
			sorted[m] = unsorted[begining];
			begining++;
		}
	}
	//terminates 3rd thread  after execution
	pthread_exit(0);
}
//Prints Arrays
void toString(int arr[]){
	int l;
	int arrsize = MAX;
	for(l=0;l<=arrsize-1;l++){
		printf("%d ",arr[l]);
	}
	printf("\n");
}
void main(){
	//Prints Array before Sorting
	printf("Unsorted Array: \n");
	toString(unsorted);
	// All Threads needed
	pthread_t arr1;
	pthread_t arr2;
	pthread_t arr3;
	//passes parameters to first thread
	parameters * arrs =(parameters*)malloc(sizeof(parameters));
        arrs->start = 0;
        arrs->end = (MAX/2)-1;
	//creates first thread with passed parameters
	pthread_create(&arr1,NULL,sort,arrs);
	//waits until thread is done
	pthread_join(arr1,NULL);
	//Prints results of first threads
	printf("Unsorted Array After 1st Thread: \n");
	toString(unsorted);
	//Passes Parameters to second Thread
	parameters * arrs2 = (parameters*)malloc(sizeof(parameters));
	arrs2->start = (MAX/2);
	arrs2->end = MAX-1;
	//Creates Thread with passed Parameters
	pthread_create(&arr2,NULL,sort,arrs2);
	//Waits until Thread finishes Execution
	pthread_join(arr2,NULL);
	//Prints results from 2nd Thread
	printf("Unsorted Array After 2nd Thread: \n");
	toString(unsorted);
	//Creates Third Thread that merges results from first two threads
	pthread_create(&arr3,NULL,merge,NULL);
	//Waits until third Thread is finished
	pthread_join(arr3,NULL);
	//Prints Final Sorted Array
	printf("Sorted Array: \n");
	toString(sorted);
}
