#include <stdio.h>
#include <math.h>
#include <pthread.h>
#define N 10000000
#define NUMTHREADS 4
double gPi = 0.0;  
pthread_mutex_t gLock;

void *Area(void *pArg){
       int myNum = *((int *)pArg);
       double h = 2.0 / N;
       double localSum = 0.0, x; 

           
       for (int i = myNum; i < N; i += NUMTHREADS){
               x = -1 + (i + 0.5f) * h;
                localSum += sqrt(1.0 - x*x) * h;
           }
           pthread_mutex_lock(&gLock);
           gPi += localSum;  // add partial to global final answer
           pthread_mutex_unlock(&gLock);
           return 0;
}

int main(int argc, char **argv) {
    float start, end, s;
    start = clock();
    pthread_t tHandles[NUMTHREADS]; 
    int tNum[NUMTHREADS], i;
    pthread_mutex_init(&gLock, NULL);
    
    for ( i = 0; i < NUMTHREADS; ++i ) {
        tNum[i] = i;
        pthread_create(&tHandles[i],NULL, Area, (void*)&tNum[i]);       
        
    }
    
    for ( i = 0; i < NUMTHREADS; ++i ) {
        pthread_join(tHandles[i], NULL);
    }
    
    gPi *= 2.0;
    printf("Computed value of Pi:  %12.9f\n", gPi );
    pthread_mutex_destroy(&gLock);
    end = clock(); 
	
	printf("\nMulti threaded multiplication\n");
	s = (end-start) / CLOCKS_PER_SEC; 
	printf ("Gecen sure:(saniye) %0.5lf", s); 
	
    return 0;
}
