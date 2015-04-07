#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int size;
int * tab ;
void parallelRegion(){
int i=0;
	
	tab = malloc(sizeof(int)*size);
	omp_set_num_threads(4);
	
	printf("nombre de thread %d\n", omp_get_num_threads());
		
}

paralleRegionForOutside(){
	int i=0;
	
	tab = malloc(sizeof(int)*size);
	omp_set_num_threads(4);
	#pragma omp parallel
	{

	
	for(i=0;i<size;i++){
		tab[i]*=tab[i]; 

		printf("nombre de thread %d\n", omp_get_num_threads());
		
	}
	}
}

void parallelRegionForInsideWithPragma(){
	int i=0;
	
	tab = malloc(sizeof(int)*size);
	
	omp_set_num_threads(4);
	#pragma omp parallel
	{
	#pragma omp for
	for(i=0;i<size;i++){
		tab[i]*=tab[i]; 

		printf("nombre de thread %d\n", omp_get_num_threads());
		
	}
	}
}


void init(int *tab,int size){
	int i=0;
	//tab = malloc(sizeof(int)*size);
	//#pragma omp parallel for
	for(i=0;i<size;i++){
		tab[i]=rand()%(10);
		
    }
   	//printf("nombre de thread %d\n", omp_get_num_threads());
    //free(tab);
	
}
