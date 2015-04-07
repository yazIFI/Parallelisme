#include "MOULAYEELY_Bezeid_Code.c"


int main(int argc, char **argv) {
	
	generateArray(&source,argv[1]);
	//printArray(&source,"Q");
	// struct tablo * temp =  malloc(sizeof(struct tablo));
	// temp->tab = malloc(source.size*2*sizeof(int));
	// temp->size = source.size*2;
	// copieTableau(&source,temp);
	// gettimeofday(&t1,NULL);
	// montee(&source,temp,'m');
	// gettimeofday(&t2,NULL);
	// printf("___________________________________________________________");
	// float res = (float)(t2.tv_usec - t1.tv_usec);
	// printf ("%f\n",res);
	// printf("___________________________________________________________");
	


	struct tablo * a = malloc(sizeof(struct tablo));
	struct tablo * PSUM = malloc(sizeof(struct tablo));
	struct tablo * SSUM = malloc(sizeof(struct tablo));
	struct tablo * PMAX = malloc(sizeof(struct tablo));
	struct tablo * SMAX = malloc(sizeof(struct tablo));  
	struct tablo *Ms = malloc(sizeof(struct tablo));
	struct  tablo *Mp = malloc(sizeof(struct tablo));
	struct  tablo *M = malloc(sizeof(struct tablo));



	a->tab = malloc(source.size*2*sizeof(int));
	PSUM->tab = malloc(source.size*sizeof(int));
	SSUM->tab = malloc(source.size*sizeof(int));
	PMAX->tab = malloc(source.size*sizeof(int));
	SMAX->tab = calloc(source.size,sizeof(int));
	Ms->tab = malloc(source.size*sizeof(int));
	Mp->tab = malloc(source.size*sizeof(int));
	M->tab = malloc(source.size*sizeof(int));

	a->size =source.size*2;
	PSUM->size = source.size;
	SSUM->size = source.size;
	PMAX->size = source.size;
	SMAX->size = source.size;
	Ms->size = source.size;
	Mp->size = source.size;
	M->size = source.size;

	//gettimeofday(&t1,NULL);

	prefix(source,a,PSUM,'s'); 

	//printArray(PSUM,"PSUM");

	suffixe(PSUM, SSUM, 's');

	//printArray(SSUM,"SSUM");
	suffixe(PSUM,SMAX,'m');
	//printArray(SMAX,"SMAX");



	prefix(*SSUM,a,PMAX,'m');

	//printArray(PMAX,"PMAX");

	int i;
	#pragma omp parallel for
	for (i = 0; i < source.size; ++i)
	{
	  Ms->tab[i] = PMAX->tab[i] - SSUM->tab[i] + source.tab[i];
	  Mp->tab[i] = SMAX->tab[i] - PSUM->tab[i] + source.tab[i];
	  M->tab[i] = Ms->tab[i] + Mp->tab[i] - source.tab[i];
	}



	//printf("M = ");
	//printf("[");
	// for (i = 0; i < M->size; i++)
	// {
	//   printf(" %d", M->tab[i]);
	// }
	//  printf("]\n");
	// printf("************************\n RESULTAT FINAL \n********************** \n");

	// copieTableau(M,temp);
	// montee(M,temp,'m');
	// int max =temp->tab[1];
	// printf("[%d", max); 
	
	// #pragma omp parallel for
	// for (i = 0; i < M->size; i++)
	// {
	//   if(M->tab[i]==max){
	//     printf(" %d", source.tab[i]);
	//   }
	// }
	// printf("]\n");

	maxM(M);

	// gettimeofday(&t2,NULL);
	// //printf("___________________________________________________________");
	// float res = (float)((t2.tv_usec + t2.tv_sec*1000000) - (t1.tv_usec + t1.tv_sec*1000000));
	// printf ("%d : %f\n",atoi(argv[2]), res);
	// //printf("___________________________________________________________");
	

	// free(a->tab);
	// free(PSUM->tab);
	// free(PMAX->tab);
	// free(SSUM->tab);
	// free(SMAX);
	// free(Ms->tab);
	// free(Mp->tab);
	// free(M->tab);

	// free(a);
	// free(PSUM);
	// free(PMAX);
	// free(SSUM);
	// free(SMAX);
	// free(Ms);
	// free(Mp);
	// free(M);
	return 0;
}