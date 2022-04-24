#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>//ensemble de bibliothèques standard de fonctions pour vérifier la valeur d'un char

#include "unbounded_int.h"


/* permet de créer un nouveau chiffre avec le char c passer en paramètres
    et les pointeurs suivant et precedent a NULL  */
static chiffre *new(char c){
    chiffre *res = malloc(sizeof(chiffre));
    assert(res != NULL);
    res->c = c;
    res->suivant = NULL;
    res->precedent = NULL;
    return res;
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
/* transforme le nombre en chaine de caractère */
static char *ll2str(long long i) {
    int len = 0;
    long long cop1 = i;
    //on commence par chercher la longeur de notre nombre
    while(cop1 != 0) {
        len+=1;
        cop1/=10;
    }
    // on prévoit d'allouer plus d'espace de mémoire si notre chiffre est négatif 
    char *res = i > 0 ? malloc((len * sizeof(char)) + 1) : ((len * sizeof(char)) + 2);
    int deb = i > 0 ? 0 : 1;
    if(deb == 1){
        res[0] = '-';
    }
    // on place nos chiffres sans oublier de les convertir en char
    for(int j = len-1; j >= deb; j--){
        res[j] = i%10+'0';
        i /= 10;
    }
    //on oublie pas de mettre le caractère qui spécifie la fin de notre chaine de caractere
    res[len] = '\0';
    return res;
}
unbounded_int ll2unbounded_int(long long i) {
   
   char *e = ll2str(i);
   unbounded_int liste = string2unbounded_int(e);

   return liste;
    
}


char * unbounded_int2string(unbounded_int i) {
    assert(i.signe != '*');
    // l'allocation d'espace est faite en fonction du signe de notre unbounded int  
    char *res =  i.signe == '+' ? malloc(i.len * sizeof(char) + 1) : malloc(i.len * sizeof(char) + 2);
    if( res == NULL ){
        perror("échec de malloc réesayer\n");
        exit(1);
    }
    // si l'unbounded int est de signe moins, alors on le place au début de notre string
    int ind = i.signe == '+' ? 0 : 1;
    if(ind == 1) {
        res[0] = '-';
    }

    chiffre *tmp = i.premier;
    /* on récupere tous les char de unbounded int sauf le dernier qui est ajouter a la fin
       ainsi que le caractere qui met fin a notre string */
    while ( tmp != i.dernier ) {
        res[ind] = tmp->c;
        ind++;
        tmp = tmp->suivant;  
    }
    res[ind] = i.dernier->c;
    res[ind+1] = '\0';
    return res;
}

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b) {
    assert(a.signe != '*' && b.signe != '*');
    //on commence par vérifier les signes et ont agit en conséquence
    if( a.signe != b.signe ){   
        return a.signe == '-' ? -1 : 1;
    }

    /* ensuite on regarde la longueur de nos nombres si l'un est plus long que l'autre
       alors on agit en fonction */
    if((int)a.len != (int)b.len ){   
        return (int)a.len < (int)b.len ? -1 : 1;
    }

    /* on parcours nos deux chiffres a la recherche de différence*/
    chiffre *tmpA = a.premier;
    chiffre *tmpB = b.premier;
    /* on utilise un DO WHILE a cause du dernier pointeur qui n'est pas 
       pris en compte en cas de while "normal" */
    do {
        if( tmpA->c > tmpB->c || tmpA->c < tmpB->c ){
            return tmpA->c < tmpB->c ? -1 : 1;
        }
        tmpA = tmpA->suivant;
        tmpB = tmpB->suivant;
    }while ( tmpA != a.dernier && tmpB != b.dernier);
    //si a la fin de notre parcours on ne trouve aucune différence alors ils sont égaux
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
