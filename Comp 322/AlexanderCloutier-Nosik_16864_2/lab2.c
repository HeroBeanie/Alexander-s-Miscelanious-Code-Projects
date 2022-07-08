#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
int main (){
pid_t child;
child = fork();
char arr[30];

if (child == 0) {
        exit(0);
        }

else {

        sleep(10);
        system("ps -l");
        printf("Time spent as Zombie 10 sec\n");
        sprintf(arr,"kill -9 %d", getpid());
        printf("Now terminating %d\n", getpid());
        system(arr);
        }

return 0;
}
