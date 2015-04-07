#include <stdio.h>
#include "exo1.c"
#include "exo2.c"
#include "exo3.c"
struct timeval t1,t2;

int main(int argc, char *argv[]){
	int i;
	FILE *fp;
	fp = fopen("mesure.txt", "w");
	size = atoi(argv[1]);
	float somme = 0.0;
	int *tab ;
	tab = malloc(sizeof(int)*atoi(argv[1]));
	float * sommeTab = malloc(sizeof(float)*200);
	//print(tab,atoi(argv[1]));
	init(tab,atoi(argv[1]));
	/*if (fp == NULL) {
  		fprintf(stderr, "Can't open input file in.list!\n");
		exit(1);
	}
	else{
		for(i=0;i< 10;i++){
			
			gettimeofday(&t1,NULL);
			paralleRegionForOutside();
			gettimeofday(&t2,NULL);
			float diffTemps = (float) ((t2.tv_usec + (t2.tv_sec*1000000)) - (t1.tv_usec+(t2.tv_sec*1000000))) ;
			somme += diffTemps;
			//fprintf(fp, "%d : %f\n", i, diffTemps);
		}
	}
	fprintf(fp,"inside 4 thread: %f\n", somme/10.0);

	privateScope2();
	printf("global : %d\n", global);
	*/
	parallelRegionForCall1();
	printf("iterateur : %d", iterateur);
	return 0;
}