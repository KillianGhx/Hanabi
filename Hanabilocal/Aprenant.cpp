/*
 * Aprenant.cpp
 *
 *  Created on: 30 avr. 2017
 *      Author: ubuntu
 */
#include "Aprenant.h"

Aprenant::Aprenant(){
	res = new Reseau({1,40,100});
}

Aprenant::Aprenant(vector<int> v){
	res = new Reseau(v);
}

double Aprenant::learn(vector<vector<double>> partie,double score){
	vector<vector<double>>::iterator it;
	double erreur=0;
//	while (erreur > 0.1 || erreur <(-0.1)){
	for (it =  partie.begin();it != partie.end();it++){
		res->backprop(*it,score);
		erreur += (res->getSortie() - score);
//	}
	erreur/=partie.size();
//	cout << erreur << endl;
	}
	return  erreur;

}

void Aprenant::learn2(vector<vector<vector<double>>> parties,vector<double> score){
	double erreur = 10000;
//	while (erreur > 0.1 || erreur <(-0.1)){
		erreur =0;
		for (unsigned i = 0;i<parties.size();i++){
			erreur += learn(parties[i],score[i]);
//		}
		erreur /= parties.size();
//		cout << erreur << endl;
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
			float max = -100000000;
			int index = 0;
			double tmp;
			int coupChoisis=0;
			for(it=nextGS.begin();it!=nextGS.end();it++){
				enAvant(*it);
				if (res->getSortie() > max){
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
//			cout << "choix de l'ia : " << out[0] << endl;
//			cout << "carte : " << out[1] << endl;
			return out;
}

