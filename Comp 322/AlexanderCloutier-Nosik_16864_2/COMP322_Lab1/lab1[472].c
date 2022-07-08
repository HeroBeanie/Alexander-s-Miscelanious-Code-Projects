#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//Creates a new Data type for a Node in the Double Linked List
struct Node{
struct Node *next;
struct Node *prev;
char origc;
char shifted;
};

//Creates type called list to make a Double Linked List
struct List{
struct Node *root;
struct Node *last;
};

struct Node *NewNode(char val){
	struct Node *newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->origc = val;
	return newNode;
	}

struct List InitList(char string[],int size){
	//Creates an instance of a double linked list and sets each char in a string to a new node and places it in the list
	int i;
	struct Node *temp;
	struct List list;
	list.root = NewNode(string[0]);
	list.last=list.root;
	list.root->prev = NULL;
	temp = list.root;
	for(i=1;i<size;i++){
		temp->next = NewNode(string[i]);
		temp->next->prev=temp;
		temp= temp->next;
		list.last=temp;
		list.last->next=NULL;

	}
	return list;
}
struct List Shift(struct List list, int shift,int size){
	//Shifts the String
	int j;
	struct Node *temp;
	temp = list.root;
	int tempshift;
	for(j=0;j<size;j++){
		//Checks if non alpha char is in string
		if(isalpha(temp->origc)){
			//If lower case shifts beyond z resets it to a
		 	if(shift>0 && (temp->origc + shift)>122){
				tempshift = shift - (122- temp->origc); 
				temp->shifted = 'a' + tempshift-1;
				temp= temp->next;
			}
			//Checks if Capitals shift beyond Z then resets to A
			else if(((temp->origc + shift > 90)&&temp->origc<97) && shift>0){
				tempshift= shift - (90 - temp->origc);
				temp->shifted = 'A'+tempshift-1;
				temp= temp->next;
			}
			//Checks if lower case shifts before a then resets to z
			else if(((temp->origc + shift< 97)&& temp->origc>65)&&shift<0){
				tempshift= shift + (temp->origc-97);
				temp->shifted= 'z' + tempshift;
				temp= temp->next;
			}
			//Checks if Capital case shifts before A then resets to Z
			else if((temp->origc+shift<65)&&shift<0){
				tempshift= shift + (temp->origc - 65);
				temp->shifted = 'Z'+ tempshift;
				temp = temp-> next;
			}
			else{
				temp->shifted = temp->origc + shift;
				temp= temp->next;
			}
		}
		else{
			temp->shifted= temp->origc;
			temp=temp->next;
		}	
	}
	return list;
}
void PrintList(struct List list,int size){
	struct Node *temp;
	int k;
	//Prints Original String
	printf("Original String\n");
	temp = list.root;
	for(k=0;k<size;k++){
		printf("%c",temp->origc);
		temp = temp->next;
	}
	printf("\nShifted String\n");
	//Prints Shifted String
	temp = list.root;
        for(k=0;k<size;k++){
                printf("%c",temp->shifted);
                temp = temp->next;
        }
	//Prints Shifted Backwards
	printf("\nShifted and Reversed String\n");
	temp = list.last;
        for(k=0;k<size;k++){
                printf("%c",temp->shifted);
                temp = temp->prev;
        }
	printf("\n");
}
int isNumber(char string[], int size){
	int j;
	for(j=0;j<size;j++){
		if(isdigit(string[j])){	
		return 0;
		}
	}
return 1;

}

int mainmenue(){
int input;
char string[256];
struct List list;
int sizeofstring;
//Asks User For Essental Information
printf("Please Enter String to be Shifted:\n");
scanf("%[^\n]s",string);
sizeofstring = strlen(string);
if(isNumber(string,sizeofstring)==0){
	printf("Error Invalid String No Numbers\n");
	return 0;
}
printf("Please enter how much you want to shift:\n");
scanf(" %d", &input);
if((input>0 && input<=15)||(input<=-5&&input>=-10)){
	list = InitList(string,sizeofstring);
        Shift(list,input,sizeofstring);
        PrintList(list,sizeofstring);
	}
else{
	printf("Error Enter Correct Bounds\n");
        return 0;
	}
return 0;
}

int main(){
mainmenue();
return 0;
}
