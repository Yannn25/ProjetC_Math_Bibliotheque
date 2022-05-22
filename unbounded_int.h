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


unbounded_int string2unbounded_int(const char *e);
/* prenant en argument l’adresse d’une chaîne de caractères représentant un entier (e.g. "421") et renvoyant une va-
leur unbounded_int représentant cet entier suivant le format présenté à la section 3.
Si la chaîne pointée par e ne représente pas un entier la fonction retournera un
unbounded_int avec le champ signe == ’*’. */

unbounded_int ll2unbounded_int(long long i);
/* qui prend en argument un nombre long long et retourne la structure unbounded_int représentant ce nombre. */

char *unbounded_int2string(unbounded_int i);
/* qui prend en argument une structure unbounded_int représentant un entier et retourne cet entier sous forme d’une chaîne
de caractères. Cette fonction est l’inverse de la fonction string2unbounded_in(), par exemple
unbounded_int2string(string2unbounded_in("-4543676543298" )) doit retourner un
pointeur vers la chaîne de caractères "-4543676543298". */

int unbounded_int_cmp_unbounded_int(unbounded_int a, unbounded_int b);
/* qui retourne une des valeurs −1, 0, 1 si, respectivement, a < b, a == b, a > b (ou a, b sont
les entiers représentés par a et b) */

int unbounded_int_cmp_ll(unbounded_int a, long long b);
/* envoyant la même chose que la fonction précédente, mais où le second argument est de type long long. */

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b);
/* renvoyant la représentation de la somme de deux entiers représentés par a et b */

unbounded_int unbounded_int_difference( unbounded_int a, unbounded_int b);
/* renvoyant la représentation de leur différence */

unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b);
/* renvoyant la représentation de leur produit */

/* FONCTIONS AUXILIAIRES  */

static void affiche_unbounded_int(unbounded_int a);
/* affichage de notre unbouded int ainsi que les informations sur sa longueur et sont signe*/

static char *ll2str(long long i);
/* transforme le nombre en chaine de caractère */

static unbounded_int  NouvelleListe();
/* permet de créer un nouveau unbouded int vide avec pour signe '*', de longeur 0 et sans aucun pointeur */

static chiffre *newChiffre(char c);
/* permet de créer un nouveau chiffre avec le char c passer en paramètres
    et les pointeurs suivant et precedent a NULL  */

static unbounded_int abs_unboundedint(unbounded_int a);
/* Change le signe de a en '+' afin d'obtenir sa valeur absolue */

static unbounded_int neg_unboundedint(unbounded_int a);
/* Change le signe de a en '-' de a */

static long long unbounded_int2ll(unbounded_int a); 
/* Permet de transformer un unbounded_int en long long */

//static char *binaire(long long a);
/* Convertir un nombre en binaire */

//static long long bin2ll(char *bin);
/* Convertir une chaine de caractères qui représente un nombre binaire en entier */

//static char  *divBinaire(char *a,char *b);
/* Implémentation de la division de deux nombres binaires */


