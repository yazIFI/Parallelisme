#include <stdio.h>
#include <stdlib.h>

int iterateur = 0;
void parallelRegionForCall1(){
	forCall1();
}

void parallelRegionForCall1(){
	#pragma omp parallel{
		forCall1();
	}
}

void forCall1(){
	int i;
	for(i=0;i<10;i++){
		printf("nombre de thread %d\n", omp_get_num_threads());
		iterateur++;
	}
}

void forCall2(){
	int i;
	#pragma omp parallel for
	for(i=0;i<20;i++){
		printf("nombre de thread %d\n", omp_get_num_threads());
		
	}
}

