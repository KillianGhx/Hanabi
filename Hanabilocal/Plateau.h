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

using namespace std;

vector<int> listToVector(list<int> liste){
	vector<int> res;
	list<int>::iterator it;
	for (it = liste.begin();it != liste.end();it++){
		res.push_back(*it);
	}
	return res;
}

vector<int> toBool(int n){
	list<int> v;
	while(n != 0){
		if(n%2 == 0){
			v.push_front(0);
		}
		else v.push_front(1);
		n=n/2;
	}
	return listToVector(v);
}

vector<int> carteToBool(Carte c){
	vector<int> res;
	vector<int> tmp;
	res=toBool(c.getColor().toInt());
	tmp=toBool(c.getNumero());
	res.insert(res.end(),tmp.begin(),tmp.end());
	return res;

}

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
