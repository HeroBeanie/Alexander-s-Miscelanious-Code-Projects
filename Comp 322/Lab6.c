#include <stdio.h>
#include <stdlib.h>
#define MEMSIZE 16384
#define PAGESIZE 4096
int virtualaddress;

int main(int argc,char* argv[]){
		int realaddress,virtualpage,offset;
		int exist=0;
  		virtualaddress=atoi(argv[1]);
  		printf("Enter virtual memory address to access: \n");
  		virtualpage = virtualaddress/PAGESIZE;
  		offset = virtualaddress%PAGESIZE;
  		printf("Page number: %d\n",virtualpage);
  		printf("offset: %d\n",offset);
}
