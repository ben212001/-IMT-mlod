#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "dates.h"

void initialiseDate(Date *d){
    printf("Rentrer le jour: ");
    scanf("%d", &(*d).jour);    //petit point syntaxe:  (*d).jour = d->jour
    printf("Rentrer le mois: ");
    scanf("%d", &(*d).mois);
    printf("Rentrer l'annee: ");
    scanf("%d", &(*d).annee);
    printf("\n");
}

void afficheDate(Date *d){
    printf("Nous sommes le %d/%d/%d\n", d->jour, d->mois, d->annee);
}

Date creerDateParCopie(){
    Date d;
    initialiseDate(&d);
    return d;
}
