/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring < turingWinners.txt > out.txt

 Tests
 diff out.txt turingWinners.txt

 Détection de fuites mémoires
 valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./prixTuring < turingWinners.txt > out.txt
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
**WARNING**: The result of this function has been allocated (calloc) by the function */
char* scanLine()
{
	int maxLineSize = 255;
	char c, *line = calloc(maxLineSize+1,sizeof(char));

	scanf("%250[^\n]", line);

	if ( (c = getchar()) != '\n') {
		/* we did not get all the line */
		line[250] = '[';
		line[251] = line[252] = line[253] = '.';
		line[254] = ']';
		// line[255] = '\0'; // useless because already initialized by calloc

		// let's skip all chars untli the end of line
		while (( (c = getchar()) != '\n') && c != EOF) ;
	}

	return line;
}

/* This function scans a line of text (until \n), converts it as an integer and returns this integer */
int scanLineAsInt() {
	int buf;
	scanf("%i\n",&buf);
	return buf;
}

typedef struct {
	int year;
	char* name;
	char* field;
} Winner;

typedef struct {
	int taille;
	Winner *valeurs;
} TableauWinners;

void readWinners(){
	int nbGagnants=scanLineAsInt();
	TableauWinners *allWinners;
	allWinners->taille = nbGagnants;
	allWinners->valeurs = calloc(nbGagnants, sizeof(Winner));
	for (int i=0; i<nbGagnants*3; i++){
		if (i==0 || i%3==0)
			allWinners->valeurs[i]=scanLineAsInt();
		else allWinners->valeurs=scanLine();
	}
}

/*char *printWinner(Winner winner){
	printf("%i\n", winner.year);
	printf("%s\n", winner.name);
	printf("%s\n", winner.field);
	return *winner.name;
}*/

/* Winner *printWinners(){
	int nbGagnants = scanLineAsInt();
	Winner *tousGagnants[nbGagnants];
	for (int i=0; i<nbGagnants; i++){
		tousGagnants[i]=printWinner(readWinner());
	}
	return tousGagnants;
}*/

int main(void) {

	readWinners();
	//int nbGagnants = scanLineAsInt();
	//for (int i=0; i<nbGagnants; i++){
	//	printf("%p", printWinners()[i]);
	//}


	//int nbGagnants = scanLineAsInt();
	//printf("nbGagnants = %i\n",nbGagnants);
	
	//int yearFirstWinner = scanLineAsInt();
	//printf("yearFirstWinner = %i\n", yearFirstWinner);
	//char* nameFirstWinner = scanLine();
	//printf("nameFirstWinner = %s\n", nameFirstWinner);

	return EXIT_SUCCESS;
}
