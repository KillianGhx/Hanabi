/*
 * Calcule.cpp
 *
 *  Created on: 5 mars 2017
 *      Author: louis
 */

#include "Calcule.h"
#include<fstream>
#include <iomanip>
#include <stdlib.h>



Calcule::Calcule(char  *c){
	this->chemin=c;
}

Calcule::~Calcule(){
	//cout<<"Destruction de Calcule "<<endl;
}

float Calcule::moyenne(){
	int nombre_ligne=0;
	ifstream fichierIn(this->chemin);
	float tab[300];
	do{
		string ligne;
		getline(fichierIn, ligne);
		tab[nombre_ligne]=(double)atof(ligne.c_str());
		nombre_ligne++;
	} while (!fichierIn.eof());
	float moyenne = 0;
	for (int i = 0; i < nombre_ligne - 1; i++) {
		moyenne += tab[i];
	}
	moyenne /= (nombre_ligne - 1);
	return moyenne;
}

float Calcule::max(){
	int nombre_ligne = 0;
	ifstream fichierIn(this->chemin);
	float tab[300];
	do {
		string ligne;
		getline(fichierIn, ligne);
		tab[nombre_ligne] = (double) atof(ligne.c_str());
		nombre_ligne++;
	} while (!fichierIn.eof());
	float max = 0;
	for (int i = 0; i < nombre_ligne - 1; i++) {
		if(max < tab[i]){
			max = tab[i];
		}
	}
	return max;
}

float Calcule::min(){
	int nombre_ligne = 0;
	ifstream fichierIn(this->chemin);
	float tab[300];
	do {
		string ligne;
		getline(fichierIn, ligne);
		tab[nombre_ligne] = (double) atof(ligne.c_str());
		nombre_ligne++;
	} while (!fichierIn.eof());
	float min=25;
	for (int i = 0; i < nombre_ligne - 1; i++) {
		if(min > tab[i]){
			min = tab[i];
		}
	}
	return min;
}

int Calcule::nombreDePartie(){
	int nombre_ligne = 0;
	ifstream fichierIn(this->chemin);
	do {
			string ligne;
			getline(fichierIn, ligne);
			nombre_ligne++;
		} while (!fichierIn.eof());
	return nombre_ligne;
}


void Calcule::afficherInfo(){
	cout<<"Nombre de partie : "<<this->nombreDePartie()<<endl;
	cout<<"Moyenne : "<<this->moyenne()<<endl;
	cout<<"Max : "<<this->max()<<endl;
	cout<<"Min : "<<this->min()<<endl;
}

