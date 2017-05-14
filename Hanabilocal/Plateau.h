/*
 * Plateau.h
 *
 *  Created on: 20 févr. 2017
 *      Author: ubuntu
 */
#ifndef PLATEAU_H_
#define PLATEAU_H_
#include <list>
#include <stack>
#include <vector>
#include "Deck.h"
#include<fstream>
#include "Fonctions.h"

using namespace std;

vector<int> listToVector(list<int> liste);
vector<int> toBool(int n,int nbBits);
vector<int> carteToBool(Carte c);

class Plateau{
private :
	int JetonRouge;
	//int JetonBleu = 8;
	bool jeu_fini;

	stack<Carte> jaunes;
	stack<Carte> rouges;
	stack<Carte> verts;
	stack<Carte> blancs;
	stack<Carte> bleus;



public :
	Deck paquet;
	vector<Carte> defausse;


	void poser(Carte c);
	Carte piocher();
	Plateau();
	Plateau(int seed);
	~Plateau();
	void affiche();
	void affiche2D();
	void fini();
	vector<Carte> distribution(int nbcartes);
	int calculpoint();
	void afficheDefausse();
	void defausser(Carte c);
	vector<int> getState();
	vector<double> resumedefausse();
	vector<double> getFeu();
	vector<int> resumeDefausse2();

	int sizePaquet(){
		return paquet.taille();
	}

	void setJetonRouge(int jetonRouge = 3) {
		JetonRouge = jetonRouge;
	}

	bool isJeuFini() const {
		return jeu_fini;
	}

	void setJeuFini(bool jeuFini) {
		jeu_fini = jeuFini;
	}

	vector<Carte> alltop();
	vector<double> tops();

	int getJetonRouge() const {
		return JetonRouge;
	}

	const stack<Carte>& getBlancs() const {
		return blancs;
	}

	void setBlancs(const stack<Carte>& blancs) {
		this->blancs = blancs;
	}

	const stack<Carte>& getBleus() const {
		return bleus;
	}

	void setBleus(const stack<Carte>& bleus) {
		this->bleus = bleus;
	}

	const vector<Carte>& getDefausse() const {
		return defausse;
	}

	void setDefausse(const vector<Carte>& defausse) {
		this->defausse = defausse;
	}

	const stack<Carte>& getJaunes() const {
		return jaunes;
	}

	void setJaunes(const stack<Carte>& jaunes) {
		this->jaunes = jaunes;
	}

	const Deck& getPaquet() {
		return paquet;
	}

	void setPaquet(const Deck& paquet) {
		this->paquet = paquet;
	}

	const stack<Carte>& getRouges() const {
		return rouges;
	}

	void setRouges(const stack<Carte>& rouges) {
		this->rouges = rouges;
	}

	const stack<Carte>& getVerts() const {
		return verts;
	}

	void setVerts(const stack<Carte>& verts) {
		this->verts = verts;
	}


};



#endif /* PLATEAU_H_ */
