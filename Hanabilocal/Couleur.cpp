/*
 * Couleur.cpp
 *
 *  Created on: 21 févr. 2017
 *      Author: ubuntu
 */
#include "Couleur.h"
#include <iostream>
using namespace std;

Couleur::Couleur(){
	this->color="blanc";

}

Couleur::Couleur(string couleur){
	if (couleur == "bleu" || couleur == "rouge" || couleur == "blanc" || couleur == "jaune" || couleur =="vert"){
		this->color=couleur;
	}
	else {
//		cout << "la couleur n'est pas valide !" << endl;
	}
}

int Couleur::toInt(){
		if (this->color == "bleu") return 0;
		else if (this->color == "rouge") return 1;
		else if (this->color == "blanc" ) return 2;
		else if (this->color == "jaune") return 3;
		else if (this->color =="vert") return 4;
		else return 5;
}

void Couleur::affiche(){
	cout<<"La couleur est : "<<color<<endl;
}

bool Couleur::operator ==(const Couleur& color2){
	if(this->getString().compare(color2.getString())){
		return false;
	}
	return true;
}

Couleur::~Couleur(){
//	cout<<"La couleur a bien �t� d�truite."<<endl;
}
