/*
 * Aprenant.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: ubuntu
 */
#include "Aprenant.h"

Aprenant::Aprenant(){
	res = new Reseau({1,80,100});
}

Aprenant::Aprenant(vector<int> v){
	res = new Reseau(v);
}

void Aprenant::learn(vector<vector<double>> partie,int score){
	vector<vector<double>>::iterator it;
	for (it =  partie.begin();it != partie.end();it++){
		res->backprop(*it,res->sigmoide(score));
	}

}

double Aprenant::enAvant(vector<double> gameState){
	res->input(gameState);
	res->transfert2();
	return res->getSortie();
}

vector<int> Aprenant::previsionCoup(Game g){
			vector<vector<double>> nextGS = g.nextGameState();
			vector<vector<double>>::iterator it;
			vector<int> out;
			double max = -100000000;
			int index = 0;
			int coupChoisis=1;
			for(it=nextGS.begin();it!=nextGS.end();it++){
				if (enAvant(*it) > max){
					max = res->getSortie();
					coupChoisis = index;
				}
				index ++;
			}
			if (coupChoisis %2 == 0){
				out.push_back(1);
			}
			if (coupChoisis %2 == 1){
				out.push_back(2);
			}
			out.push_back(coupChoisis/2);
			//cout << "choix de l'ia : " << out[0] << endl;
			//cout << "carte : " << out[1] << endl;
			return out;
}

