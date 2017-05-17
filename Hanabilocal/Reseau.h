/*
 * Reseau.h
 *
 *  Created on: 28 mars 2017
 *      Author: ubuntu
 */

#ifndef RESEAU_H_
#define RESEAU_H_
#define NBCOUCHE 3
#include <vector>
#include <string>
#define BORNESUP 1
#define BORNEINF -1
#define MAX 200
#define PAS  0.2
#define SEED 1
using namespace std;



class Reseau{

private :
	int taille[NBCOUCHE];
	double out[NBCOUCHE][MAX];
	double poids[NBCOUCHE-1][MAX*MAX];
	double signal[NBCOUCHE-1][MAX];


public :
	Reseau();
	~Reseau(){};
	Reseau(vector <int> cou);
	Reseau(vector <int> couche, vector <double> pds);
	void affiche();
	void afficheT();
	void input(vector<double> input);
	void transfert();
	void transfert2();
	double backprop(vector <double> in, double target);
	double signalErreur(double target, double out);
	int maxTaille();
	double sigmoide(double);
	void getDelta();
	void getDelta(int i, int j);
	void getDelta2();
	double majPoid(double signal, double out);
	double getSortie(){
		return out[0][0];
	}
	vector <double> getPoids();

	void savePoidsDansTxt(string chemin);
	vector <double> PoidsTxtDansVector(string chemin);

	template<class T> T abs(T nbr) {
	    if(nbr >= 0) return nbr;
	    else        return -nbr;
	}



};



#endif /* RESEAU_H_ */
