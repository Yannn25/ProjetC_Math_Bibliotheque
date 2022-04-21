#include <stdio.h>

#include "unbounded_int.c"

int main(void) {
    char *nb = "235";
    unbounded_int n = string2unbounded_int(nb);

    affiche_unbounded_int(n);

    unbounded_int a = ll2unbounded_int(321);
    affiche_unbounded_int(a);

    /*char *t = "test du testeur";
    printf("\n ------------ \n%s \n ----------- \n",t);
    char *unb = unbounded_int2string(n);
    printf("\n ------------ \n%s \n ----------- \n",unb);*/

}