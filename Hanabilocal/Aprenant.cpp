/*
 * Aprenant.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: ubuntu
 */
#include "Aprenant.h"

Aprenant::Aprenant(vector<int> v){
	res = Reseau(v);
}

void Aprenant::learn(vector<vector<double>> partie,int score){
	vector<vector<double>>::iterator it;
	for (it =  partie.begin();it != partie.end();it++){
		res.backprop(*it,res.sigmoide(score));
	}

}

double Aprenant::enAvant(vector<double> gameState){
	res.input(gameState);
	res.transfert();
	return res.getSortie();
}

