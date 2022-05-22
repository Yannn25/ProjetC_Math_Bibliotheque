#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>//ensemble de bibliothèques standard de fonctions pour vérifier la valeur d'un char

#include "unbounded_int.h"



static chiffre *newChiffre(char c){
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
            c = newChiffre(e[i]);
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

static char *ll2str(long long i) {
    int len = 0;
    long long cop1 = i;
    //on commence par chercher la longeur de notre nombre
    while(cop1 != 0) {
        len+=1;
        cop1/=10;
    }
    // on prévoit d'allouer plus d'espace de mémoire si notre chiffre est négatif 
    char *res = i > 0  ? malloc((len * sizeof(char)) + 1) : malloc((len * sizeof(char)) + 2);
    int deb = i > 0  ? 0 : 1;
    if(deb == 1){
        res[0] = '-';
        len++;
    }
    // on place nos chiffres sans oublier de les convertir en char
    for(int j = len-1; j >= deb; j--){
        res[j] = (abs(i)%10)+'0';
        i /= 10;
    }
    //on oublie pas de mettre le caractère qui spécifie la fin de notre chaine de caractere
    res[len] = '\0';
    return res;
}
unbounded_int ll2unbounded_int(long long i) {

   char *e = ll2str(i);
   return string2unbounded_int(e);

}



char *unbounded_int2string(unbounded_int i) {
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

    /* on parcours nos deux chiffres a la recherche de différence les sachant de meme taille */
    chiffre *tmpA = a.premier;
    chiffre *tmpB = b.premier;
    do {
        if( tmpA->c > tmpB->c || tmpA->c < tmpB->c ){
            return tmpA->c < tmpB->c ? -1 : 1;
        }
        tmpA = tmpA->suivant;
        tmpB = tmpB->suivant;
    }while ( tmpA != NULL && tmpB != NULL);
    //si a la fin de notre parcours on ne trouve aucune différence alors ils sont égaux
    return 0;
}

int unbounded_int_cmp_ll(unbounded_int a, long long b) {
    return unbounded_int_cmp_unbounded_int(a,ll2unbounded_int(b));
}

static unbounded_int abs_unboundedint(unbounded_int a) {
    a.signe = '+';
    return a;
}
static unbounded_int neg_unboundedint(unbounded_int a) {
    a.signe = '-';
    return a;
}

unbounded_int unbounded_int_somme(unbounded_int a, unbounded_int b) {
    if(a.signe == '+' && b.signe == '-') {
        unbounded_int tmp;
        return unbounded_int_difference(a,tmp = abs_unboundedint(b));
    }
    if(a.signe == '-' && b.signe == '+') {
        unbounded_int tmp;
        return unbounded_int_difference(b,tmp = abs_unboundedint(a));
    }
    int l = a.len > b.len ? a.len : b.len;
    char *res = malloc((sizeof(char) * l) + 2);
    if(res == NULL) return NouvelleListe();
    res[l+1] = '\0';
    if(a.signe == '-' && b.signe == '-') {
        res[0] = '-';
    }
    chiffre *tmpA = a.dernier;
    chiffre *tmpB = b.dernier;
    int r = 0;
    int c;
    do {
      if(tmpA != NULL && tmpB != NULL) {  
            c = (((tmpA->c-'0') + (tmpB->c-'0')+ r )%10);
            r = ((tmpA->c-'0') + (tmpB->c-'0')+ r )/10;
            res[l] = c+'0';
            l--;
            tmpA = tmpA->precedent;
            tmpB = tmpB->precedent;
      } else if(tmpA == NULL && tmpB != NULL){
            c = (( (tmpB->c-'0')+ r)%10);
            res[l] = c+'0';
            r = ((tmpB->c-'0')+ r)/10;
            l--;
            tmpB = tmpB->precedent;
      } else {
            c = (( (tmpA->c-'0')+ r )%10);
            res[l] = c+'0';
            r = ((tmpA->c-'0')+ r )/10;
            l--;
            tmpA = tmpA->precedent;
      }
    } while(tmpA != NULL || tmpB != NULL);
    if(l == 0 && res[l] != '-') res[l] = r != 0  ? r + '0' : 'a'; 
    return string2unbounded_int(res);
}

unbounded_int unbounded_int_difference( unbounded_int a, unbounded_int b) {
    if(unbounded_int_cmp_unbounded_int(a,b) == -1) return neg_unboundedint(unbounded_int_difference(b,a));
    if(a.signe == '+' && b.signe == '-') {
        unbounded_int tmp;
        return unbounded_int_somme(a,tmp = abs_unboundedint(b));
    }
    if(a.signe == '-' && b.signe == '+') {
        unbounded_int tmp;
        return neg_unboundedint(unbounded_int_somme(b,tmp = abs_unboundedint(a)));
    }
    int l = a.len > b.len ? a.len : b.len;
    char *res = malloc((sizeof(char) * l) + 1);
    if(res == NULL) return NouvelleListe();
    res[l] = '\0';
    chiffre *tmpA = a.dernier;
    chiffre *tmpB = b.dernier;
    int r = 0;
    int c;
    do{
        if(tmpA != NULL && tmpB != NULL) {  
           if( ( ( (tmpA->c-'0') - (tmpB->c-'0') ) + r ) >= 0 ){
               c = ( ( (tmpA->c-'0') - (tmpB->c-'0') ) + r );
               r = 0;
           } else {
               c = ( ( (tmpA->c-'0') - (tmpB->c-'0') ) + r ) + 10;
               r = -1;
           }
            res[l-1] = c+'0';
            l--;
            tmpA = tmpA->precedent;
            tmpB = tmpB->precedent;
      } else if(tmpA == NULL && tmpB != NULL){
           if( ( (tmpB->c-'0') + r ) >= 0 ){
               c = ( ( (tmpB->c-'0') ) + r );
               r = 0;
           } else {
               c = ( ( (tmpB->c-'0') ) + r ) + 10;
               r = -1;
           }
            res[l-1] = c+'0';
            l--;
            tmpB = tmpB->precedent;
      } else {
           if( ( (tmpA->c-'0') + r ) >= 0 ){
               c = ( ( (tmpA->c-'0') ) + r );
               r = 0;
           } else {
               c = ( ( (tmpA->c-'0') ) + r ) + 10;
               r = -1;
           }
            res[l-1] = c+'0';
            l--;
            tmpA = tmpA->precedent; 
      }
    } while(tmpA != NULL || tmpB != NULL);
    int j = 0;
    while(res[j] == '0' ){
        res[j] = 'a';
        j++;
    }
    return string2unbounded_int(res);
}

unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b) {
    if ( a.signe == '-' && b.signe == '-' ){
        unbounded_int tmp1; unbounded_int tmp2;
        return  unbounded_int_produit( tmp1 = abs_unboundedint(a), tmp2 = abs_unboundedint(b) ) ; 
    }
    if ( a.signe == '-' || b.signe == '-' ){
        unbounded_int tmp1; unbounded_int tmp2;
        return neg_unboundedint( unbounded_int_produit( tmp1 = abs_unboundedint(a), tmp2 = abs_unboundedint(b) ) ); 
    }
    long long v = unbounded_int2ll(a) * unbounded_int2ll(b);
    char *res = ll2str(v);
    return string2unbounded_int(res);
}

/* Première implémentation qui ne marche pas!!! 
unbounded_int unbounded_int_produit( unbounded_int a, unbounded_int b) {
    if ( a.signe == '-' || b.signe == '-' ){
        unbounded_int tmp1; unbounded_int tmp2;
        return neg_unboundedint( unbounded_int_produit( tmp1 = abs_unboundedint(a), tmp2 = abs_unboundedint(b) ) ); 
    }
    int l = a.len > b.len ? a.len : b.len;
    char *res = malloc( ( (sizeof(char) * l) * 2) + 1);
    if(res == NULL) return NouvelleListe();
    res[l*2] = '\0';
    for(int i = 0; i < l*2; i++){
      res[i] = '0';
    }
    char *strA = unbounded_int2string(a);
    char *strB = unbounded_int2string(b); 
    int r = 0, i = 0, j = 0, w = 0;
    for( j = 0; j < (int)b.len; j++){ // boucle sur les chiffres de b
        r = 0;
        if( strB[j] == 0 )
            continue;
        for(i = 0; i < (int)a.len; i++ ){ // boucle sur les chiffres de a
            int v = (res[i+j] - '0') + ( (strA[i] - '0')*(strB[j] - '0') ) + r;
            res[i+j] = (v % 10) + '0';
            r = v / 10;
            }
            res[j + (int)a.len] = r + '0';
            w++;
        }
    w++;    
    while(res[w] == '0' ){
        res[w] = 'a';
        w++;
    }
    return string2unbounded_int(res);
}
*/


<<<<<<< unbounded_int.c
static void affiche_unbounded_int(unbounded_int a) {
    printf("Longueur : %ld et Signe : %c\nunbounded_int : ",a.len,a.signe);
    chiffre *tmp = a.premier;
    while( tmp !=  NULL){
        printf("%c ",tmp->c);
        tmp = tmp->suivant;
    }
    printf("\n");
}

static long long unbounded_int2ll(unbounded_int a) {
    long long res = 0;
    int mul = 1;
    chiffre *tmp = a.dernier;
    while(tmp != NULL) {
        res += (tmp->c - '0') * mul;
        mul = mul*10;
        tmp = tmp->precedent;
    }
    return res;
}
// static char *binaire(long long a) {
//   long long cop1 = a;
//   int l = 0;
//   while(cop1 > 0) {
//     cop1 /= 2;
//     l++; 
//   }
//   long long cop2 = a;
//   char *res = a > 0  ? malloc((l * sizeof(char)) + 1) : malloc((l * sizeof(char)) + 2);
//   int deb = a > 0  ? 0 : 1;
//   if(deb == 1){
//         res[0] = '-';
//         l++;
//   }
//   for(int j = l-1; j >= deb; j--){
//         res[j] = (abs(cop2)%2)+'0';
//         cop2 /= 2;
//   }
//   //on oublie pas de mettre le caractère qui spécifie la fin de notre chaine de caractere
//   res[l] = '\0';
//   return res;
// }

// static long long bin2ll(char *bin) {
//   int mul = 1;
//   int deb = bin[0] == '-' ? 1 : 0; 
//   long long res = 0, i;
//   for(i = strlen(bin)-1; i >= deb; i--) {
//     res += (bin[i] - '0') *  mul;
//     mul *= 2;
//   }
//   return res;
// }

/*static char  *divBinaire(char *a,char *b){
  int lenA = strlen(a), lenB = strlen(b);
  char *res = malloc( lenA + 1); 
  res[lenA] = '\0';
  char *tmp;
   //Division de a par b avec la méthode de décalage... 
  for(int i = 0; i < lenA; i++) {
    tmp = memcpy(tmp, a+i, lenB);
  }
}*/

// unbounded_int unbounded_int_quotient(unbounded_int a, unbounded_int b ) {
//     /*  On commence par convertir nos unbounded int en long long */
//     long long lla = unbounded_int2ll(a);
//     long long llb = unbounded_int2ll(b);

//     /* Ensuite on convertir le tout en base binaire */
//     char *binA = binaire(lla);
//     char *binB = binaire(llb);
    
//     /* Puis on effectue leur division */
//     char *res = divBinaire(binA, binB);

//     /* Enfin on retourne le resultat de la division sous forme de unbounded int
//     (avec au préalable la conversion du résultat en décimal) */
//     return ll2unbounded_int(bin2ll(res));
// }
=======

>>>>>>> unbounded_int.c