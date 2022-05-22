#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *multi(char *a, char *b) {
  int m = strlen(b);
  int n = strlen(a);
  int l = m > n ? m: n;
  char *c = malloc((l*2)+1) ;
  c[l] = '\0';
  int j;int i=0;int r;int v;
  for(j = 0; i < m; i++){ /* boucle sur les chiffres de b*/
    r = 0;
    if( b[j] == 0 )
      continue;
    for(i = 0; i < n; i++ ){ /* boucle sur les chiffres de a*/
      v = (c[i+j]-'0') + (a[i]-'0')*(b[j]-'0') + r;
      c[i+j] = v % 10;
      r = v / 10;
    }
    c[j + n] = r;
  }
  return c;
}

void affiche(char *c) {
    for(int i = 0; i < strlen(c); i++){
        printf("%i ",c[i]);
    }
    printf("\n");
}


int main() {
  char *a = "11";
  char *b = "12";
 // char *c = "";
  //int aa = (c[0]-'0') +(a[0]-'0')*(b[0]-'0');
  char *c = multi(a,b);
  affiche(c);
}