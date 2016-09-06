#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>



int main(int argc, char **argv){
	//Initialize random values
	srand(time(NULL));

	//Create vars
	int exp = 20, N = 0;
	long long int alocNum, average, k;
	int r;

	//Get arguments
	//scanf(" %d", &N);
	N = atoi(argv[1]);

	//Calculate size and alocate vector of random values
	alocNum = N*(long)pow(2,exp);
	int *vars = (int *)malloc(alocNum * sizeof(int));

	//Apply values to vars
	for(k=0; k<alocNum; k++){
		r = 1 + rand() % 1000;
		vars[k] = r;
	}

	//Calculate the average value for the numbers
	average = 0;
	for(k=0; k<alocNum; k++){
		average += vars[k];
	}	
	
	//Divides from number of alocNum
	average /= alocNum;

	//Print results
	printf("%lli", average);

	//Unallocate vector of random values
	free(vars);

	return 0;
}
