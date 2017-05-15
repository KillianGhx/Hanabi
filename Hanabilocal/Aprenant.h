/*
 * Aprenant.h
 *
 *  Created on: 30 avr. 2017
 *      Author: ubuntu
 */
#include "Reseau.h"
#include "Game.h"
#ifndef HANABILOCAL_APRENANT_H_
#define HANABILOCAL_APRENANT_H_

class Aprenant{
private :
	Reseau res;
public :
	Aprenant();
	Aprenant(vector<int>);
	~Aprenant(){};
	double enAvant(vector<double> entrer);

	//apprentissage sur une partie enregistrer en binaire
	void learn(vector<vector<double>>,int target);
};



#endif /* HANABILOCAL_APRENANT_H_ */
