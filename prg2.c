#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int msize;
int csize;
int bsize;
int *mainmem;
int address;
int value;
int tag;
int word;
int blocknum;
int fileinput[150];
int p=0;
int line;


int main(void){
  printf("Program Written By Alexander Cloutier-Nosik\n");
  printf("Program Assignment 2 Cache Memory\n");
  printf("COMP222 Fall 2018\n");
  printf("Class Meeting Time 8:00-9:15\n");
  printf("*** Starting to Read Input From File:prg2_data.txt\n\n");
  printf("______________________________________________________\n");
  int o=0;
  char *fn ="prg2_data.txt";
  FILE *pointer = fopen(fn,"r");
  if(!pointer){
    printf("Error in Opening");
    return -1;
   }
  while(!feof(pointer)){
    fscanf(pointer,"%s",&fileinput[o]);
    o++;
   }
  fclose(pointer);
  MainMenue();
  return 0;
}
struct node{
  int tag;
  int *block;
}*cache=NULL;

typedef struct node n;

MainMenue(void){//Main Menue
   int input;
   printf("Make a Selection\n");
   printf("Enter Configuration Parameters\n");
   printf("Read Cache Memory\n");
   printf("Write to Cache Memory\n");
   printf("Quit\n");
    input=fileinput[p];
   //scanf("%d",&input);
    p++;
   if(input==1){
     CheckValues();
   }
   else if(input==2){
     Read();
   }
   else if(input==3){
     Write();
   }
  else if(input==4){
    Quit();
   }
     else{
       printf("Invalid Selection Returning to Main Menue");
       MainMenue();
     }
   }
CheckValues(void){//Checks Validity of Values
  printf("Enter Main Memory Size\n");
   msize= fileinput[p];
   p++;
  //scanf("%d",&msize);
  printf("Enter Cache Size\n");
  csize=fileinput[p];
  p++;
  //scanf("%d",&csize);
  printf("Enter Block Size\n");
  bsize=fileinput[p];
  p++;
  //scanf("%d",&bsize);
  if(CheckPow(msize,bsize,csize)==1 && CheckBlk(msize,bsize)==1 && CheckMul(csize,bsize)==1){
    printf("***All Input Parameter Have Been Accepted Starting Read/Write Requests\n\n");
    printf("_______________________________________________________________________\n");
    InitializeCache(msize,csize,bsize);
    MainMenue();
  }
  else{
    MainMenue();
  }
  return 0;
}
int CheckPow(int m,int b,int ca){//Checks Values are all to Power of 2
  while(m!=1){
      if(m%2!=0){
        printf("***Error- Main Memory Size Not to Power 2\n\n");
        printf("____________________________________\n");
        return 0;
      }
     m=m/2;
  }
  while(b!=1){
    if(b%2!=0){
      printf("***Error- Block Size Not to Power 2\n\n");
      printf("________________________________\n");
      return 0;
    }
    b=b/2;
  }
  while(ca!=1){
    if(ca%2!=0){
      printf("***Error- Cache Size Not to Power 2\n\n");
      printf("_____________________________\n");
      return 0;
    }
    ca=ca/2;
  }
  return 1;
 }
int CheckBlk(int msize, int bsize){//Checks block size is smaller then Main Memory
  if(bsize<msize){
    return 1;
  }
  else{
    printf("***Error-Block Size is Larger Than Main Memory\n\n");
    printf("__________________________________________________\n");
    return 0;
  }
}
int CheckMul(int csize, int bsize){//Checks For multiple
  if(csize%bsize==0){
    return 1;
  }
  else{
    printf("***Error- Cache Size not a Multiple of Block Size\n");
    return 0;
  }
}
InitializeCache(int msize,int csize,int bsize){//Initializes Cache and Main Memory
  int i=0;
  int numLines;
 int j=0;
  mainmem=(int*)malloc(msize*sizeof(int));
  for(i=0;i<msize;i++){
    mainmem[i]= msize-1;
  }
  cache=(n*)malloc(csize*sizeof(n));
  for(j=0;j<csize;j++){
    cache[j].block = NULL;
    cache[j].tag=-1;
  }
}
Read(){//Reads from Cache
  int b=0;
  struct node cnode;
  printf("Please Enter Address to Read From\n");
  address=fileinput[p];
  p++;
  //scanf("%d",&address);
  tag=address/csize;
  line=(address%csize)/bsize;
  blocknum= address/bsize;
  word= address%bsize;
  for(b=0;b<csize-1;b++){
    if(cache[b].tag==tag){
      printf("***Cache Hit \n\n");
      printf("***Word ");
      printf("%d", word);
      printf(" of CacheLine ");
      printf("%d",line);
      printf(" with tag ");
      printf("%d",tag);
      printf(" contains the Value ");
      printf("%d",*(cache[b].block + word));
      printf("\n");
      printf("___________________________\n\n");
      MainMenue();
    }
  }
  printf("***Cache Miss \n\n");
  NewBlock();
  printf("***Word ");
  printf("%d", word);
  printf(" of CacheLine ");
  printf("%d",line);
  printf(" with tag ");
  printf("%d",tag);
  printf(" contains the Value ");
  printf("%d",*(cache[tag].block + word));
  printf("\n");
  printf("_____________________________\n\n");
  MainMenue();
}
Write(){//Writes to Cache
  int d=0;
  struct node wnode;
  printf("What Address do you want to write to\n");
  address=fileinput[p];
  p++;
  //scanf("%d",&address);
  printf("What Content to Write\n");
  value = fileinput[p];
  p++;
  //scanf("%d",&value);
  tag = address/csize;
  line =(address&csize)/bsize;
  word = address%bsize;
  for(d=0;d<csize-1;d++){
    if(cache[d].tag==tag){
      *(cache[d].block+word)=value;
      printf("***Cache Hit\n\n");
      printf("***Word ");
      printf("%d", word);
      printf(" of CacheLine ");
      printf("%d",line);
      printf(" with tag ");
      printf("%d",tag);
      printf(" contains the Value ");
      printf("%d",*(cache[d].block + word));
      printf("\n");
      printf("____________________________\n\n");
      MainMenue();
    }
  }
  printf("***Cache Miss\n\n");
      mainmem[address]=value;
      NewBlock();
      *(cache[tag].block+word)=value;
      printf("***Word ");
      printf("%d", word);
      printf(" of CacheLine ");
      printf("%d",line);
      printf(" with tag ");
      printf("%d",tag);
      printf(" contains the Value ");
      printf("%d",*(cache[tag].block + word));
      printf("\n");
      printf("______________________________\n");
       MainMenue();
}
NewBlock(){//Copies Data From Main Memory to Cache
  int g=0;
  int startline;
  startline=line+word;
  cache[tag].tag=tag;
  int *array;
 array= (int*)malloc(bsize*sizeof(int));
  for(g=0;g<bsize-1;g++){
    *(array + g)=mainmem[startline+g];
  }
  cache[tag].block=array;
  free(array);
}
Quit(){//Frees Alocated Memory and Terminates Program
  free(cache);
  free(mainmem);
  printf("*** Memory Freed- Program Terminated Normally\n");
}

