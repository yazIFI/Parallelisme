#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <limits.h>

struct tablo {
  int * tab;
  int size;
};
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


struct tablo * PSUM;
struct tablo * SSUM;
struct tablo * PMAX;
struct tablo * SMAX;

struct tablo source;

int somme=0;
void printArray(struct tablo * tmp) {
  printf("---- Array of size %i ---- \n", tmp->size);
  int size = tmp->size;
  //tmp->tab[0]=tmp->tab[0];
  int i;
  for (i = 0; i < size; ++i) {
    printf("%i ", tmp->tab[i]);
  }
  printf("\n");
}


void reverse(struct tablo *a){
  int i;
  int temp;
  for (i = 0; i < a->size/2; i++)
  {
    temp = a->tab[i];
    a->tab[i]=a->tab[a->size-i-1];
    a->tab[a->size-i-1] = temp;
  }
}

struct tablo * allocateTablo(int size) {
  struct tablo * tmp = malloc(sizeof(struct tablo));
  tmp->size = size;
  tmp->tab = malloc(size*sizeof(int));
  return tmp;
}

void copieTableau(struct tablo * source, struct tablo * destination){
   destination->size=2*source->size;
   int i;
   for(i=0;i<source->size;i++){
      destination->tab[i+source->size]=source->tab[i];
   }
}

void montee(struct tablo * source, struct tablo * destination , char oper) {
  //TODO : remplissage du tableau destination de taille 2*n en
  // copiant les données du tableau source dans destination, 
  // à la bonne position
  // on suppose que le malloc de destination a été fait avant
         
  // TODO: Boucle de calcul pour la montée dans l'arbre/tableau
   
    int l;
    int j;
    for(l=ceil(log2(source->size))-1;l>=0;l--){
      for(j=ceil(pow(2,l)); j<=ceil(pow(2,l+1)) -1;j++){
        if(oper == 's'){destination->tab[j] = destination->tab[2*j] + destination->tab[(2*j)+1];}
        if(oper == 'm'){destination->tab[j] = MAX(destination->tab[2*j] , destination->tab[(2*j)+1]);}
        
      }
    }
   
   
}


void descente(struct tablo * a, struct tablo * b, char oper) {
  // TODO : implementation de la phase de descente{}
  if(oper=='m'){b->tab[1]=INT_MIN;
  
    int l;
    
    for (l = 1; l < ceil(log2(a->size)); l++)
    {
      int j;
      int pow1 = ceil(pow(2,l));
      int pow2 = ceil(pow(2,l+1))-1;
      #pragma omp parallel for 
     for(j=pow1;j<=pow2;j++){
        
        if(j%2==0){b->tab[j]=b->tab[j/2];}
        else{b->tab[j]=MAX(b->tab[j/2], a->tab[j-1]);}
        

        }

    }
    
  }
  else{
    b->tab[1]=0;
    int l;
    
    for (l = 1; l < ceil(log2(a->size)); l++)
    {
      int j;
      int pow1 = ceil(pow(2,l));
      int pow2 = ceil(pow(2,l+1))-1;
      #pragma omp parallel for 
     for(j=pow1;j<=pow2;j++){

        if(j%2==0){b->tab[j]=b->tab[j/2];}
        else{b->tab[j]=b->tab[j/2]+a->tab[j-1];}
        
        }
    }
  }
  

}


void final(struct tablo * a, struct tablo *b, char oper) {
  // TODO : phase finale
  
  int m =  ceil(log2(a->size/2));
  int j;
  int pow1 = ceil(pow(2,m));
  int pow2 = ceil(pow(2,m+1)-1);
   #pragma omp parallel for
  for(j=pow1;j<=pow2;j++){
    if(oper=='s'){
      b->tab[j]=b->tab[j]+a->tab[j];
      
    }
    else{
      b->tab[j]= MAX(b->tab[j],a->tab[j]);
      
    }  
  }
 
}


void generateArray(struct tablo * s) {
  //construction d'un tableau pour tester
  s->size=16;
  s->tab=malloc(s->size*sizeof(int));
  s->tab[0]=3;//3;
  s->tab[1]=2;//1;
  s->tab[2]=-7;//7;
  s->tab[3]=11;//0;
  s->tab[4]=10;//4;
  s->tab[5]=-6;//1;
  s->tab[6]=4;//6;
  s->tab[7]=9;//3;
  s->tab[8]=-6;
  s->tab[9]=1;
  s->tab[10]=-2;
  s->tab[11]=-3;
  s->tab[12]=4;
  s->tab[13]=-3;
  s->tab[14]=0;
  s->tab[15]=2;

}



void prefix(struct tablo source, struct tablo * a, struct tablo *b, char oper){
  
  int l = 0;
  if(oper=='m'){l = INT_MIN;}

  copieTableau(&source,a);

  montee(&source,a,oper);

  a->tab[0]=l;
  //printArray(a);
  descente(a, b,oper);
  b->tab[0]=l;
 // printArray(b);
  final(a,b,oper);
  b->tab[0]=l;
  int i=0;
  #pragma omp parallel for 
  for (i = 0; i < source.size; ++i)
  {
      if(oper=='s'){PSUM->tab[i]=b->tab[source.size+i];}
      else{PMAX->tab[i]=b->tab[source.size+i];}
  }
  
}



void suffixe(struct tablo * b, struct tablo * c, char oper){
  

  
  if(oper=='s'){
    c->tab[0] = b->tab[b->size-1];
    int i;
    #pragma omp parallel for
    for (i = 1; i < c->size; i++)
    {
      c->tab[i] = c->tab[0] - b->tab[i -1];
    }
  }
  else{
    c->tab[0] = b->tab[b->size-1];
    int i;
    #pragma omp parallel for
    for (i = 1; i < c->size; i++)
    {
      c->tab[i] = MAX(c->tab[i-1] , b->tab[c->size - i]);
    }
  }
  int i;
  #pragma omp parallel for 
  for (i = 0; i < c->size; i++)
  {
    if(oper=='s'){SSUM->tab[i]=c->tab[i];}
    else{SMAX->tab[i]=c->tab[i];}
  }

}


void  max_subarray(struct tablo * A){
    int max_ending_here = A->tab[0];
    int  max_so_far = A->tab[0];
    int i;
    for (i = 1; i < A->size; i++)
    {
      max_ending_here = MAX(A->tab[i], max_ending_here + A->tab[i]);
      max_so_far = MAX(max_so_far, max_ending_here);
      printf(" max 1: %d  ;; %d \n", max_so_far,max_ending_here);
     
    }
    printf("test %d", MAX(2,3));
}


int main(int argc, char **argv) {

 

  generateArray(&source);

  PSUM = malloc(sizeof(struct tablo));
  PSUM->tab = malloc(source.size*sizeof(int));
  PSUM->size = source.size;

  SSUM = malloc(sizeof(struct tablo));
  SSUM->tab = malloc(source.size*sizeof(int));
  SSUM->size = source.size;
  
  PMAX = malloc(sizeof(struct tablo));
  PMAX->tab = malloc(source.size*sizeof(int));
  PMAX->size = source.size;

  SMAX = malloc(sizeof(struct tablo));
  SMAX->tab = malloc(source.size*sizeof(int));
  SMAX->size = source.size;

  struct tablo * a = malloc(sizeof(struct tablo));
  a->tab = malloc(source.size*2*sizeof(int));
  a->size =source.size*2;
  
  struct tablo * b = malloc(sizeof(struct tablo));
  b->tab= malloc(source.size*2*sizeof(int));
  b->size=source.size*2;

  struct tablo * c = malloc(sizeof(struct tablo));
  c->tab= malloc(source.size*sizeof(int));
  c->size=source.size;
  //reverse(&source);
  prefix(source,a,b,'s');
  printf("%s\n", "            PSUM");
  //reverse(PSUM);
  printArray(PSUM);
  printf("############################ \n");
  suffixe(PSUM, SSUM, 's');
  printf("%s\n", "            SSUM");
  printArray(SSUM);
  printf("############################ \n");

  suffixe(PSUM,SMAX,'m');
  reverse(SMAX);
  printf("%s\n","             SMAX");
  printArray(SMAX);
  
 
  printf("############################ \n");
  prefix(*SSUM,a,b,'m');
  printf("%s\n","             PMAX");
  
  printArray(PMAX);
  printf("############################ \n");
  printf("*****************************\n RESULTAT FINAL ********************** \n");
  int *Ms, *Mp, *M;
  Ms = malloc(source.size*sizeof(int));
  Mp = malloc(source.size*sizeof(int));
  M = malloc(source.size*sizeof(int));
  int i;
  for (i = 0; i < source.size; ++i)
  {
    Ms[i] = PMAX->tab[i] - SSUM->tab[i] + source.tab[i];
    Mp[i] = SMAX->tab[i] - PSUM->tab[i] + source.tab[i];
    M[i] = Ms[i] + Mp[i] - source.tab[i];
  }
  printf("[ ");
  for (i = 0; i < source.size; ++i)
  {
    printf("%d , ", M[i]);
  }
  printf(" ]\n");
  printf("############################ \n");

     
/*
struct tablo * A = malloc(sizeof(struct tablo));
A->tab = malloc(9*sizeof(int));
A->size =9;
A->tab[0] = -2; A->tab[1] = 1; A->tab[2] = -3; A->tab[3] = 4; A->tab[4] = -1;
A->tab[5] = 2; A->tab[6] = 1; A->tab[7] = -5; A->tab[8] = 5;
max_subarray(A);
*/
return 0;
}