/*
 * Fonctions.cpp
 *
 *  Created on: 3 avr. 2017
 *      Author: ubuntu
 */

#include "Fonctions.h"
#include <ctime>
#include <random>
#include <iostream>
using namespace std;


int peutPoser1(vector<double> exemple){
	double cCarte=exemple[0];
	double nCarte=exemple[1];
	double cFeu=exemple[2];
	double nFeu=exemple[3];
	if(cCarte==cFeu && nCarte == (nFeu+1)) return 1;
	else return 0;
}

void Fonctions::poserReseau(int sizeAp,int sizeTest){
	vector<vector<double>> aprentissage;
	vector<vector<double>> test;
	vector<double> targetTest;
	vector<double> targetAprentissage;
	vector<double> tmp;
	bool appartient;
	vector<vector<double>>::iterator it;

	srand(SEED);

	// remplissage de l'ensemble d'aprentissage
	for (int i = 0;i< sizeAp;i++){
		tmp = {abs(rand()%5),abs((rand()%6)+1),abs(rand()%5),abs(rand()%5)};
		aprentissage.push_back(tmp);
		targetAprentissage.push_back(peutPoser1(tmp));
	}
	//remplissage de l'ensemble de test
		for (int i = 0;i< sizeTest;i++){
			tmp = {abs(rand()%5),abs((rand()%6)+1),abs(rand()%5),abs(rand()%5)};
			appartient = false;
			for(it = aprentissage.begin();it != aprentissage.end();it ++){
				if((*it)==tmp){
					appartient=true;
				}
			}

			if(appartient){
				i--;
			}
			else{
				test.push_back(tmp);
				targetTest.push_back(peutPoser1(tmp));
			}
		}

		Reseau res({1,4,4});

		//lancement des exemples d'aprentissage avec backprop
		cout <<endl<< "LANCEMENT DU BACKPROP" <<endl;
		double erreur = 1;
		while(erreur >0.05){
		for(int i = 0 ; i < aprentissage.size();i++){
			erreur+=res.backprop(aprentissage[i],targetAprentissage[i]);
		}
		erreur /= sizeAp;
		cout << "valeur de l'erreur" <<  erreur << endl;
		}

		int count = 0;
		//verification si les exemples sont bien classés
		cout <<endl<< "LANCEMENT DE LA PHASE DE TEST" << endl;
		for (int i = 0;i<test.size();i++){
			res.input(test[i]);
			res.transfert();
			if((res.getSortie() > 0.5 && targetTest[i]==1) || (res.getSortie() < 0.5 && targetTest[i]==0)){
				count ++;
			}
			else{
				cout << "Affichage d'une erreur" << endl;
				for (int k = 0;k < test[i].size();k++){
					cout << " " << test[i][k];
				}
				cout << endl << "target : " << targetTest[i] << endl;
			}
		}
		cout << "Nombre d'exemples bien classés : " << count << " sur : " << sizeTest << " exemples de test" << endl;


}
int peutPoser2 (vector<double> exemple){

	double cCarte=exemple[0];
	double nCarte=exemple[1];
	double nFeu1=exemple[2];
	double nFeu2=exemple[3];
	double nFeu3=exemple[4];
	double nFeu4=exemple[5];
	double nFeu5=exemple[6];

	if(cCarte == 0 && nCarte == (nFeu1+1)) return 1;
	if(cCarte == 1 && nCarte == (nFeu2+1)) return 1;
	if(cCarte == 2 && nCarte == (nFeu3+1)) return 1;
	if(cCarte == 3 && nCarte == (nFeu4+1)) return 1;
	if(cCarte == 4 && nCarte == (nFeu5+1)) return 1;
	return 0;
}

void Fonctions::poserReseau2(int sizeAp,int sizeTest){
	srand(SEED);
	vector<vector<double>> aprentissage;
	vector<vector<double>> test;
	vector<double> targetTest;
	vector<double> targetAprentissage;
	vector<double> tmp;
	bool appartient;
	vector<vector<double>>::iterator it;

	//remplissage de l'ensemble d'aprentissage
	for (int i = 0;i< sizeAp;i++){
		tmp = {abs(rand()%5),abs((rand()%6)+1),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5)};
		aprentissage.push_back(tmp);
		targetAprentissage.push_back(peutPoser2(tmp));
	}

	//remplissage de l'ensemble de test
	for (int i = 0;i< sizeTest;i++){
		tmp = {abs(rand()%5),abs(rand()%6+1),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5)};
		appartient =false;
		for(it = aprentissage.begin();it != aprentissage.end();it ++){
			if((*it)==tmp){
				appartient=true;
			}
		}

		if(!appartient){
			test.push_back(tmp);
			targetTest.push_back(peutPoser2(tmp));
		}
		else{
			i--;
		}
	}
	srand(1);
	Reseau res({1,8,20,7});
	//lancement des exemples d'aprentissage avec backprop
	cout <<endl<< "LANCEMENT DU BACKPROP" <<endl;
	double erreur = 1;
	double nb=0;
	while(erreur > 0.02){
		erreur =0;
	for(int i = 0 ; i < aprentissage.size();i++){
		res.backprop(aprentissage[i],targetAprentissage[i]);
		erreur+=res.backprop(aprentissage[i],targetAprentissage[i]);
	}
	nb ++;
	erreur /= sizeAp;
	cout << "valeur de l'erreur" << erreur << endl << "nombre d'iterations " << nb << endl;
	}

	int count = 0;
	//verification si les exemples sont bien classés
	cout <<endl<< "LANCEMENT DE LA PHASE DE TEST" << endl;
	for (int i = 0;i<test.size();i++){
		res.input(test[i]);
		res.transfert();
		if((res.getSortie() > 0.5 && targetTest[i]==1) || (res.getSortie() < 0.5 && targetTest[i]==0)){
			count ++;
		}
		else{
			cout << "Affichage d'une erreur" << endl;
			for (int k = 0;k < test[i].size();k++){
				cout << " " << test[i][k];
			}
			cout << endl << "target : " << targetTest[i] << endl;
		}
	}
	cout << "Nombre d'exemples bien classés : " << count << " sur : " << sizeTest << " exemples de test" << endl;

}

int dispensable(vector<double> exemple){
	double cCarte=exemple[0];
	double nCarte=exemple[1];
	double nFeu1=exemple[2];
	double nFeu2=exemple[3];
	double nFeu3=exemple[4];
	double nFeu4=exemple[5];
	double nFeu5=exemple[6];
	if(cCarte == 0 && nCarte <= (nFeu1)) return 1;
	if(cCarte == 1 && nCarte <= (nFeu2)) return 1;
	if(cCarte == 2 && nCarte <= (nFeu3)) return 1;
	if(cCarte == 3 && nCarte <= (nFeu4)) return 1;
	if(cCarte == 4 && nCarte <= (nFeu5)) return 1;
	return 0;

}

void Fonctions::dispensableReseau(int sizeAp,int sizeTest){

	srand(SEED);
	vector<vector<double>> aprentissage;
	vector<vector<double>> test;
	vector<double> targetTest;
	vector<double> targetAprentissage;
	vector<double> tmp;
	bool appartient;
	vector<vector<double>>::iterator it;

	//remplissage de l'ensemble d'aprentissage
	for (int i = 0;i< sizeAp;i++){
		tmp = {abs(rand()%5),abs((rand()%6)+1),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5)};
		aprentissage.push_back(tmp);
		targetAprentissage.push_back(dispensable(tmp));
	}

	//remplissage de l'ensemble de test
	for (int i = 0;i< sizeTest;i++){
		tmp = {abs(rand()%5),abs(rand()%6+1),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5),abs(rand()%5)};
		appartient =false;
		for(it = aprentissage.begin();it != aprentissage.end();it ++){
			if((*it)==tmp){
				appartient=true;
			}
		}

		if(!appartient){
			test.push_back(tmp);
			targetTest.push_back(dispensable(tmp));
		}
		else{
			i--;
		}
	}
	Reseau res({1,8,20,7});
	//lancement des exemples d'aprentissage avec backprop
	cout <<endl<< "LANCEMENT DU BACKPROP" <<endl;
	double erreur = 1;
	double nb=0;
	while(erreur > 0.02){
		erreur =0;
	for(int i = 0 ; i < aprentissage.size();i++){
		res.backprop(aprentissage[i],targetAprentissage[i]);
		erreur+=res.backprop(aprentissage[i],targetAprentissage[i]);
	}
	nb ++;
	erreur /= sizeAp;
	cout << "valeur de l'erreur" << erreur << endl << "nombre d'iterations " << nb << endl;
	}

	int count = 0;
	//verification si les exemples sont bien classés
	cout <<endl<< "LANCEMENT DE LA PHASE DE TEST" << endl;
	for (int i = 0;i<test.size();i++){
		res.input(test[i]);
		res.transfert();
		if((res.getSortie() > 0.5 && targetTest[i]==1) || (res.getSortie() < 0.5 && targetTest[i]==0)){
			count ++;
		}
		else{
			cout << "Affichage d'une erreur" << endl;
			for (int k = 0;k < test[i].size();k++){
				cout << " " << test[i][k];
			}
			cout << endl << "target : " << targetTest[i] << endl;
		}
	}
	cout << "Nombre d'exemples bien classés : " << count << " sur : " << sizeTest << " exemples de test" << endl;

}


int defaussable(vector<double> exemple){
	double cCarte=exemple[0];
	double nCarte=exemple[1];
	if(nCarte == 5) return 0;
	if(exemple[cCarte*5 + nCarte + 1 ] < 2 && nCarte==1) return 1;
	if(exemple[cCarte*5 + nCarte + 1 ] ==0) return 1;
	return 0;
}

//permet d'aprendre si la acrte est defaussage selon la defausse

void Fonctions::defaussableReseau(int sizeAp, int sizeTest){

	srand(SEED);
	vector<vector<double>> aprentissage;
	vector<vector<double>> test;
	vector<double> targetTest;
	vector<double> targetAprentissage;
	vector<double> tmp;
	bool appartient;
	vector<vector<double>>::iterator it;

	//remplissage de l'ensemble d'aprentissage
	for (int i = 0;i< sizeAp;i++){
		tmp = {abs(rand()%5),abs((rand()%6)+1),abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)};

		aprentissage.push_back(tmp);
		targetAprentissage.push_back(defaussable(tmp));
	}

	//remplissage de l'ensemble de test
	for (int i = 0;i< sizeTest;i++){
		tmp = {abs(rand()%5),abs((rand()%6)+1),abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)
				,abs(rand()%4),abs(rand()%3),abs(rand()%3),abs(rand()%3),abs(rand()%2)};

		appartient =false;
		for(it = aprentissage.begin();it != aprentissage.end();it ++){
			if((*it)==tmp){
				appartient=true;
			}
		}

		if(!appartient){
			test.push_back(tmp);
			targetTest.push_back(defaussable(tmp));
		}
		else{
			i--;
		}
	}

	srand(1);
	Reseau res({1,5,50,27});
	//lancement des exemples d'aprentissage avec backprop
	cout <<endl<< "LANCEMENT DU BACKPROP" <<endl;
	double erreur = 1;
	double nb=0;
	while(erreur > 0.1){
		erreur =0;
	for(int i = 0 ; i < aprentissage.size();i++){
		res.backprop(aprentissage[i],targetAprentissage[i]);
		erreur+=res.backprop(aprentissage[i],targetAprentissage[i]);
	}
	nb ++;
	erreur /= sizeAp;
	cout << "valeur de l'erreur" << erreur << endl << "nombre d'iterations " << nb << endl;
	}

	int count = 0;
	//verification si les exemples sont bien classés
	cout <<endl<< "LANCEMENT DE LA PHASE DE TEST" << endl;
	for (int i = 0;i<test.size();i++){
		res.input(test[i]);
		res.transfert();
		if((res.getSortie() > 0.5 && targetTest[i]==1) || (res.getSortie() < 0.5 && targetTest[i]==0)){
			count ++;
		}
		else{
			cout << "Affichage d'une erreur" << endl;
			for (int k = 0;k < test[i].size();k++){
				cout << " " << test[i][k];
			}
			cout << endl << "target : " << targetTest[i] << endl;
		}
	}
	cout << "Nombre d'exemples bien classés : " << count << " sur : " << sizeTest << " exemples de test" << endl;

}




