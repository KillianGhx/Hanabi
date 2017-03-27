/*
 * Reseau.h
 *
 *  Created on: 12 mars 2017
 *      Author: ubuntu
 */

#ifndef HANABILOCAL_RESEAU_H_
#define HANABILOCAL_RESEAU_H_
#include "Couche.h"
#include <math.h>

class Reseau{
private :
	int coucheCacher;
	double pas;
public :
	Couche entrer,cacher,cacher2,sortie;


	Reseau();

	Reseau(vector<double>);

	Reseau(int e,int c,int s,double p);

	Reseau(int e, int c1,int c2,int s, double p);

	double getValeurSortie(){
		return sortie.neurones[0].getValeur();
	}

	double majPoid(double,double);

	void input(vector<double>);

	void transfert();

	double signalErreur(double target, double out);

	double signalErreurCache(double out, Neurone n, int index, double signal);

	double backprop(vector<double> input , double target);

	void affiche();

	static double sigmoide(double val){
		return (1/(1+exp(-val)));
	}
	void getDelta(Neurone);


	bool isCoucheCacher() const {
		return coucheCacher;
	}

	void setCoucheCacher(bool coucheCacher) {
		this->coucheCacher = coucheCacher;
	}

	double getPas() const {
		return pas;
	}

	void setPas(double pas) {
		this->pas = pas;
	}
};



#endif /* HANABILOCAL_RESEAU_H_ */
