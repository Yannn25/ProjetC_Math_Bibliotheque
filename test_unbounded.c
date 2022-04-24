#include <stdio.h>

#include "unbounded_int.c"

int main(void) {
    printf("\n ------ STRING TO UNBOUNDED INT ------\n");
    char *nb = "-225";
    unbounded_int n = string2unbounded_int(nb);
    affiche_unbounded_int(n);

    printf("\n ------ LONG LONG TO UNBOUNDED INT ------\n");
    unbounded_int a = ll2unbounded_int(321);
    affiche_unbounded_int(a);

    printf("\n ------ UNBOUNDED INT TO STRING ------\n");
    char *st = unbounded_int2string(n);
    printf("\n%s\n",st);

    unbounded_int b = ll2unbounded_int(322);
    unbounded_int c = ll2unbounded_int(1);
    unbounded_int d = ll2unbounded_int(321);
    printf("\n------------ \nBATTERIE DE TEST SUR LA FONCTION DE COMPARAISON \n");
    int e,f,g,h,i,j,k;
    e = unbounded_int_cmp_unbounded_int(n,a);//-1
    f = unbounded_int_cmp_unbounded_int(a,n);//1
    g = unbounded_int_cmp_unbounded_int(b,a);//1
    h = unbounded_int_cmp_unbounded_int(d,a);//0 
    i = unbounded_int_cmp_unbounded_int(c,n);
    j = unbounded_int_cmp_unbounded_int(c,d);
    k = unbounded_int_cmp_unbounded_int(b,b);//err
    printf("e: %i\nf: %i\ng: %i\nh: %i\ni: %i\nj: %i\nk: %i\n",e,f,g,h,i,j,k);
    printf("----------- \n");
    /*char *t = "test du testeur";
    
    char *unb = unbounded_int2string(n);
    printf("\n ------------ \n%s \n ----------- \n",unb);*/

}