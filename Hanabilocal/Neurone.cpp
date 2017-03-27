/*
 * Neurone.cpp
 *
 *  Created on: 12 mars 2017
 *      Author: ubuntu
 */
#include "Neurone.h"
#include <ctime>
#include <cstdlib>

static int borneMin = -1;
static int borneMax= 1;


Neurone::Neurone(){
	this->valeur=0.0;
	this->biais=(rand()%(1000*(borneMax-(borneMin))+1))/1000.+(borneMin);
//	this->biais=0.5;
	nc=this->poids.size();
}

Neurone::~Neurone(){
}

Neurone::Neurone(vector <double> pds,double biais){
	this->valeur=0.0;
	this->biais=biais;
	poids=pds;
	nc=pds.size();
}



void Neurone::affiche(){
	cout<<"valeur du neurone : " << valeur << ", valeur du biais : " << biais << endl;
	vector <double>::iterator it;
	cout << "valeur poids : ";
	for(it=poids.begin();it!=poids.end();it++){
		cout  << *it <<",  " ;
	}
	cout << endl;
}

