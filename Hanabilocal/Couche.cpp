/*
 * Couche.cpp
 *
 *  Created on: 12 mars 2017
 *      Author: ubuntu
 */

#include <ctime>
#include <cstdlib>
#include "Couche.h"
#include <iostream>

static int borneMin = -1;
static int borneMax= 1;


Couche::Couche(){
	nbneurones = 0;
	voisin=vector<Couche>();
}

Couche::Couche(int nb){
	voisin = vector<Couche>();
	nbneurones=nb;
	for(int i =0; i<nbneurones;i++){
		neurones.push_back(Neurone());
	}
}

Couche::~Couche(){
	//Destruction de la couche
}

Couche::Couche(Couche c,int nb){
	voisin.push_back(c);
	nbneurones=nb;
	for(int i=0; i<nbneurones;i++){
		neurones.push_back(Neurone());
		for(int j =0;j<this->voisin[0].getNbneurones();j++){
			neurones.at(i).poids.push_back((rand()%(1000*(borneMax-(borneMin))+1))/1000.+(borneMin));
		}
	}
}

Couche::Couche(Couche c, vector<double> pds,double biais){
	voisin.push_back(c);
	nbneurones=1;
	neurones.push_back(Neurone(pds,biais));
}

void Couche::affiche(){
	vector <Neurone>::iterator it_neurone;
	vector<Couche>::iterator it_voisin;
	cout << "Affichage des neurones de la couche : "<<endl;
	for(it_neurone=this->neurones.begin();it_neurone!=this->neurones.end(); it_neurone++){
		it_neurone->affiche();
	}
	cout << " Affichage de la couche voisine du dessous : " << endl;
	for(it_voisin=this->voisin.begin();it_voisin!=this->voisin.end(); it_voisin++){
			it_voisin->affiche();
		}


}

