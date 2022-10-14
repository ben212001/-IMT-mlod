#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
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

Date *newDate(){
    Date *d;
    d = (Date *) malloc(sizeof(Date));
    initialiseDate(d);
    free(d);
    return d;
}

bool estBissextile(unsigned int annee){
    if (annee%4==0)
        if (annee%100==0)
            return annee%400==0;
        return true;
    return false;
}

unsigned int nbreJours(Month mois, unsigned int annee){
    switch(mois){
        case 1 :
            return 31;
            break;
        case 3 :
            return 31;
            break;
        case 5 :
            return 31;
            break;
        case 7 :
            return 31;
            break;
        case 8 :
            return 31;
            break;
        case 10 :  
            return 31;
            break;
        case 12 :
            return 31;
            break;
        case 4 :
            return 30;
            break;
        case 6 :
            return 30;
            break;
        case 9 :
            return 30;
            break;
        case 11 :
            return 30;
            break;
        case 2 :
            if (estBissextile(annee))
                return 29;
            else return 28;
        default :
            printf("mois inexistant");
    }
}

bool dateValide(Date uneDate){
    return ((uneDate.annee>0 && uneDate.mois>=1 && uneDate.mois<=12 
    && uneDate.jour>0 && uneDate.jour<=nbreJours(uneDate.mois, uneDate.annee)));
}

int jourDansAnnee (Date uneDate){
    int sum =0;
    if (uneDate.mois >2)
        for (int i=1; i<uneDate.mois; i++)
            sum += nbreJours(i, uneDate.annee);
        return sum + uneDate.jour;
    return uneDate.jour;
}
