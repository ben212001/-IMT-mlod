#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dates.h"

#define SIZE 5

int main(void){
    //Date d;
    //initialiseDate(&d); //Pourquoi a t-on ajouté un &?
    //afficheDate(&d);

    //d = creerDateParCopie();
    //afficheDate(&d);

    Date *date;
    date = newDate();
    afficheDate(date);
    free(date);
    return 0;
}