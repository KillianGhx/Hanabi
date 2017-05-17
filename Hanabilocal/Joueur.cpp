/*
 * Joueur.cpp
 *
 *  Created on: 22 f�vr. 2017
 *      Author: louis
 */

#include "Joueur.h"

#include <iterator>
#include <sstream>

#include "Couleur.h"

using namespace std;

Joueur::Joueur() {
	vector<Carte> init;
	this->nom = "";
	cin >> nom;
	this->numero = 0;
	this->is_ia = false;
	this->main = init;

}

Joueur::Joueur(int num) {
	vector<Carte> init;

	string n = "Joueur ";

	std::stringstream sstm;
	sstm << n << num;
	string result = sstm.str();

	this->nom = result;
	this->numero = num;
	this->is_ia = false;
	this->main = init;

}

Joueur::Joueur(string n, int num, bool ia, vector<Carte> m) {
	vector<Carte> init;
	this->nom = n;
	this->numero = num;
	this->is_ia = ia;
	this->main = m;

}

Joueur::~Joueur() {

}

void Joueur::jeterCarte(int num_carte) {
	this->main.erase(this->main.begin() + num_carte);
}

void Joueur::afficher() {
	cout << "Nom : " << nom << ", numero : " << numero << endl;
	cout << "Affichage de la main : " << endl;
	vector<Carte>::iterator it;
	int compteur = 0;
	for (it = main.begin(); it != main.end(); it++) {
		it->affiche();
		cout << " (" << compteur << ")" << endl;
		compteur++;
	}

}

int Joueur::IArandomchose() {

	return (rand() % 2) + 1;
}

int Joueur::IArandomnumerocarte(int nbcartes) {
	return rand() % nbcartes;
}

int Joueur::IAv2pose(Plateau d) {
	int move = 0;
	int index = 0;
	vector<Carte>::iterator itmain;
	vector<Carte>::iterator ittop;
	for (itmain = this->main.begin(); itmain != this->main.end(); itmain++) {
		for (ittop = d.alltop().begin(); ittop != d.alltop().end(); ittop++) {
			if (itmain->getColor() == ittop->getColor()
					&& (itmain->getNumero() == ittop->getNumero() + 1)) {
				move = index;
			}
		}
		index++;
	}
	return move;
}

bool Joueur::peutJouerCoupValide(Plateau p) {
	vector<Carte>::iterator itmain;
	vector<Carte>::iterator ittop;
	for (itmain = this->main.begin(); itmain != this->main.end(); itmain++) {
		for (ittop = p.alltop().begin(); ittop != p.alltop().end(); ittop++) {
			if (itmain->getColor() == ittop->getColor()
					&& (itmain->getNumero() == ittop->getNumero() + 1)) {
				return true;
			}
		}
	}
	return false;
}

int Joueur::valideDefausse(Plateau p) {
	int move = -1;
	vector<Carte>::iterator itmain;
	vector<Carte>::iterator itdefausse;
	vector<Carte>::iterator ittop;
	int index = 0;
	int count;
	for (itmain = this->main.begin(); itmain != this->main.end(); itmain++) {
		count = 0;

		for (itdefausse = p.defausse.begin(); itdefausse != p.defausse.end();
				itdefausse++) {
			if (*itdefausse == *itmain) {
				count++;
			}
			if (itmain->getNumero() == 1) {
				if (count <= 2) {
					move = index;
				}
			}
		}
		if (itmain->getNumero() == 2 || itmain->getNumero() == 3
				|| itmain->getNumero() == 4) {
			if (count <= 1) {
				move = index;
				cout << "debug " << "count =" << count << endl;
			}
		}

		index++;

	}
	index = 0;
	for (itmain = this->main.begin(); itmain != this->main.end(); itmain++) {
		for (ittop = p.alltop().begin(); ittop != p.alltop().end(); ittop++) {
			if (ittop->getColor() == itmain->getColor()
					&& ittop->getNumero() >= itmain->getNumero()) {
				move = index;
			}
		}
		index++;
	}
	if (move < 0) {
		return rand() % index;
	}
	return move;
}

bool Joueur::peutJouer(Plateau p) {
	vector<Carte> lol = p.alltop();
	vector<Carte>::iterator itman;
	vector<Carte>::iterator itman2;
	for (itman = lol.begin(); itman != lol.end(); itman++) {
		for (itman2 = this->main.begin(); itman2 != this->main.end();
				itman2++) {
			if (itman->getColor() == itman2->getColor()
					&& itman->getNumero() + 1 == itman2->getNumero()) {
				return true;
			}
		}
	}
	return false;
}

int Joueur::JouerCoup(Plateau p) {
	vector<Carte> lol = p.alltop();
	vector<Carte>::iterator itman;
	vector<Carte>::iterator itman2;
	int compteur = 0;
	for (itman = lol.begin(); itman != lol.end(); itman++) {
		compteur = 0;
		for (itman2 = this->main.begin(); itman2 != this->main.end();
				itman2++) {
			if (itman->getColor() == itman2->getColor()
					&& itman->getNumero() + 1 == itman2->getNumero()) {
				return compteur;
			}
			compteur++;
		}
	}
	return compteur;

}

int Joueur::DefausseIA3(Plateau p) {
	vector<Carte> lel = p.defausse;
	vector<Carte> lil = p.alltop();
	Couleur c("blanc");
	Carte n(c, 0);
	lel.push_back(n);
	vector<Carte>::iterator itman;
	vector<Carte>::iterator itman2;
	int compteur = 0;
	for (itman = this->main.begin(); itman != this->main.end(); itman++) {
		for (itman2 = lil.begin(); itman2 != lil.end(); itman2++) { // d�file all tops
			if (itman->getColor() == itman2->getColor()
					&& itman->getNumero() <= itman2->getNumero()) { //Si la carte a ete deja jou�
				return compteur;
			}
			break;
		}
		for (itman2 = lel.begin(); itman2 != lel.end(); itman2++) { // D�file la defausse
			if (!(itman->getColor() == itman2->getColor()
					&& itman->getNumero() == itman2->getNumero())) {
				if (itman->getNumero() != 5) {
					return compteur;
				}

			}
			break;
		}

		compteur++;
	}
	return compteur;

}

