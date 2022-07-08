#include<stdio.h>
#include<stdlib.h>
#define CYLINDERS 5000
#define REQUESTS 8
int requests[REQUESTS];
int test[] = {98,183,37,122,14,124,65,67};
int head =0;

//Sort Arrays when needed 
int * sort(int *Que){
	int i,j;
	int temp;
	for(i=0;i<REQUESTS;i++){
		for(j=0;j<REQUESTS;j++){
			if(Que[i]> Que[j]){
				temp = Que[i];
				Que[i]=Que[j];
				Que[j]=temp;
			}
		}
	}
	return Que;
}

void fcfs(int *Que){
 	int b;
	int diff=0;

	diff += abs(Que[0]-head);
	//iterates Thorugh Request array adding the differences as they are requested
	for(b=1;b<REQUESTS;b++){
		diff += abs(Que[b]-Que[b-1]);
	}
	//prints values
	printf("Number of Head Changes for FCFS: %d\n",diff);

}

void sstf(int Que[REQUESTS]){
	//initialize Variables
	int done[REQUESTS];
        int a,b;
	int headval = head;
	int next;
	int dis;
	int local;
	int temp = 0;
	int headmov = 0;
	//initializes done array
        for(a = 0; a < REQUESTS; a++){
		done[a]=0;
        }
	//iterates through each request
	for(b=0;b<REQUESTS;b++){
		next = 0;
		dis = CYLINDERS;
		//searches for smallest distance and checks if request has been completed
		for(a=0;a<REQUESTS;a++){
			temp = a;
			local = abs(headval-Que[a]);
			if(done[a]==0 && local<dis){
				next = temp;
				dis =  local;
			}
		}
	//adds shortest distance
	headmov += dis;
	headval = Que[next];
	done[next] =1;
	}
	printf("SSTF Head Movement %d\n",headmov);
}

void scan(int Que[REQUESTS]){
	//variable declaration and initilization
	int i,j;
	int sortQue[REQUESTS];
	int current=0;
	int save=head;
	int diff=0;
	int headmov=0;
	int index=0;
	Que = sort(Que);
	//sets sorted array to temp array to not alter global array
	for(i=0;i<REQUESTS;i++){
		sortQue[i]=Que[i];
	}//goes to correct head position
	for(i =0;i<REQUESTS;i++){
		if(save>sortQue[i]){
			current=i;
		}
		else{
			headmov += abs(save-sortQue[current]);
			break;
		}
	}//scans to lesser values
	for(i=current;i>0;i--){
		headmov += abs(sortQue[i]-sortQue[i-1]);
	}
	//adds value subtracted from 0 to add to next request
	headmov += abs(sortQue[0]);
	index = current+1;
	headmov+=abs(sortQue[index]);
	//scans to larger values
	for(i = index; i<REQUESTS;i++){
		headmov += abs(sortQue[i]-sortQue[i+1]);
	}
	printf("SCAN Head Movement : %d\n",headmov);

}

void cscan(int Que[REQUESTS]){
	int i,j;
	int current=0;
	int sortQue[REQUESTS];
	int save=head;
	int max= REQUESTS-1;
	int headmov=0;
	int index=0;
	int end=0;
	Que = sort(Que);
	for(i=0;i<REQUESTS;i++){
		sortQue[i]=Que[i];
	}
	//goes to correct head position
	for(i=0;i<REQUESTS;i++){
		if(save> sortQue[i]){
			current=i;
		}
		else{
			headmov+= abs(save-sortQue[current+1]);
			break;
		}
	}
	//scans to larger values
	for(i = current+1;i<REQUESTS;i++){
		headmov += abs(sortQue[i]-sortQue[i+1]);
		end = i+1;
	}
	//resets to begining
	headmov+= abs(max-sortQue[end])+ max + sortQue[0];
	//adds values from begining until last request
	for(i=0;i<current;i++){
		headmov+= abs(sortQue[i]-sortQue[i+1]);
	}
	printf("CSCAN Head Movement: %d\n",headmov);

}

void look(int Que[REQUESTS]){
	int i,j;
	int sortQue[REQUESTS];
	int current=0;
	int save=head;
	int headmov=0;
	int end=0;
	Que = sort(Que);
	//sorts array and places in temp array
	for(i=0;i<REQUESTS;i++){
		sortQue[i]=Que[i];
	}
	//goes to correct head position
	for(i=0;i<REQUESTS;i++){
		if(save > sortQue[i]){
			current = i;
		}
		else{
			headmov+=abs(save - sortQue[current+1]);
			break;
		}
	}
	//scans to the last request
	for(i=current+1;i<REQUESTS;i++){
		headmov+= abs(sortQue[i]-sortQue[i+1]);
		end = i+1;
	}
	//adds last request
	headmov += abs(sortQue[end]=sortQue[current]);
	//scans to begining
	for(i=current;i>0;i--){
		headmov+=(sortQue[i]-sortQue[i-1]);
	}
	printf("LOOK Head Movement: %d\n",headmov);
}

void clook(int Que[REQUESTS]){
	int i,j;
        int current=0;
        int save=head;
        int headmov=0;
        int end=0;
        int sortQue[REQUESTS];
	Que = sort(Que);
	//sorts and copies to temp array
	for(i=0;i<REQUESTS;i++){
		sortQue[i]=Que[i];
	}
	//goes to correct potition 
        for(i=0;i<REQUESTS;i++){
                if(save > sortQue[i]){
                        current = i;
                }
                else{
                        headmov+=abs(save - sortQue[current+1]);
                        break;
                }
        }
	//scans to larger values
        for(i=current+1;i<REQUESTS;i++){
                headmov+= abs(sortQue[i]-sortQue[i+1]);
                end = i+1;
        }
	//resets to begining
        headmov += abs(sortQue[end]-sortQue[0]);
        //finsihes adding last requests
	for(i=0;i>current;i++){
                headmov+=(sortQue[i]-sortQue[i+1]);
        }
        printf("CLOOK Head Movement: %d\n",headmov);


}

void main(int argc, char *argv[]){
	int i;
	head = atoi(argv[1]);
	if(head>4999){
		printf("Plesae enter Valid Selection");

	}
	else{
		if(argc !=2){
			printf("Please Enter Valid selection");
			exit(-1);
		}
	//makes random array  of 1000 nums with values up to 5000
		srand(time(0));
		for(i=0; i<REQUESTS;i++){
			requests[i]= rand()%5000;
		}

	fcfs(requests);
	sstf(requests);
	scan(requests);
	cscan(requests);
	look(requests);
	clook(requests);
	}

}
