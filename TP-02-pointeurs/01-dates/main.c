#include <stdint.h>
#include <stdlib.h>
#include "dates.h"

#define SIZE 5

int main(void){
    Date d;
    //initialiseDate(&d); //Pourquoi a t-on ajouté un &?
    //afficheDate(&d);

    d = creerDateParCopie();
    afficheDate(&d);
    return 0;
}