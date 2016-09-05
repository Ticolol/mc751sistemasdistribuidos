#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>



int main(){
	//Initialize random values
	srand(time(NULL));

	int exp = 20, N = 0;
	long long int alocNum, average, k;
	int r;

	scanf(" %d", &N);

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
	average /= alocNum;

	printf("%lli %d %lli\n", alocNum, vars[0], average);

	free(vars);

	return 0;
}
