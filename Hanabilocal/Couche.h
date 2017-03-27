/*
 * Couche.h
 *
 *  Created on: 12 mars 2017
 *      Author: ubuntu
 */

#ifndef HANABILOCAL_COUCHE_H_
#define HANABILOCAL_COUCHE_H_
#include "Neurone.h"

class Couche{
private:
	int nbneurones;
public:

	vector<Neurone> neurones;
	vector<Couche> voisin; //Couche du dessous


	Couche();
	~Couche();
	Couche(int);
	Couche(Couche ,int);
	Couche(Couche, vector<double>,double biais);
	void affiche();
	int getNbneurones() const {
			return nbneurones;
		}
};



#endif /* HANABILOCAL_COUCHE_H_ */
