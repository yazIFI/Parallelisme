#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int global = 0;

void privateScope0(){
	int i;
	#pragma omp for
	for(i=0;i<10;i++){
		global++ ;

		//printf("nombre de thread %d\n", omp_get_num_threads());	
	}
}
void privateScope1(){
	int i;
	#pragma omp for private(global)
	for(i=0;i<10;i++){
		global++ ;

		//printf("nombre de thread %d\n", omp_get_num_threads());	
	}
}
void privateScope2(){
	int i;
	#pragma omp for private(global)
	for(i=0;i<10;i++){
		privateScope2_sub();

		//printf("nombre de thread %d\n", omp_get_num_threads());	
	}
}
void privateScope2_sub(){
	global++;
}