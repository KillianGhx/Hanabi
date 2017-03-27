/*
 * Carte.cpp
 *
 *  Created on: 20 févr. 2017
 *      Author: ubuntu
 */

#include "Carte.h"
#include <iostream>
using namespace std;

Carte::Carte(){
	numero = 1;
	color = Couleur ("");
}
Carte::Carte(Couleur color,short numero){
	this->color = color;
	this->numero=numero;

}

void Carte::affiche(){
	cout <<"Carte - "<<this->numero<<" "<<this->color.getString();
}

void Carte::affiche2D(){
	cout<<"- - - -"<<endl;
	cout<<"|  "<<this->numero<<"  |"<<endl;
	if(this->color.getString()=="vert" || this->color.getString()=="bleu" ){
		cout<<"|"<<color.getString()<<" |"<<endl;
	}
	else{
		cout<<"|"<<color.getString()<<"|"<<endl;
	}
	cout<<"- - - -"<<endl;
}

Carte::~Carte(){
//	cout<<"Destruction de la carte "<<endl;
}


