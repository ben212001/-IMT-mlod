#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void afficheElement(Element e) {
    printf("%s ", (char*)e);
}

void detruireElement(Element e) {
    ;
}

bool equalsElement(Element e1, Element e2) {
    return (strcmp(e1,e2)==0);
}

int main(void) {
    Liste l, p;

	l = NULL;
	printf("estVide(l) = %s\n",estVide(l)?"TRUE":"FALSE");

	l = ajoutTete("allo",l);
	l = ajoutTete("a l'huile",l);
	l = ajoutTete("waouh",l);
	l = ajoutTete("where is bryan",l);
	l = ajoutTete("ssuigui",l);
	l = ajoutTete("hey ya!",l);
	l = ajoutTete("vroum vrouuuum",l);
	l = ajoutTete("okay okayyyy",l);
	l = ajoutTete("mmmh je me régale !",l);

	afficheListe_i(l);

	ajoutFin_i("vrouuuum",l);
	afficheListe_i(l);

	ajoutFin_r("oui non",l);
	afficheListe_i(l);

	p = cherche_i("schtroumpf",l);
	printf("cherche_i(schtroumpf) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

	p = cherche_i("p",l);
	if(estVide(p))
		printf("cherche_i(p) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_i(p) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

	p = cherche_r("r",l);
	printf("cherche_r(r) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

	p = cherche_r("a",l);
	if(estVide(p))
		printf("cherche_r(a) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_r(a) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

	printf("retirePremier_i(t)   : ");
	l = retirePremier_i("t",l);
	afficheListe_r(l);

	printf("retirePremier_i(b)   : ");
	l = retirePremier_i("b",l);
	afficheListe_r(l);

	printf("retirePremier_i(biberon) : ");
	l = retirePremier_i("biberon",l);
	afficheListe_r(l);

	printf("retirePremier_r(carosse)   : ");
	l = retirePremier_r("carosse",l);
	afficheListe_r(l);

	printf("retirePremier_r(okay okayyyy)   : ");
	l = retirePremier_r("okay okayyyy",l);
	afficheListe_r(l);

	printf("retirePremier_r(hey ya!)  : ");
	l = retirePremier_r("hey ya!",l);
	afficheListe_r(l);

	detruire_r(l);

	return EXIT_SUCCESS;
};