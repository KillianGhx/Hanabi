/*
 * Couleur.h
 *
 *  Created on: 21 févr. 2017
 *      Author: ubuntu
 */

#ifndef COULEUR_H_
#define COULEUR_H_
#include <string>
using namespace std;

class Couleur {
private :
	string color;
public :
	Couleur();
	Couleur(string couleur);
	~Couleur();
	int toInt();
	void affiche();
	bool operator==(const Couleur& color2);

	const string& getString() const {
		return color;
	}

	void setColor(const string& color) {
		this->color = color;
	}
};



#endif /* COULEUR_H_ */
