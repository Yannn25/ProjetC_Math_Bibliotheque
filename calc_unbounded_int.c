#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

long find(Liste l,char var){
    variable *tmp = l.first;
    while(tmp != NULL){
        if( tmp->name == var ) return 1;
        tmp = tmp->next;
    }
    return 0;
}


variable* createVariable(const char *val[],char nom){
    variable *n = malloc(sizeof(variable));
    long v = val-'\0';
    unbounded_int r = string2unbounded_int(val);
    n->value =v;
    n->name = nom;
    n->ub = r;
    n->next = NULL;
    return n;

}

void ajoutVariable(Liste *l,variable *v){  
    /* Insertion de l'élément au début de la liste */
    if (l->first == NULL)
    {
        l->first = v;
        return;
    }
    
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

void recupNombre(size_t deb,const char *chainesrc[],const char *chainedst[]){
    size_t j = 0;
    size_t i = deb;
    
    while (isdigit(chainesrc[i]) && chainesrc[i]!='\0')
        {
            chainedst[j] = chainesrc[i];
            i++;
            j++;
        }
}
char * doitprint(const char *e[]){
    char print[5];

    for (int i = 0; i < strlen(e); i++)
    {
       
    }
    
}
void TraitementLigne(const char *ligne[]){
    
        char chiffre1 [255];
        char chiffre2 [255];
        char name = malloc(sizeof(char));
        char op = malloc(sizeof(char));

        for (size_t i = 0; i < 1024; i++)
        {
            if (ligne[i] == '+' || ligne[i] == '-' || ligne[i] == '*')
            {
                op = ligne [i];
            }
            recupNombre(0,ligne,chiffre1);

            if (isalpha(ligne[i]))
            {
                name = ligne[i];
            }
        }
}

void addition(variable *v,variable *v1,variable *v2){
    v->ub = unbounded_int_somme(v1->ub, v2->ub);
}
void produit(variable *v,variable *v1,variable *v2){
    v->ub = unbounded_int_produit(v1->ub, v2->ub);
}

void soustraction(variable *v,variable *v1,variable *v2){
    v->ub = unbounded_int_difference(v1->ub, v2->ub);
}
void affiche(variable v){
    printf("%c = %ld",v.name,v.value);
}


int main(int argc, char const *argv[])
{
    FILE *src = malloc(sizeof(FILE));
    FILE *dst = malloc(sizeof(FILE));
    
    //Liste *var = malloc(sizeof(variable*3));
    //var->first = NULL;
    char ligne [1024];

     if(argc == 3){
        src = fopen (argv [1],"r+");
        dst = fopen (argv [2],"a+");
    }

    if (argc == 4)
    {
        
        if (strcmp("i",argv[1]))
        {
            printf("que l'option -i");
            src = fopen (argv [2],"r+");
            dst = stdout;
        }else
        {
           if (strcmp("-o",argv[2]))
            {
                printf("que l'option -o");
                src = fopen(argv[1],"r+");
                src = stdin;
                dst = fopen (argv [3],"a+");
            }
        }
        
    }

    if (argc == 5)
    {
         src = fopen (argv [2],"r+");
         dst = fopen (argv [4],"a+");
    }

    if(src == NULL) {
      perror("Error opening file");
      return(-1);
    }

     while (fgets(ligne,1024,src) != NULL)
    {
        TraitementLigne(ligne);
        
    }

    fclose(src);
    fclose(dst);
    return 0;
}
