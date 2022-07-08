#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE 80 

char history[10][MAX_LINE]; 
int commandCount = 0;  

//Prints history with most recent on top
void PrintHistory(){
    int i;
    int j = 0;
    int historyindex = commandCount;
	//iterates though History 2D array     
	for (i = 0; i<10; i++){ 
       	printf("%d.  ", historyindex);
        while (history[i][j] != '\n' && history[i][j] != '\0'){
            printf("%c", history[i][j]);
            j++;
        }
        printf("\n");
        j = 0;
        historyindex--;
        if (historyindex ==  0)
        break;
    }
}
//Reads user Commands Exxecutes them and puts them in History
void commandInput(char input[], char *arguments[],int *isAnd){
    int characterIndex = 0;    
    int commandLength; 		
    int nextCommand;
    int i;
    //reads console input  			
    commandLength = read(STDIN_FILENO, input, MAX_LINE);
    nextCommand = -1;
    //If nothing was entered
    if (commandLength == 0){
        exit(0);
    }
    //if somehow the length was wrong
    if (commandLength < 0){
        perror("could not read command");
	    exit(-1);
    }
    //Loops though input string checking chars and placing /0 inbetween words for evecvp
    for (i = 0; i < commandLength; i++) {
        switch (input[i]){
            //If space char same as tab
	    case ' ':
	    // if tab places a /0 char for evecvp
	    case '\t' :
	    // if first char in input
            if(nextCommand != -1){
                arguments[characterIndex] = &input[nextCommand];
                characterIndex++;
            }
            input[i] = '\0';
            nextCommand = -1;
            break;
	//If and sign then places \0 
        case '&': 	
            *isAnd = 1;
            input[i] = '\0';
            break;
	//If new line is encountered places \0 for evecvp and NULL for end of command
        case '\n':
            if (nextCommand != -1){
                arguments[characterIndex] = &input[nextCommand];
                characterIndex++;
            }
            input[i] = '\0';
            arguments[characterIndex] = NULL;
            break;
	//Any other Char continue to next char
        default :
            if (nextCommand == -1)
                nextCommand = i;
	}
    }
    arguments[characterIndex] = NULL;
    //If History was the input
    if(strcmp(arguments[0],"history") == 0){
        if(commandCount>0){
        	PrintHistory();
        } 
        else{
    	    printf("\nNo Commands in history\n");
    	}
    }
	//If first ! encountered
    	else if (**arguments == '!'){
    		int check2 = arguments[0][1]- '0';
    		int check3 = arguments[0][2];
    		if(check2 > commandCount){
    		printf("\nCommand not found\n");
    		strcpy(input,"Invalid Command");
    		}
	//if something at [0][2] besides 0 it passes the history limit         
	else if (check3 != 0){
    		printf("\nCannot access That far in the past. \n");
    		strcpy(input,"Invalid Command");
    	}	
	//ASCII ! second ! has been read execute most recent command
        else if(check2==-15){
    		 strcpy(input,history[0]);
        }
		//tried to do command 0 history bound 1-9 or !! for 10
                else if(check2 == 0){
    				printf("Out of Bounds. History Bounded by 1-9 or !! for 10");
    				strcpy(input,"Invalid Command");
    			}
		//Executes specefied command in History                
		else if(check2 >= 1){
    				strcpy(input,history[commandCount-check2]);
    			}

    		}
    //Adds Input into History	       
    for (i = 9; i>0; i--){
    	strcpy(history[i], history[i-1]);
    }
    strcpy(history[0],input);
    commandCount++;
    	if(commandCount>10){
    	    commandCount=10;
    	}
}
//Main Loop for Lab
int mainLoop(void){
    char input[MAX_LINE]; 			
    char *arguments[MAX_LINE/2+1];
    int isAnd;             		
    pid_t child;
    int numloop;					
    int nextLoop = 1;
    //Loops Until CTRL^C is encountered
    while (nextLoop){
	    isAnd = 0;
	    printf("osh>");
        fflush(stdout);
        commandInput(input, arguments, &isAnd);   
	//Forks Child Process        
	child = fork();
		//If Child Was not forked correctly exits   	    
		if (child < 0) {  			
   		    printf("Fork failed.\n");
   		    exit (1);
 	    } 		
	//If Child Forked Correclty attempts exxecution if it fails and it ws not due to history
	//invalid command        
	else if (child == 0){
 		    if (execvp(arguments[0], arguments) == -1 && strcmp(input, "history") != 0){
 			printf("Invalid Command (ctrl^c to exit)\n");
 		    }
        }
	//If command executes and no And sign loops iterates and waits for process to finish	
        else{
    	    if (isAnd == 0){
    		    numloop++;
    		    wait(NULL);
    	    }

        }
    }
	//otherwise reterns 0 ending the loop
	return 0;
}
int main(void){
    //Calls Main Loop to start Program
    mainLoop();
    return 0;
}
