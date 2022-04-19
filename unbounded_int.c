#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>//ensemble de bibliothèques standard de fonctions pour vérifier la valeur d'un char
#include "unbounded_int.h"

unbounded_int  NouvelleListe(){
    unbounded_int *ub = malloc(sizeof(unbounded_int));
    ub->len = 0;
    ub->signe = '*';
    ub->premier = NULL;
    ub->dernier = NULL;

    return *ub;
}

unbounded_int string2unbounded_int(const char *e)
{
    unbounded_int liste = NouvelleListe();
    chiffre *tmp  = NULL;
    chiffre *c = malloc(sizeof(chiffre));
    size_t deb = 0;

    if (e[0] == '-')
    {
       liste.signe = '-';
       deb = 1;
    }
    if( (e[0] != '-' ) || ( !isdigit(e[0])) )
        return liste;
    
    for (size_t i = deb; i < strlen(e); i++)
    {
        if (isdigit(e[i])) //isdigit()-> vérifie si un caractère est un chiffre
        {
            c->c = e[i];
            if (tmp != NULL)
            {
                tmp->suivant = c;
                c->precedent = tmp;
                tmp = c;
            }
            
           if (liste.premier == NULL)
           {    
               liste.premier = c;
                tmp = c;
           }  

           liste.len++;
        }
    }
    if (deb == 0 )
        liste.signe = '+';
    
    liste.dernier = c;

    return liste;
}

unbounded_int ll2unbounded_int(long long i)
{
   char e = i+'0';//transforme le nombre en chaine de caractère
   unbounded_int liste = string2unbounded_int(&e);

   return liste;
    
    
}

/*char *unbounded_int2string(unbounded_int i)
{
    char chaine = malloc(sizeof(int)*i.len);
    /*
        chaine[0] = '-' si le signe est moins
        sinon
    */
//}*/

int main(void) {



    return 0;
}