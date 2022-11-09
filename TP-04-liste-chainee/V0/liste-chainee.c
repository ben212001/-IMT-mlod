#include "liste-chainee.h"
#include <stdlib.h>
#include <stdio.h>

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
	return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
	Liste lst = (Liste) malloc(sizeof(Cellule));
	if (!estVide(lst))
	{
		lst->val = v;
		lst->suiv =NULL;
	}
	else{return 1;}
	return lst;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) {
	Liste lst = creer(v);
	lst->suiv = l;
	return lst;
}


void afficheElement(Element e) {
	printf("%i",e);
}

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l) {
	Liste p = l;
	if(estVide(l)){printf("la liste est vide");}
	while(!estVide(p)){
		afficheElement(p->val);
		p = p->suiv;
	}
	printf("\n");
}

// version recursive
void afficheListe_r(Liste l) {
	if (!estVide(l)){
		afficheElement(l->val);
		afficheListe_r(l->suiv);
	}
	else
	printf("\n");
}

void detruireElement(Element e) {}

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) {
	Liste suivant, courant = l;

	while(!estVide(courant)){
		suivant=courant->suiv;
		detruireElement(courant->val);
		free(courant);
		courant = suivant;
	}
}

// version récursive
void detruire_r(Liste l) {
	while(!estVide(l)){
		detruire_r(l->suiv);
		detruireElement(l->val);
		free(l);
	}
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l) {
	Liste elem = creer(v);
	Liste p = l;

	if(estVide(p)){
		return elem;
	}

	while(!estVide(p->suiv)){
		p = p->suiv;
	}
	
	p->suiv = elem;
	return l;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l) {
	if(estVide(l))
		return creer(v);
	else
		l->suiv = ajoutFin_r(v,l->suiv);
	return l;
}

// compare deux elements
bool equalsElement(Element e1, Element e2){
	return e1 == e2;
}

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l) {
	while(!estVide(l) && !equalsElement(l->val, v)){
		l = l->suiv;
	}
	return l;
}

// version récursive
Liste cherche_r(Element v,Liste l) {
	if (estVide(l) || equalsElement(l->val,v))
		return l;
	return cherche_r(v, l->suiv);
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Element v, Liste l) {
	Liste listeDeRech = cherche_i(v, l);
	if(!estVide(listeDeRech)) {
		if(equalsElement(l->val,v)) {
			Liste p = l->suiv;
			l->suiv = NULL;
			detruire_r(l);
			return p;
		}
		else {
			Liste newL = l;
			while (!equalsElement(v, newL->suiv->val)){
				newL = newL->suiv;
			}
			newL->suiv = listeDeRech->suiv;
			listeDeRech->suiv = NULL;
			detruire_r(listeDeRech);
			return(l);
		}
	}
}

// version recursive
Liste retirePremier_r(Element v, Liste l) {
	if (!estVide(l)) {
		if (equalsElement(l->val,v)) {
			Liste p = l->suiv;
			l->suiv = NULL;
			detruire_r(l);
			return p;
		}
		else {
			l->suiv = retirePremier_r(v, l->suiv);
			return l;
		}
	}
}


void afficheEnvers_r(Liste l) {
	if(!estVide(l))
		if(!estVide(l->suiv))
			afficheEnvers_r(l->suiv);
		afficheElement(l->val);
		printf(" ");
}



