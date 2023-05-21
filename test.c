#include<pthread.h>
#include<stdio.h>
#include <unistd.h>


void    *rt()
{
    int i = 0;
    while(i < 50)
    {
        printf("routinr : %d\n", i++);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t t1;

    int  i= -1;
    
    pthread_create(&t1, NULL, &rt, NULL);
    pthread_detach(t1);
    while(++i < 10)
    {
        // usleep(5000);
        printf("main :  %d\n", i);
    }
}