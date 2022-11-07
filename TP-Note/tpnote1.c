//Benjamin Puzenat

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int *repeat (int *t1[], int *t2[], int *resultat[]){
    int premiereCaseNonCompleteeDeResultat = 0;
    for (int parcoursCasesT1=1; parcoursCasesT1 <=len(t1); parcoursCasesT1++){
        int valeursCasesT1 = t1[parcoursCasesT1];
        while (valeursCasesT1>0){
            resultat[premiereCaseNonCompleteeDeResultat] = t2[parcoursCasesT1];
            valeursCasesT1--;
            premiereCaseNonCompleteeDeResultat++;
        }
return resultat;
    }
}


int main(void){
    int t1[3] = {3,4,1};
    int t2[3] = {10,2,6};
    int *resultat = malloc(33000 * sizeof(int) ); //j'alloue une place en mémoire suffisament grande pour la majorité des cas.
    int **resultatFinal = repeat(t1,t2,resultat);
    printf("le tableau resultat s'écrit (\n");
    for(int i=1; i<len(resultat);i++){
        printf("%d;",resultat[i]);
    }
    printf(")");
    free(resultat);

    return 0;
}
 
