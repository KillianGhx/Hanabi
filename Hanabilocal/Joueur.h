/*
 * Joeur.h
 *
 *  Created on: 22 f�vr. 2017
 *      Author: louis
 */

#ifndef JOUEUR_H_
#define JOUEUR_H_

#include <iostream>
#include <string>
#include "Carte.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Plateau.h"
using namespace std;

class Joueur{
private:
	int numero;
	string nom;
	bool is_ia;

public:
	void jeterCarte(int num_carte);
	int IAv2pose(Plateau p);
	vector <Carte> main;
	Joueur();
	Joueur(int num);
	Joueur(string n, int num, bool ia, vector<Carte> m);
	~Joueur();
	int valideDefausse(Plateau p);
	int IArandomchose();
	int IArandomnumerocarte(int nbcartes);
	void afficher();
	bool peutJouerCoupValide(Plateau p);
	bool peutJouer(Plateau p);
	int JouerCoup(Plateau p);
	int DefausseIA3(Plateau p);
	bool isIsIa() const {
		return is_ia;
	}

	const vector<Carte>& getMain() const {
		return main;
	}

	void setMain(const vector<Carte>& main) {
		this->main = main;
	}

	const string& getNom() const {
		return nom;
	}

	int getNumero() const {
		return numero;
	}

	void setNumero(int numero) {
		this->numero = numero;
	}
};


#endif /* JOUEUR_H_ */
