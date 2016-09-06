#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(){
	//Initialize random values
	srand(time(NULL));

	//Create vars
	int exp = 20, N = 0, K=1;
	long long int alocNum;
	int r, i, *childs, ci, v;

	//Initialize shared memory
	int fd = shm_open("process", O_RDWR | O_CREAT, 0666);
	if (fd == -1) {
		perror("shm_open");
		exit(-1);
	}

	//Get arguments
	scanf(" %d %d", &N, &K);

	//Calculate size and alocate vector of random values on shared space	
	alocNum = N*(long)pow(2,exp);
	ftruncate(fd, (alocNum+2)*(sizeof(int)));
	int *ptr = (int *)mmap(0, (alocNum+2)*(sizeof(int)), PROT_READ | PROT_WRITE, MAP_SHARED,  fd, 0);
	int *available = &ptr[alocNum];
	int *average = &ptr[alocNum+1];
	*available = 0;
	*average = 0;

	//Initialize child vector
	childs = (int *)malloc(K * sizeof(int));
	
	//Generate forks
	pid_t pid;
	int isFather = 1;
	ci = 0;
	for(v=1; v<K; v++){
		pid = fork();
		if(pid < 0) {
			perror("fork");
	   		exit(-1);
		}else if(pid == 0){
			//Child. Get out
			isFather = 0;
			break;
		}else{
			//Father. Store childs pids
			childs[ci] = pid;
			ci++;
		}
	}
	//Detect if actual process is the father
	if(isFather){
		v=0;
	}//else{
		//printf("Sou o filho %d. ", v);
	//}
   	//printf("Meu PID é %d. Meu pai é %d\n", getpid(), getppid());


	//Allocate	local variables
	long long int j, start, end, localSum;
	//Calculate start and end of array domain
	start = (alocNum/K)*v;	
	end = (alocNum/K)*(v+1);	

	//Apply values to vars and calculate the average value for the numbers
	localSum = 0;
	for(j=start; j<end; j++){
		ptr[j] = 1 + rand() % 1000;			
		localSum += ptr[j];	
	}
	localSum = (long long int)(localSum/(long long int)(alocNum/K));

   	//printf("Sou %d. Meu AVERAGE é %lli\n", v, localSum);

	//Sum to total;
	while(*available == 1){
		//printf("Sou %d, esperando...\n", v);
	} //wait for average to be available
	*available = 1;//lock
	*average += localSum;
	*available = 0;//unlock
   	//printf("Sou %d e eu terminei\n", v, localSum);


	//Eliminate all process but the father
	if(!isFather){
		exit(0);
	}else{
		int status;
		for(i=0; i<K; i++)	
			waitpid(childs[i], &status, 0);		
	}

	//Print results
	printf("%d\n", *average/K);

	//Unallocate vector of random values and shared memory
	munmap(ptr, (alocNum+2)*(sizeof(int)));
	shm_unlink("process");
	free(childs);

	return 0;
}
