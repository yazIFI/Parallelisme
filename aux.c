#include <stdlib.h>
#include <stdio.h>


struct tablo {
  int * tab;
  int size;
};

struct valeur{
  int val;
  int index;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))



/*
pRemplirTableauAvecFichier permet d'extraire les nombres contenu dans le fichier passé en second parametre et de les placer dans la structure de tableau passé en premier parametre.
Le troisieme parametre permet à la fonction d'ignorer les x premiers nombre si on veut se placer sur le sommet x.
le quatrieme parametre permet à la fin de la fonction de connaitre le nombre reel de case utilisees dans les valeurs de la structure tableau
pRemplirTableauAvecFichier retourne un pointeur sur une structure tableau.
*/
void generateArray(struct tablo *source, char *nomFichier)
{
  source->tab = malloc(sizeof(int));
  FILE *fichier = fopen(nomFichier, "r");

  if (fichier == NULL)
  {
    exit(1); 
  }
  char caractere;
  int nbCarLu = 0;
  int positEltSuiv = 0;
  int coef = 1;
  int nbElts=1;
  
  char *temp = calloc(4,sizeof(char));
  //source = malloc(sizeof(int));
  temp[0]=' ';
  while((caractere = fgetc(fichier)) != EOF) 
  {
    source->tab = realloc(source->tab,nbElts*sizeof(int));
    source->size = nbElts;
    if (caractere >= '0' && caractere <= '9')
    {
      

      temp[nbCarLu] = caractere;
       nbCarLu++;

      
    }
    else if (nbCarLu == 0 && caractere == '-')
    {
      coef = -1;
    }
    else if (nbCarLu != 0 && (caractere == '\n' || caractere == '\t' || caractere == ' ')){
        int elt = atoi(temp) * coef;
        source->tab[positEltSuiv] = elt ;
        positEltSuiv++;
        nbElts += 1;
        coef = 1;
      
      int i;
      
      for (i = 0; i < nbCarLu; i++)
      {
         temp[i] = 0;
      }
       
        nbCarLu=0;
    }
  }

  fclose(fichier);
  free(temp);
}


int maxM(struct tablo * M){

  int i;
  int max=M->tab[0];
  for (i = 1; i < M->size; ++i)
  {
    if(max<M->tab[i]){max=M->tab[i];}
  }

  return max;
}