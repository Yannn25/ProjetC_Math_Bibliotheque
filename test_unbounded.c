#include <stdio.h>

#include "unbounded_int.h"
static void affiche_unbounded_int(unbounded_int a);

int main(void) {
    printf("\n ------ STRING TO UNBOUNDED INT ------\n");
    printf("Conversion de '-225' en UNBOUNDED INT\n");
    char *nb = "-225";
    unbounded_int n = string2unbounded_int(nb);
    affiche_unbounded_int(n);
    printf("Conversion de '0' en UNBOUNDED INT\n");
    char *zero = "0";
    unbounded_int z =string2unbounded_int(zero);
    affiche_unbounded_int(z);
    printf("Conversion d'une chaine de caractère contenant des caractères en UNBOUNDED INT\n");
    unbounded_int sttoi = string2unbounded_int("45ga6kok7  8ppp9");
    affiche_unbounded_int(sttoi);

    printf("\n ------ LONG LONG TO UNBOUNDED INT ------\n");
    unbounded_int a = ll2unbounded_int(321);
    unbounded_int lltoi = ll2unbounded_int(-156);
    affiche_unbounded_int(a);
    affiche_unbounded_int(lltoi);

    printf("\n ------ UNBOUNDED INT TO STRING ------\n");
    char *st = unbounded_int2string(n);
    printf("\n%s\n",st);
    char *t = unbounded_int2string(string2unbounded_int("-4543676543298" ));
    printf("\n%s\n",t);

    unbounded_int b = ll2unbounded_int(322);
    unbounded_int c = ll2unbounded_int(1);
    unbounded_int d = ll2unbounded_int(321);
    printf("\n------------ \nBATTERIE DE TEST SUR LES FONCTIONS DE COMPARAISON \n");
    int e,f,g,h,i,j,k;
    e = unbounded_int_cmp_unbounded_int(n,a);//-1
    f = unbounded_int_cmp_unbounded_int(a,n);//1
    g = unbounded_int_cmp_unbounded_int(b,a);//1
    h = unbounded_int_cmp_unbounded_int(d,a);//0 
    i = unbounded_int_cmp_unbounded_int(c,n);
    j = unbounded_int_cmp_unbounded_int(c,d);
    k = unbounded_int_cmp_unbounded_int(b,b);
    printf("e: %i\nf: %i\ng: %i\nh: %i\ni: %i\nj: %i\nk: %i\n",e,f,g,h,i,j,k);
    printf("\n");
    e = unbounded_int_cmp_ll(n,-224);
    f = unbounded_int_cmp_ll(a,124);
    g = unbounded_int_cmp_ll(b,322);
    h = unbounded_int_cmp_ll(d,777);//0 
    printf("e: %i\nf: %i\ng: %i\nh: %i\ni: %i\nj: %i\nk: %i\n",e,f,g,h,i,j,k);
    printf("----------- \n");

    printf("\n--------  SOMME  -------\n");
    unbounded_int o = ll2unbounded_int(123456);
    unbounded_int p = ll2unbounded_int(654321);
    unbounded_int s = unbounded_int_somme(o,p);
    printf("La somme de 123456 et 654321 :\n");
    affiche_unbounded_int(s);
    unbounded_int l = string2unbounded_int("-20");
    unbounded_int m = string2unbounded_int("-20");
    unbounded_int ss = unbounded_int_somme(l,m);
    printf("La somme de -20 et -20 :\n");
    affiche_unbounded_int(ss);
    unbounded_int ac1 = ll2unbounded_int(28);
    unbounded_int bc1 = ll2unbounded_int(-14);
    unbounded_int sss = unbounded_int_somme(ac1,bc1);
    printf("La somme de 28 et -14 :\n");
    affiche_unbounded_int(sss);
    unbounded_int ac2 = string2unbounded_int("-90");
    unbounded_int bc2 = string2unbounded_int("30");
    printf("La somme de -90 et 30 :\n");
    unbounded_int ssss = unbounded_int_somme(ac2,bc2);
    affiche_unbounded_int(ssss);

    printf("\n--------  SOUSTRACTION  -------\n");

    unbounded_int q = ll2unbounded_int(20);
    unbounded_int r = ll2unbounded_int(24);
    unbounded_int sous = unbounded_int_difference(r,q);
    printf("La soustraction de 24 et 20 :\n");
    affiche_unbounded_int(sous);
    sous =  unbounded_int_difference(q,r);
    affiche_unbounded_int(sous);
    q = string2unbounded_int("94");
    r = string2unbounded_int("-6");
    printf("La soustraction de 94 et -6 :\n");
    sous =  unbounded_int_difference(q,r);
    affiche_unbounded_int(sous);
    q = ll2unbounded_int(-220);
    r = ll2unbounded_int(20);
    printf("La soustraction de -220 et 20 :\n");
    sous = unbounded_int_difference(q,r);
    affiche_unbounded_int(sous);

     printf("\n--------  MULTIPLICATION -------\n");
    printf("La multiplication de 225 et 15689 :\n");
    unbounded_int x = string2unbounded_int("225");
    unbounded_int w = string2unbounded_int("15689");
    unbounded_int mul = unbounded_int_produit(x,w);
    affiche_unbounded_int(mul);
    w = string2unbounded_int("-14");
    mul = unbounded_int_produit(x,w);
    printf("La multiplication de 225 et -14 :\n");
    affiche_unbounded_int(mul);
    x =  string2unbounded_int("-12");
    mul = unbounded_int_produit(x,w);
    printf("La multiplication de -12 et -14 :\n");
    affiche_unbounded_int(mul);

    return 0;

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
