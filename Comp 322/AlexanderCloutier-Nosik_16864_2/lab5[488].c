#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

//Number of Philosophers at the Table

#define TOTAL_PHILOSOPHERS 5

//define total methods used
void *loop(void*);
void pickUpChop(void*);
void putDownChop(void*);
void thinking(void*);
void eating(void*);

//Philosopher thread array, mutex lock array, thread attribute array
pthread_t phils[TOTAL_PHILOSOPHERS];
pthread_mutex_t chopstick[TOTAL_PHILOSOPHERS];
pthread_attr_t attr[TOTAL_PHILOSOPHERS];

//Loops infinetly to show dining Philosopher Solution
void *loop(void * philosopher){
	int i;
	//loops for a maximum of 5 times
	for (i=0;i<5;i++){
		thinking(philosopher);
		pickUpChop(philosopher);
		eating(philosopher);
		putDownChop(philosopher);
	}
}
//Function that philosophers call to pick up chopstics
void pickUpChop(void* philosopher){
	//right and left chopstick set for specific philosopher
	int rchop = (int)(philosopher +1)% TOTAL_PHILOSOPHERS;
	int lchop = (int)(philosopher + TOTAL_PHILOSOPHERS)%TOTAL_PHILOSOPHERS;

	//Checks whether right or left chopstic is open
	if((int)philosopher & 1){
		//Locks right chopstick to show philosopher has picked it up
		pthread_mutex_lock(&chopstick[rchop]);
		//Locks Left chopstick to show that it has been picked up
		pthread_mutex_lock(&chopstick[lchop]);
	}
	else{
                //Locks Lefet chopstick to show its been picked up
		pthread_mutex_lock(&chopstick[lchop]);
                //locks Right Chopstic to show its been picked up
		pthread_mutex_lock(&chopstick[rchop]);
	}
}
//Function philosophers call to put down their chopsticks
void putDownChop(void* philosopher){
	//Mutex locks unlocked so that other philosophers may pick up
	pthread_mutex_unlock(&chopstick[(int)(philosopher +1) % TOTAL_PHILOSOPHERS]);
	pthread_mutex_unlock(&chopstick[(int)(philosopher + TOTAL_PHILOSOPHERS)%TOTAL_PHILOSOPHERS]);
}
//Function Philosophers call when thinking
void thinking(void* philosopher){
	//Thinking time set to random 1-3 secs
	int rest = rand() %3 +1;
	printf("Philosopher %d  thinks for %d seconds\n",philosopher+1, rest);
	sleep(rest);
}
//Function Philosophers call when eating
void eating(void* philosopher){
	//Eating time set to random 1-3 secs
	int eat = rand()%3 + 1;
	printf("Philosopher %d eats for %d seconds\n",philosopher+1,eat);
	sleep(eat);
}
//Main Method
int main(){
	int j;
	srand(time(NULL));
	//loop to initialize mutex and attribute array
	for (j=0;j<TOTAL_PHILOSOPHERS;j++){
		pthread_mutex_init(&chopstick[j],NULL);
		pthread_attr_init(&attr[j]);
	}
	//loop for creating threads for the philosophers(1 for each)
	for(j=0;j<TOTAL_PHILOSOPHERS;j++){
		pthread_create(&phils[j],&attr[j],loop,(void*)(j));

	}
	//loop for joining the philosopher threads
	for(j=0;j<TOTAL_PHILOSOPHERS;j++){
                pthread_join(phils[j],NULL);
        }
}
