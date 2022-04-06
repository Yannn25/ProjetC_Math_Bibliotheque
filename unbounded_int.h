#include <stdio.h>

typedef struct chiffre{
    struct chiffre *suivant;
    char c;
    struct chiffre *precedent;
} chiffre;

typedef struct{
    char signe; /* soit ’+’ soit ’-’ */
    size_t len; /* longueur de la liste */
    chiffre *premier; /* pointeur vers le premier élément de la liste*/
    chiffre *dernier; /*pointeur vers le dernier élément de la liste*/
} unbounded_int;

/*  Toutes les fonctions auxiliaires doivent être déclarées avec l’attribut static */

/* !!!  Si les appels à malloc() échouent pour indiquer le problème la fonction doit retourner un unbounded_int
avec le champ signe == ’*’  */


char *unbounded_int2string(unbounded_int i);

unbounded_int string2unbounded_int(const char *e);

unbounded_int ll2unbounded_int(long long i);



int main(void) {


    return 0;
}
