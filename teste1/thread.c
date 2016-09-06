#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>


int average;
pthread_mutex_t mtx;

typedef struct {
	int ik; 
	int K; 
	long long int alocNum;
	int *vars;
}ThreadInfo;

void *GetAverage(void *info){
	long long int i, start, end, localSum;
	ThreadInfo *ti = (ThreadInfo *)info;
//	printf("Started thread %d\n", );

	//Calculate start and end of array domain
	start = (ti->alocNum/ti->K)*ti->ik;	
	end = (ti->alocNum/ti->K)*(ti->ik+1);	

	//Apply values to vars
	for(i=start; i<end; i++){
		ti->vars[i] = 1 + rand() % 1000;		
	}

	//Calculate the average value for the numbers
	localSum = 0;
	for(i=start; i<end; i++){
		localSum += ti->vars[i];
	}

	//Sum to total;
	localSum /= (long long int)(ti->alocNum/ti->K);
	pthread_mutex_lock(&mtx);
	average += localSum;
	pthread_mutex_unlock(&mtx);

	//exit
	pthread_exit(NULL);
}

int main(int argc, char **argv){
	//Initialize random values
	srand(time(NULL));

	//Create vars
	int exp = 20, N = 0, K=1;
	long long int alocNum;
	int r, i;
	int *vars;
	ThreadInfo ti;

	//Initialize thread mutex
	pthread_mutex_init(&mtx, NULL);

	//Get arguments
	//scanf(" %d %d", &N, &K);
	N = atoi(argv[1]);
	K = atoi(argv[2]);

	//Create threads
	pthread_t threads[K];

	//Calculate size and alocate vector of random values
	alocNum = N*(long)pow(2,exp);
	vars = (int *)malloc(alocNum * sizeof(int));

	//Run threads
	ti.vars = vars;
	ti.K = K;
	ti.alocNum = alocNum;
	for(int i = 0; i < K; i++) {
		ti.ik = i;
		//printf("Generate %dth thread\n", i);
		pthread_create(&threads[i], NULL,
		GetAverage, (void *)&ti);
	}

	//Join threads
	for(int i = 0; i < K; i++) {
		pthread_join(threads[i], NULL);
	}
	
	//Divides from number of alocNum
	average /= K;

	//Print results
	printf("%lli", average);

	//Unallocate vector of random values
	free(vars);

	return 0;
}
