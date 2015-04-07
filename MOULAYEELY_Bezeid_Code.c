#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <limits.h>
#include "aux.c"

struct tablo source;

struct timeval t1,t2;

void printArray(struct tablo * tmp, char * name) {
 // printf("---- Array of size %i ---- \n", tmp->size);
  int size = tmp->size;
  //tmp->tab[0]=tmp->tab[0];
  int i;
printf("%s = [ ", name);
  for (i = 0; i < size; ++i) {
    printf(" %i ", tmp->tab[i]);
  }
  printf("]\n\n");
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
  //TODO : remplissage du tableau destination de taille 2*n en
  // copiant les données du tableau source dans destination, 
  // à la bonne position
  // on suppose que le malloc de destination a été fait avant

   destination->size=2*source->size;
   int i;
   for(i=0;i<source->size;i++){
      destination->tab[i+source->size]=source->tab[i];
   }
}

void montee(struct tablo * source, struct tablo * destination , char oper) {
  
         
  // TODO: Boucle de calcul pour la montée dans l'arbre/tableau
   
    int l;
    int j;

    for(l=ceil(log2(source->size))-1;l>=0;l--){
      int pow1 = ceil(pow(2,l));
      int pow2 = ceil(pow(2,l+1))-1;
      #pragma omp parallel for 
      for(j=pow1; j<=pow2;j++){
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

/*
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

*/

void prefix(struct tablo source, struct tablo * a, struct tablo *b, char oper){
  
  struct tablo * temp = malloc(sizeof(struct tablo));
  temp->tab = malloc(b->size*2*sizeof(int));
  temp->size =b->size*2;

  int l = 0;
  if(oper=='m'){l = INT_MIN;}

  copieTableau(&source,a);

  montee(&source,a,oper);

  a->tab[0]=l;
  //printArray(a);
  descente(a, temp,oper);
  temp->tab[0]=l;
 // printArray(b);
  final(a,temp,oper);
  temp->tab[0]=l;
  int i=0;
  #pragma omp parallel for 
  for (i = 0; i < b->size; ++i)
  {
      if(oper=='s'){b->tab[i]=temp->tab[b->size+i];}
      else{b->tab[i]=temp->tab[b->size+i];}
  }
  free(temp->tab);
  free(temp);
  


}



void suffixe(struct tablo * b, struct tablo * c, char oper){
  
  
  
    
    int taille=c->size;
   
    int i;
    if(oper=='s'){
      c->tab[0] = b->tab[taille-1];
      #pragma omp parallel for
      for (i = 1; i < taille; i++)
      {
        c->tab[i] = c->tab[0] - b->tab[i -1];

      }
    }
    if(oper=='m'){
      struct tablo *a = malloc(sizeof(struct tablo));
      a->tab = malloc(taille*2*sizeof(int));
      a->size = taille*2;
      reverse(b);
      prefix(*b,a,c,'m');
      reverse(b);
      reverse(c);
     
    }
   
}

struct valeur * maxtabi(int *t1,int *t2,int i1,int i2){
  struct valeur *v1 = malloc(sizeof(struct valeur));
  struct valeur *v2 = malloc(sizeof(struct valeur));
  v1->val = t1[i1];
  v2->val = t2[i2];
  v1->index = i1;
  v2->index = i2;
  return (((v1->val) > (v2->val)) ? (v1) : (v2));
}


struct tablo * montee2(struct tablo *source){

  struct tablo * dest = malloc(sizeof(struct tablo));
  dest->tab = calloc(source->size,sizeof(int));
  dest->size = source->size;
  struct tablo * tabi = malloc(sizeof(struct tablo));
  tabi->tab = calloc(1,sizeof(int));
  tabi->size = 1;
  int i=0;
  for(i=0;i<source->size;i++){
      dest->tab[i]=source->tab[i];
   }
  
  int l;
  int j;
  
  
  int minT=0;
  int maxT;
  int *tabR = calloc(8,sizeof(int));
 
  int size = ceil(log2(source->size/2))-1;
    
   for(l=size;l>=0;l--){
     int pow1 = ceil(pow(2,l));
     int pow2 = ceil(pow(2,l+1))-1;

    //#pragma omp parallel for 
    for(j=pow1-1; j<=pow2;j++){
      
      struct valeur *v = maxtabi(dest->tab,dest->tab,2*j,(2*j)+1);
      printf("j = %d { val = %d : ind = %d } \n",j,v->val,v->index);
      if(dest->tab[(2*j)]==dest->tab[(2*j)+1]){tabR[2*j]=tabR[(2*j)+1]=v->val;minT = 2*j;maxT=(2*j)+1;}
      else{tabR[v->index]=v->val;maxT = v->index;}
     // printf("min : %d ; max : %d \n", minT, maxT);
    } 
    printf("\n\n");
  }
   for (i = minT; i <= maxT; i++)
   {
     printf(" %d , ", dest->tab[i]);
   }
 
  return tabi;
}

