/*
 * Deck.cpp
 *
 *  Created on: 20 févr. 2017
 *      Author: ubuntu
 */

using namespace std;
#include <iostream>
#include "Deck.h"
#include <cstdlib>
#include <ctime>

Deck::Deck() {
	Deck(rand());
}

Deck::Deck(int  seed){

	list<Couleur>colors;
	colors.push_back(Couleur("bleu"));
	colors.push_back(Couleur("jaune"));
	colors.push_back(Couleur("rouge"));
	colors.push_back(Couleur("vert"));
	colors.push_back(Couleur("blanc"));
	list<Couleur>::iterator it;
	for (int i=1;i<=5;i++){
		if (i==1){
			for (int j=0;j<3;j++){
					for(it=colors.begin();it!=colors.end();it++){

						paquet.push_back(Carte(*it,i));
					}
			}

	}
		if (i == 2 || i== 3 || i==4){
			for (int j=0;j<2;j++){
					for(it=colors.begin();it!=colors.end();it++){
						paquet.push_back(Carte(*it,i));
					}
			}
	}
		if (i == 5){
					for(it=colors.begin();it!=colors.end();it++){
						paquet.push_back(Carte(*it,i));
					}
			}
	}

	this->shuffle(seed);
}

Deck::~Deck(){
//	cout << "destruction du deck " << endl;
}

void Deck::affiche(){
	vector<Carte>::iterator it;
	int compteur = 1;
	for (it = paquet.begin();it!=paquet.end();it++){
		cout<<"Carte num�ro : "<<compteur<<" - ";
		it->affiche();
		compteur++;
	}
}

void Deck::affiche2D(){
	vector<Carte>::iterator it;
	int compteur = 1;
	for (it = paquet.begin();it!=paquet.end();it++){
		cout<<"Carte num�ro : "<<compteur<<endl;
		it->affiche2D();
		compteur++;
	}
}

Carte Deck::pioche(){
	Carte buffer = paquet[paquet.size()-1];
	paquet.pop_back();
	return buffer;
}

void Deck::shuffle(int seed){
	srand(seed);
	Carte buffer1,buffer2;
	int random1;
	int random2;
	for(int i =0 ; i< 1000 ; i++){
		random1 = rand()%this->taille();
		random2 = rand()%this->taille();
		buffer1 = paquet[random1];
		paquet[random1]=paquet[random2];
		paquet[random2]=buffer1;
	}


}


int Deck::taille(){
	return paquet.size();
}
