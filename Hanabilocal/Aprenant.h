/*
 * Aprenant.h
 *
 *  Created on: 30 avr. 2017
 *      Author: ubuntu
 */

#ifndef HANABILOCAL_APRENANT_H_
#define HANABILOCAL_APRENANT_H_
#include "Reseau.h"
#include "Game.h"

class Aprenant{
private :
	Reseau *res;
public :
	Aprenant();
	Aprenant(vector<int>);
	~Aprenant(){delete res;};
	double enAvant(vector<double> entrer);
	vector<int> previsionCoup(Game *g);

	//apprentissage sur une partie enregistrer en binaire
	void learn(vector<vector<double>>,int target);
};



#endif /* HANABILOCAL_APRENANT_H_ */
