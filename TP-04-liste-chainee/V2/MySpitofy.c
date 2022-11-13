#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListOfMusic.h"

void afficheElement(Element e)
{
    Music *music = (Music *)e;
    printf("%s,", music->name);
    printf("%s,", music->artist);
    printf("%s,", music->album);
    printf("%s,", music->type);
    printf("%s,", music->discNumber);
    printf("%s,", music->trackNumber);
    printf("%s", music->year);
    printf("\n");
}

void detruireElement(Element e)
{
    Music *music = (Music *)e;
    free(music->name);
    free(music->type);
    free(music->album);
    free(music->artist);
    free(music->discNumber);
    free(music->trackNumber);
    free(music->year);
    free(music);
    e = NULL;
}

bool equalsElement(Element e1, Element e2)
{
    Music *music1 = (Music *)e1;
    Music *music2 = (Music *)e2;

    if (strcmp(music1->name, music2->name) != 0){
        return 0;
    }
    if (strcmp(music1->type, music2->type) != 0){
        return 0;
    }
    if (strcmp(music1->album, music2->album) != 0){
        return 0;
    }
    if (strcmp(music1->artist, music2->artist) != 0){
        return 0;
    }
    if (strcmp(music1->discNumber, music2->discNumber) != 0){
        return 0;
    }
    if (strcmp(music1->trackNumber, music2->trackNumber) != 0){
        return 0;
    }
    if (strcmp(music1->year, music2->year) != 0){
        return 0;
    }
    return 1;
}

Liste lireCSV(FILE *csv){
    Liste lst;
    int tailleLigne = 256;
    lst = NULL;
    Music *musicTemp;
    char *line, *copy, *value, *tracer;
    line = calloc(tailleLigne, sizeof(char));
    while (fgets(line, tailleLigne, csv) != NULL)
    {
        musicTemp = malloc(sizeof(Music));
        copy = strdup(line);
        tracer = copy;

        value = strsep(&copy, ",\n");
        musicTemp->name = calloc(strlen(value) + 1, sizeof(char));
        strcpy(musicTemp->name, value);

        value = strsep(&copy, ",\n");
        musicTemp->artist = calloc(strlen(value) + 1, sizeof(char));
        strcpy(musicTemp->artist, value);

        value = strsep(&copy, ",\n");
        musicTemp->album = calloc(strlen(value) + 1, sizeof(char));
        strcpy(musicTemp->album, value);

        value = strsep(&copy, ",\n");
        musicTemp->type = calloc(strlen(value) + 1, sizeof(char));
        strcpy(musicTemp->type, value);

        value = strsep(&copy, ",\n");
        musicTemp->discNumber = calloc(strlen(value) + 1, sizeof(char));
        strcpy(musicTemp->discNumber, value);

        value = strsep(&copy, ",\n");
        musicTemp->trackNumber = calloc(strlen(value) + 1, sizeof(char));
        strcpy(musicTemp->trackNumber, value);

        value = strsep(&copy, ",\n");
        musicTemp->year = calloc(strlen(value) + 1, sizeof(char));
        strcpy(musicTemp->year, value);

        lst = ajoutFin_i(musicTemp, lst);
        free(tracer);
    }
    free(line);
    return lst;
}

Liste triParAnnee(Liste lst){
    if(estVide(lst) || estVide(lst->suiv)){
		return lst;
	}

    Cellule *actu, *prec, *ancien, *precAncien; 
    Music *musicActu = actu->val; 
    Music *musicPrec = prec->val; 
    Music *musicAncien = ancien->val; 
    Music *musicPrecAncien = precAncien->val;

	actu = prec = ancien = precAncien = lst;

	while(!estVide(actu)){
		if(strcmp(musicActu->year, musicAncien->year) <= 0){
			precAncien = prec;
			ancien = actu;
		}
		prec = actu;
		actu = actu->suiv;
	}

	Liste temp;
	if(ancien != lst){
		precAncien->suiv = lst;
		temp = lst->suiv;
		lst->suiv = ancien->suiv;
		ancien->suiv = temp;
	}
	ancien->suiv = trierParAnnee(ancien->suiv);

	return ancien;
}

int main(void){

    FILE* file;
    file = fopen("music.csv","r");
    Liste library;

    library = lireCSV(file); 
    afficheListe_i(library);
    detruire_r(library);
    fclose(file);
    return 0;
}