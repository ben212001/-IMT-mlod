
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix_mult.h"

#define SIZE 5

void matrix_mult(int64_t matriceResultat[][SIZE], int64_t matrice1[][SIZE], int64_t matrice2[][SIZE]){
    int a;
    for (int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            a = 0;
            for (int k= 0; k<SIZE; k++)
                matriceResultat[i][j]+=matrice1[a][k]*matrice2[k][a];
            a++;
}
    
void matrix_print(int64_t matriceResultat[][SIZE]){
    for (int i=0; i<5; i++)
        for (int j=0; j<5; j++)
            printf("%lld\t", matriceResultat[i][j]);
        printf("\n");
}