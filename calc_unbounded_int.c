#include <stdio.h>
#include <stdlib.h>
#include "unbounded_int.h"

/*  idée:
    -faire une struc variable
    -faire une liste de variables pour pouvoir les réutiliser

    lorsqu'on va lire le fichier :
    pour chaque LIGNE :
    stocker le mot jusqu'a voir un espace
    si le mot est un chiffre on le transforme en unbounded int (avec son signe)
        si on rencontre une opération on la stock dans une variable
    on recupére le deuxieme nombre comme le 1
    on traite les deux unbounded int

    si le mot est juste une variable(juste un char)
    on cherche si la vraiable existe dans notre liste de variable (si elle n'xiste pas on la créera avec les infos qui sont après le =)
    on fait les opération demandés sur cette variable

    si le mot est une instruction
     on stock l'instruction (print)
        et on l'execute sur la variable qui se situe après si la variable n'existe pas print 0
*/

typedef struct 
{
    long value;
    char name;
    unbounded_int ub;
    variable *next;
}variable;

typedef struct 
{
    variable *first;
}Liste;

int find(char variable){
    return 0;
}

void ajoutVariable(Liste l,variable v){//ajoute une variable a la in de la liste    

}

void clear(Liste l){ //vide la liste
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if (liste->premier != NULL)
    {
        variable *aSupprimer = liste->first;
        liste->first = liste->first->next;
        free(aSupprimer);
    }
}

int main(int argc, char const *argv[])
{
    FILE *src;
    FILE *dst;

    

     if(len(argv) == 3){
        src = fopen (argv [1],"r");
        dst = fopen (argv [2],"a+");
    }

    if (len(argv) == 4)
    {
        if (strcmp("-i",argv[1]))
        {
            printf("que l'option -i");
        }

        if (strcmp("-o",argv[2]))
        {
             printf("que l'option -o");
        }
        
        
    }

    if (len(argv)==5)
    {
        
    }
    
     while (fgets(texte,1024,src) != NULL)
    {
        printf("%s",texte);
    }

    return 0;
}
