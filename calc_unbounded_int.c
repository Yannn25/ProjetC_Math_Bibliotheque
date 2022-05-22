#include <stdio.h>
#include <stdlib.h>
#include "unbounded_int.h"

/*  idée:
    -faire une struc variable
    -faire une liste de variables pour pouvoir les réutiliser

    lorsqu'on va lire le fichier :
    pour chaque LIGNE :
    stocker le mot jusqu'a voir un espace

    si le mot est juste une variable(juste un char)
    on cherche si la vraiable existe dans notre liste de variable (si elle n'xiste pas on la créera avec les infos qui sont après le =)
    on fait les opération demandés sur cette variable

    si le mot est un chiffre on le transforme en unbounded int (avec son signe)
        si on rencontre une opération on la stock dans une variable
    on recupére le deuxieme nombre comme le 1
    on traite les deux unbounded int

    si le mot est une instruction
     on stock l'instruction (print)
        et on l'execute sur la variable qui se situe après si la variable n'existe pas print 0
*/

typedef struct variable
{
    long value;
    char name;
    unbounded_int ub;
    struct variable *next;
}variable;

typedef struct Liste
{
    variable *first;
}Liste;

int find(Liste l,char variable){
    return 0;
}

/*variable createVariable(char val,char nom){

}*/

void ajoutVariable(Liste *l,variable *v){//ajoute une variable au début de la liste    
        /* Création du nouvel élément */
  

    /* Insertion de l'élément au début de la liste */
    v->next = l->first;
    l->first = v;

}

void clear(Liste *liste){ //vide la liste
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    if (liste->first != NULL)
    {
        variable *aSupprimer = liste->first;
        liste->first = liste->first->next;
        free(aSupprimer);
    }
}

int main(int argc, char const *argv[])
{
    FILE *src = malloc(sizeof(FILE));
    FILE *dst = malloc(sizeof(FILE));

    char ligne [1024];

     if(argc == 3){
        src = fopen (argv [1],"r+");
        dst = fopen (argv [2],"a+");
    }

    if (argc == 4)
    {
        if ("-i" == argv[1])
        {
            printf("que l'option -i");
            src = fopen (argv [2],"r+");
            dst = stdout;
        }

        if ("-o" == argv[2])
        {
            printf("que l'option -o");
            src = stdin;
            dst = fopen (argv [3],"a+");
        }
        
        
    }

    if (argc == 5)
    {
         src = fopen (argv [2],"r+");
         dst = fopen (argv [4],"a+");
    }
    
     while (fgets(ligne,255,src) != NULL)
    {
        printf("%s",ligne);
    }

    fclose(src);
    fclose(dst);
    return 0;
}
