#define CHUNK_SIZE_MAX 5
#include <stdio.h>
#include <stdlib.h>

typedef struct String {
    struct String *next;
    int chunkSize;
    char *chunk[];
} String;

String *string_new(char chunkEntered[], int chunkSizeEntered){
    String *str = malloc(strlen(chunkEntered) * sizeOf(char)+ 2 * sizeOf(int)); // Je ne vois pas le problème avec mon utilisation de sizeOf
    str->next = NULL;
    str->chunkSize = chunkSizeEntered;
    char *chunkLeftToEnter;
    for(int i =0; i < chunkSizeEntered; i++)
    {   
        if(chunkEntered[i] != ' ')
        {
            str->chunk[i] = chunkEntered[i];
            chunkLeftToEnter -= chunkEntered[0]; //J'aimerais retirer le character qui vient d'être lu de la chaîne qu'il reste à lire
        }
        else
        {
            str->next = string_new(chunkLeftToEnter, strlen(chunkLeftToEnter));
        }
    }
    return str;
}


void affichageCharacter(char character){
    printf("%c", character);
}


void affichageString(String *str, int chunkSizeEntered){
    for(int i = 0; i < chunkSizeEntered; i++)
    {
        affichageCharacter(str->chunk[i]);
    }
    printf("\n");
}

unsigned int string_length(String *str){
    int compteurDeLongueur = 0;
    while(str->chunk[compteurDeLongueur] != EOF){
        compteurDeLongueur += 1;
    }
    return compteurDeLongueur;
}

String *string_insert_at(String *str, int positionWhereInsert, char chunk[]){
    String *strToInsert = string_new(chunk, strlen(chunk));
    int incrementStr = 0;
    String *nextOfElementBeforePositionToInsert;
    while(incrementStr < positionWhereInsert - 1)
    {
        incrementStr += 1;
        nextOfElementBeforePositionToInsert = str->next;
    }
    String *insert = malloc(strlen(chunk) * sizeOf(char)+ 2 * sizeOf(int));
}







int main(void)
{
    String *s = string_new("HELLO !", 6);
    affichageString(s, 6);
    unsigned int size = string_length(s);
}






