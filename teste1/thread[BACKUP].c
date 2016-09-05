#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>


long long int average;
pthread_mutex_t mtx;

void *GetAverage(int ik, int K, long long int alocNum, int *vars){
	long long int i, start, end, localSum;

	//Calculate start and end of array domain
	start = (alocNum/K)*ik;	
	end = (alocNum/K)*(ik+1);	

	//Apply values to vars
	for(i=start; i<end; i++){
		vars[i] = 1 + rand() % 1000;		
	}

	//Calculate the average value for the numbers
	localSum = 0;
	for(i=start; i<end; i++){
		localSum += vars[i];
	}

	//Sum to total;
	pthread_mutex_lock(&mtx);
	average += localSum;
	pthread_mutex_unlock(&mtx);

	//exit
	pthread_exit(NULL);
}

int main(){
	//Initialize random values
	srand(time(NULL));

	//Create vars
	int exp = 20, N = 0, K=1;
	long long int alocNum;
	int r, i;
	int *vars;

	//Initialize thread mutex
	pthread_mutex_init(&mtx, NULL);

	//Get arguments
	scanf(" %d %d", &N, &K);

	//Create threads
	pthread_t threads[K];

	//Calculate size and alocate vector of random values
	alocNum = N*(long)pow(2,exp);
	vars = (int *)malloc(alocNum * sizeof(int));

	//Run threads
	for(int i = 0; i < K; i++) {
		pthread_create(&threads[i], NULL,
		GetAverage, i, K, alocNum, vars);
	}
	//Join threads
	for(int i = 0; i < K; i++) {
		pthread_join(threads[i], NULL);
	}
	
	
	average /= alocNum;

	printf("%lli %d %lli\n", alocNum, average);

	free(vars);

	return 0;
}
