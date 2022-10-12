#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix_mult.h"

#define SIZE 5

int main(void){
    //matrices en lignes * colonnes
    int64_t matrice1[][SIZE]={{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5},{1,2,3,4,5}};
    int64_t matrice2[][SIZE]={{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10},{6,7,8,9,10}};
    int64_t matriceResultat[SIZE][SIZE];
    
    matrix_mult(matriceResultat,matrice1,matrice2);
    matrix_print(matriceResultat);


    return EXIT_SUCCESS;
}

