#include "smash.h"
#include <stdio.h>
#include <sys/time.h>

#define THREADNUM 4 

unsigned long count;

#include "example.h"

void boq(cthread *ct,int id) {
   while(1) {
//      fprintf(stderr,"T\t%d. Count is %d\n",THREAD_SELF->id,count++);
      fprintf(stderr,"%d\t%d. Count is %d\n",id,THREAD_SELF->id,count++);
      cthread_yield2();
   }
}

long calctime(struct timeval * t2, struct timeval *t1) {
   int temp = t2->tv_sec - t1->tv_sec;
   int temp2 = t2->tv_usec - t1->tv_usec;
   printf("%d seconds and %d microseconds\n",temp,temp2);
   return ((temp * 1000000) + temp2); 
}

void cthread_main() {
    int i;
    cthread * c[THREADNUM];
    struct timeval t1,t2;

    count = 0;

    for (i = 0; i < THREADNUM; i++) { 
         c[i] = cthread_init(boq,250000,1,i);
    }


    gettimeofday(&t1,NULL);
    printf("%d seconds, %d micro seconds\n",t1.tv_sec,t1.tv_usec);
    for (i = 0; i < THREADNUM; i++) 
       cthread_run(c[i]); 

    while(1) {
        fprintf(stderr,"M\t%d. Count is %d\n",kernelthread_num(),count++);
        cthread_yield2();
    }
        

    gettimeofday(&t2,NULL);
    printf("%d seconds, %d micro seconds\n",t2.tv_sec,t2.tv_usec);
  
    printf("it took %d microseconds\n", calctime(&t2,&t1));

    printf("This is the main user thread end\n");
}



