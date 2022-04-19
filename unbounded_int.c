#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "unbounded_int.h"

 unbounded_int string2unbounded_int(const char *e) {
    unbounded_int res = malloc(strlen(e) * sizeof(unbounded_int));
    if( res == NULL ){
        res.signe = '*';
        return res;
    }
    if(e[0] == '-'){
        res.signe = '-';
        res.len = strlen(e) - 1;
    }
    res.signec = '+';
    res.len = strlen(e);
    // on initialise les pointeurs vers le premier et le dernier 
    res.premier = res.signe == '+' ? e[0] : e[1];
    res.dernier = e[strlen(e)];
    //on 
    char *tmp = e;
    while(tmp != '\0'){
        res
        e++;
    }   
    return res;
 }


char * unbounded_int2string(unbounded_int i){
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
    //return unbounded_int_cmp_unbounded_int(a,ll2unbounded_int(b));
}

static void affiche_unbounded_int(unbounded_int a) {
    printf("Longueur : %d et Signe : %ld\nunbounded_int : ",a.signe,a.len);
    chiffre *tmp = a.premier;
    while( tmp != a.dernier ){
        printf("%c ",tmp->c);
        tmp = tmp->suivant;
    }
    printf("\n");
}

int main(void) {

    char *nb = "225";
    unbounded_int n = string2unbounded_int(nb);

    affiche_unbounded_int(n);

    char *t = "test du testeur";
    printf("\n ------------ \n%s \n ----------- \n",t);
    char *unb = unbounded_int2string(n);
    printf("\n ------------ \n%s \n ----------- \n",unb);
    return 0;
}