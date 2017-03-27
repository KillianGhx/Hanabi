/*
 * Carte.h
 *
 *  Created on: 20 févr. 2017
 *      Author: ubuntu
 */

#ifndef CARTE_H_
#define CARTE_H_
#include "Couleur.h"


class Carte{

private :
	short numero;
	Couleur color;

public:
	Couleur getColor() const {
		return color;
	}

	void setColor(Couleur color) {
		this->color = color;
	}

	short getNumero() const {
		return numero;
	}

	void setNumero(short numero) {
		this->numero = numero;
	}

	Carte();
	Carte(Couleur color,short numero);
	virtual ~Carte();
	void affiche();
	void affiche2D();
	bool const operator==(const Carte & c){
		if(this->color == c.getColor() && this->numero==c.getNumero()){
			return true;
		}
		return false;
	}


};



#endif /* CARTE_H_ */
