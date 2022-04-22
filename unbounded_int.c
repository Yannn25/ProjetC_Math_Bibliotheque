#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>//ensemble de bibliothèques standard de fonctions pour vérifier la valeur d'un char

#include "unbounded_int.h"

static chiffre *new(char c){
    chiffre *res = malloc(sizeof(chiffre));
    assert(res != NULL);
    res->c = c;
    res->suivant = NULL;
    res->precedent = NULL;
}
static unbounded_int  NouvelleListe(){
    unbounded_int *ub = malloc(sizeof(unbounded_int));
    assert(ub != NULL);
    ub->len = 0;
    ub->signe = '*';
    ub->premier = NULL;
    ub->dernier = NULL;

    return *ub;
}


unbounded_int string2unbounded_int(const char *e) {
    unbounded_int liste = NouvelleListe();
    chiffre *c = malloc(sizeof(chiffre));
    if(c == NULL){
        return liste;
    }
    size_t deb = 0;

    if (e[0] == '-') {
       liste.signe = '-';
       deb = 1;
    }

    for (size_t i = deb; i < strlen(e); i++) {
        if (isdigit(e[i])) { //isdigit()-> vérifie si un caractère est un chiffre
            c = new(e[i]);
            if (liste.premier != NULL) {
                liste.dernier->suivant = c; 
		        c->precedent = liste.dernier;
		        liste.dernier = c;
            }
           if (liste.premier == NULL) {    
                liste.premier = c;
                liste.dernier = c;
           }  

           liste.len++;
        }
    }
    if (deb == 0 )
        liste.signe = '+';
        
    return liste;
}

unbounded_int ll2unbounded_int(long long i) {
   
   char e = i+'0';//transforme le nombre en chaine de caractère
   unbounded_int liste = string2unbounded_int(&e);

   return liste;
    
}


char * unbounded_int2string(unbounded_int i) {
    assert(i.signe != '*');
    char *res = malloc(i.len * sizeof(char) + 1);
    if( res == NULL ){
        perror("échec de malloc réesayer\n");
        exit(1);
    }
    chiffre *tmp = i.premier;
    int ind = 0;
    while ( tmp != i.dernier ) {
        res[ind] = tmp->c;
        ind++;
        tmp = tmp->suivant;
    }
    res[i.len+1] = "\0";
    return res;
}

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    assert(a.signe != '*' && b.signe != '*');
    //on commence par vérifier les signes et ont agit en conséquence
    if( a.signe != b.signe ){   
        return a.signe == '1' ? -1 : 1;
    }

    /* ensuite on regarde la longueur de nos nombres si l'un est plus long que l'autre
       alors on agit en fonction */
    if((int)a.len != (int)b.len ){   
        return (int)a.len < (int)b.len ? -1 : 1;
    }

    /* */
    chiffre *tmpA = a.premier;
    chiffre *tmpB = b.premier;
    while ( tmpA != a.dernier && tmpB != b.dernier) {
        if( tmpA->c > tmpB->c || tmpA->c < tmpB->c ){
            return tmpA->c < tmpB->c ? -1 : 1;
        }
        tmpA = tmpA->suivant;
        tmpB = tmpB->suivant;
    }
    return 0;
}

int unbounded_int_cmp_ll(unbounded_int a, long long b) {
    return unbounded_int_cmp_unbounded_int(a,ll2unbounded_int(b));
}

static void affiche_unbounded_int(unbounded_int a) {
    printf("Longueur : %ld et Signe : %c\nunbounded_int : ",a.len,a.signe);
    chiffre *tmp = a.premier;
    while( tmp !=  NULL){
        printf("%c ",tmp->c);
        tmp = tmp->suivant;
    }
    printf("\n");
}
