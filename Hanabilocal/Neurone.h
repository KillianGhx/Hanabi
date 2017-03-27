/*
 * Neurone.h
 *
 *  Created on: 12 mars 2017
 *      Author: ubuntu
 */

#ifndef HANABILOCAL_SAUVEGARDE_NEURONE_H_
#define HANABILOCAL_SAUVEGARDE_NEURONE_H_


#include <vector>
#include<iostream>



using namespace std;

class Neurone{
private:
	double valeur;
	double biais;
	int nc; //nombre de connexion
public :
	vector<double> poids;

	Neurone();
	Neurone(vector <double>,double);
	~Neurone();
	void affiche();


	double getBiais() const {
		return biais;
	}

	void setBiais(double biais) {
		this->biais = biais;
	}

	int getNc() const {
		return nc;
	}

	void setNc(int nc) {
		this->nc = nc;
	}

	double getValeur() const {
		return valeur;
	}

	void setValeur(double valeur) {
		this->valeur = valeur;
	}
};



#endif /* HANABILOCAL_SAUVEGARDE_NEURONE_H_ */
