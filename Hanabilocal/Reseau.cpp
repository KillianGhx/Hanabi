/*
 * Reseau.cpp
 *
 *  Created on: 12 mars 2017
 *      Author: ubuntu
 */

#include "Reseau.h"
#include <iostream>

/**
 * Creation du reseau de neurone de deux couches avec les poids en entrer
 */

Reseau::Reseau(vector<double> poidsSortie) {
	vector<double>::iterator it;
	this->entrer = Couche(poidsSortie.size());
	coucheCacher = 0;
	pas = 0.1;
	this->sortie = Couche(entrer, poidsSortie, 0.5);
}

Reseau::Reseau() {
	int e = 0, c = 0, s = 1;
	double Pas = 0.1;
	cout << "rentrer le nombre de neurones d'entrer" << endl;
	cin >> e;
	cout << "rentrer le nombre de neurones dans la couche cache" << endl;
	cin >> c;
	// creation des couches

	this->entrer = Couche(e);
	if (c != 0) {
		this->cacher = Couche(entrer, c);
		this->sortie = Couche(cacher, s);
		this->pas = Pas;
	} else {
		coucheCacher = 0;
		this->sortie = Couche(entrer, s);
		this->pas = Pas;
	}
}

/**
 * Creation d'un reseau de neurone avec des poids initialises aleatirement
 */

Reseau::Reseau(int e, int c, int s, double p) {

	this->entrer = Couche(e);

	//creation des couches
	//dans le cas ou la couche cache existe
	if (c != 0) {
		this->cacher = Couche(entrer, c);
		this->sortie = Couche(cacher, s);
		this->pas = p;
		coucheCacher = 1;
	}
	// dans le cas ou il n'y a pas de couche cache
	else {
		coucheCacher = 0;
		this->sortie = Couche(entrer, s);
		this->pas=p;
	}
}

Reseau::Reseau(int e, int c1,int c2, int s, double p) {

	coucheCacher=2;
	this->pas=p;

	//création de la couche d'entrer
	this->entrer = Couche(e);
	this->cacher=Couche(entrer,c1);
	this->cacher2=Couche(cacher,c2);
	this->sortie=Couche(cacher2,s);

}

void Reseau::input(vector<double> val) {
	for (unsigned i = 0; i < val.size(); i++) {
		entrer.neurones[i].setValeur(val[i]);
	}

}

void Reseau::transfert() {
	vector<Neurone>::iterator it;
	if (coucheCacher) {
		for (it = cacher.neurones.begin(); it != cacher.neurones.end(); it++) {
			it->setValeur(0);
			for (unsigned int i = 0; i < it->poids.size(); i++) {
				it->setValeur(
						it->getValeur()
								+ (it->poids[i] * entrer.neurones[i].getValeur()));
			}
			it->setValeur(it->getValeur() + it->getBiais());
			//cout << "Valeur avant la fonction sigmoide : " << it->getValeur() << endl;
			it->setValeur(sigmoide(it->getValeur()));
			//cout << "Valeur de f(netz) : " << it->getValeur() << endl;
		}

	}
	for (it = sortie.neurones.begin(); it != sortie.neurones.end(); it++) {
		it->setValeur(0);
		for (unsigned int i = 0; i < it->poids.size(); i++) {
			if (coucheCacher) {
				it->setValeur(it->getValeur()+ (it->poids[i]* cacher.neurones[i].getValeur()));
			} else {
				it->setValeur(it->getValeur()+ (it->poids[i] * entrer.neurones[i].getValeur()));
			}
		}
		it->setValeur(it->getValeur() + it->getBiais());
		//cout << "Valeur avant la fonction sigmoide : " << it->getValeur() << endl;
		it->setValeur(sigmoide(it->getValeur()));
		//cout << "Valeur de f(netz) : " << this->sortie.neurones[0].getValeur() << endl;
	}
}

void Reseau::affiche() {
	vector<Neurone>::iterator it;
	vector<double>::iterator it2;
	cout << "neurones de sortie : " << endl;
	for (it = sortie.neurones.begin(); it != sortie.neurones.end(); it++) {
		it->affiche();
	}
	if (this->isCoucheCacher()) {
		cout << "neurones cacher : " << endl;
		for (it = cacher.neurones.begin(); it != cacher.neurones.end(); it++) {
			it->affiche();
		}

	}

	cout << "neurones d'entrer : " << endl;
	for (it = entrer.neurones.begin(); it != entrer.neurones.end(); it++) {
		cout << "valeur : " << it->getValeur() << endl;
	}
	cout << endl;
}

double Reseau::signalErreur(double target, double out) {
	return (target - out) * (out) * (1 - out);
}

double Reseau::signalErreurCache(double out,Neurone n, int index, double signal){
	//TODO faire pour plusieurs couches cacher
	return out * (1 - out) * signal * (n.poids.at(index));
}

double Reseau::majPoid(double signal, double out) {
	return this->pas * signal * out;
}

double Reseau::backprop(vector<double> in, double target) {
	input(in);
	this->transfert();
	double signal;
	double signalCacher;
	vector<Neurone>::iterator it;
	vector<double>::iterator it2;
	int index = 0;
	int indexPoids = 0;
	for (it = sortie.neurones.begin(); it != sortie.neurones.end(); it++) {
		signal = signalErreur(target, it->getValeur());
		//cout << "signal d'erreur : " << signal << endl;

		for (it2 = it->poids.begin(); it2 != it->poids.end(); it2++) {
			if (coucheCacher) {
				*it2 += majPoid(signal, this->cacher.neurones[index].getValeur());
				//cout << "Poids : " << index << " : "<< *it2 << endl;
			} else{
				*it2 += majPoid(signal, this->entrer.neurones[index].getValeur());

			}
			index++;

		}
		it->setBiais(it->getBiais() + majPoid(signal, 1.0));
		//cout << " Poids du biais : " << it->getBiais() << endl;
		index = 0;
	}
	if (coucheCacher) {

		for (it = cacher.neurones.begin(); it != cacher.neurones.end(); it++) {
			signalCacher = signalErreurCache(it->getValeur(), this->sortie.neurones.at(0), indexPoids,signal);
			//cout << target<<"  "<< it->getValeur() << endl ;
			//cout << endl << "Signal d'erreur : " << signalCacher << endl;
			for (it2 = it->poids.begin(); it2 != it->poids.end(); it2++) {
				*it2 += majPoid(signalCacher, this->entrer.neurones[index].getValeur());
				//cout << "Poids : " << index << " : "<< *it2 << endl;
				index ++;
			}
			it->setBiais(it->getBiais() + (majPoid(signalCacher, 1.0)));
			//cout << " Poids du biais : " << it->getBiais() << endl;
			index = 0;
			indexPoids++;
		}
	}
	return signal;
}

void Reseau::getDelta(Neurone n) { // Exemple d'use : reseau.getDelta(reseau.sortie.neurones.at(0));
	if (n.poids.size() == 1) {
		cout << " delta  = " << n.poids[0] << "*x + " << n.getBiais() << endl;

	}
	if (n.poids.size() == 2) {
		cout << " delta  = " << n.poids[0] << "*x + " << n.poids[1] << "*y + " << n.getBiais() << endl;
		cout << " y = - (" << n.poids[0] <<" / " << n.poids[1] <<" ) * x - ( "<<n.getBiais()<< " / " << n.poids[1]<<")"<<endl;
	}
	if (n.poids.size() == 3) {
		cout << " delta  = " << n.poids[0] << "*x + " << n.poids[1] << "*y + "
				<< n.poids[2] << "*z + " << n.getBiais() << endl;
	}

}

