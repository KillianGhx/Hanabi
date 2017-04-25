/*
 * Reseau.cpp
 *
 *  Created on: 28 mars 2017
 *      Author: ubuntu
 */
#include "Reseau.h"
#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>
#include <math.h>

using namespace std;

Reseau::Reseau() {
	int n;
	srand(SEED);
	int nbCoucheCacher = 1;
	for (int i = 0; i < NBCOUCHE; i++) {
		if (i == 0) {
			cout << "Entrez le nombre de neurone pour la couche de sortie "
					<< endl;
		} else if ((i + 1) == NBCOUCHE) {
			cout << "Entrez le nombre de neurone pour la couche d'entrée  "
					<< endl;
		} else {
			cout << "Entrez le nombre de neurone pour la couche caché  "
					<< nbCoucheCacher << endl;
			nbCoucheCacher++;
		}
		cin >> n;
		taille[i] = n;
	}
	int index = 0;
	for (int i = 0; i < NBCOUCHE; i++) {
		for (int j = 0; j < taille[index]; j++) {
			out[i][j] = 0;
		}
		index++;
	}
	index = 0;
	for (int i = 0; i < NBCOUCHE - 1; i++) {
		for (int j = 0; j < (taille[index] * taille[index + 1] + taille[index]);j++) {
			poids[i][j] = (rand()%(1000*(BORNESUP-(BORNEINF))+1))/1000.+(BORNEINF);
		}
		index++;
	}
	for(int i=0 ; i < NBCOUCHE - 1; i++){
		for(int j = 0; j < MAX; j ++){
			signal[i][j]=0;
		}
	}

}

Reseau::Reseau(vector <int> in) {
	srand(SEED);
	for (int i = 0; i < NBCOUCHE; i++) {
		taille[i] = in.at(i);
	}
	int index = 0;
	for (int i = 0; i < NBCOUCHE; i++) {
		for (int j = 0; j < taille[index]; j++) {
			out[i][j] = 0;
		}
		index++;
	}
	index = 0;
	for (int i = 0; i < NBCOUCHE - 1; i++) {
		for (int j = 0; j < (taille[index] * taille[index + 1] + taille[index]);j++) {
			poids[i][j] = (rand()%(1000*(BORNESUP-(BORNEINF))+1))/1000.+(BORNEINF);
		}
		index++;
	}
	for(int i=0 ; i < NBCOUCHE - 1; i++){
		for(int j = 0; j < MAX; j ++){
			signal[i][j]=0;
		}
	}

}

Reseau::Reseau(vector <int> couche, vector <double> pds) {
	for (int i = 0; i < NBCOUCHE; i++) {
		taille[i] = couche.at(i);
	}
	int index = 0;
	for (int i = 0; i < NBCOUCHE; i++) {
		for (int j = 0; j < taille[index]; j++) {
			out[i][j] = 0;
		}
		index++;
	}
	index = 0;
	int compteur=0;
	for (int i = 0; i < NBCOUCHE - 1; i++) {
		for (int j = 0; j < (taille[index] * taille[index + 1] + taille[index]);j++) {
			poids[i][j] = pds.at(compteur);
			compteur++;
		}
		index++;
	}
	for(int i=0 ; i < NBCOUCHE - 1; i++){
		for(int j = 0; j < MAX; j ++){
			signal[i][j]=0;
		}
	}
}

int Reseau::maxTaille() {
	int max = 0;
	for (int i = 0; i < NBCOUCHE; i++) {
		if (max < taille[i]) {
			max = taille[i];
		}
	}

	return max;
}

void Reseau::afficheT() {
	cout << "Affichage Taille : " << endl;
	for (int i = 0; i < NBCOUCHE; i++) {
		cout << "taille[" << i << "] = " << taille[i] << endl;
	}
	cout << "Affichage Output : " << endl;
	int index = 0;
	for (int i = 0; i < NBCOUCHE; i++) {
		for (int j = 0; j < taille[index]; j++) {
			cout << "output [" << i << "][" << j << "] = " << out[i][j] << endl;
		}
		index++;
	}
	index = 0;
	cout << "Affichage des poids : " << endl;
	for (int i = 0; i < NBCOUCHE - 1; i++) {
		for (int j = 0; j < (taille[index] * taille[index + 1] + taille[index]);
				j++) {
			cout << "poids [" << i << "][" << j << "] = " << poids[i][j]
					<< endl;
		}
		index++;
	}

}

void Reseau::input(vector<double> input) {
	for (int i = 0; i < taille[NBCOUCHE - 1]; i++) {
		out[NBCOUCHE - 1][i] = input[i];
	}
}

void Reseau::affiche() {
	//Ca marche mais je sais pas pkoi lol
	cout << endl;
	int indexT = 0;
	int nbCC = 1;
	int index = 0;
	int indexCouche = 1;
	int indexPds=1;
	int indexPds2=0;
	cout << "Affichage du reseau de neurone : " << endl;
	cout << "Nombre de couche : " << NBCOUCHE << endl;
	for (int i = 0; i < NBCOUCHE; i++) {
		if (i == 0) {
			cout << "Nombre e neurone dans la couche de sortie : "
					<< taille[indexT] << endl;
			indexT++;
			int indexX=0;
			for (int j = 0; j < indexCouche; j++) {
				for (int k = 0; k < taille[index]; k++) {
					cout << "Valeur du neurone : " << out[j][k] << endl;
					for(int h=0;h < indexPds ; h++){
						for(int g = 0; g < taille[indexPds2+1]+1; g++){
							if (g==0){
								cout << "Valeur du biais : " << poids[h][indexX] << ", valeurs des poids : ";
								indexX++;
							}else{
								cout << poids[h][indexX] << " " ;
								indexX++;
							}

						}
						cout << endl;
					}
				}
			}
			index++;
			indexCouche++;
			indexPds2++;
			indexPds++;
			cout << endl;
		} else if ((i + 1) == NBCOUCHE) {
			cout << "Nombre de neurone dans la couche d'entre : "
					<< taille[indexT] << endl;
			indexT++;
			for (int j = indexCouche-1; j < indexCouche; j++) {
				for (int k = 0; k < taille[index]; k++) {
					cout << "Valeur du neurone : " << out[j][k] << endl;

				}
			}
			index++;
			indexCouche++;
		} else {
			cout << "Nombre de neurone dans la couche cache  " << nbCC << " : "
					<< taille[indexT] << endl;
			indexT++;
			nbCC++;
			int indexX=0;
			for (int j = indexCouche-1; j < indexCouche; j++) {
				for (int k = 0; k < taille[index]; k++) {
					cout << "Valeur du neurone : " << out[j][k] << endl;
					for(int h=indexPds-1;h < indexPds ; h++){
						for(int g = 0; g < taille[indexPds2+1]+1; g++){
							if(g==0){
								cout << "Valeur du biais : " << poids[h][indexX] << ", valeurs des poids : ";
								indexX++;
							}else{
								cout << poids[h][indexX] << " " ;
								indexX++;
							}

						}
						cout << endl;
					}

				}
			}
			index++;
			indexCouche++;
			indexPds2++;
			indexPds++;
		}
	}

}

void Reseau::transfert(){
	int indexCouche = NBCOUCHE - 2; // On va defiler out et on s'arretera lorsqu'il atteindra la sortie
	int memo;
	while( indexCouche >= 0 ){
		int indexPds=0;
		int k=0;
		for(int i=0; i < taille[indexCouche]; i++){
			for(int j=indexPds; j < (taille[indexCouche+1]+1)+indexPds ; j++  ){
				if((j%(taille[indexCouche+1]+1)) == 0){ //Alors c'est le biais
					out[indexCouche][i] = poids[indexCouche][j];
				}
				else{
					out[indexCouche][i] += poids[indexCouche][j] * out[indexCouche+1][k];
					k++;
				}
				memo=j;
			}
			out[indexCouche][i] = sigmoide(out[indexCouche][i]);
			k=0;
			indexPds=memo+1;
		}
		indexCouche--;
	}
}

double Reseau::sigmoide(double val){
		return (1/(1+exp(-val)));
	}

void Reseau::getDelta(){
	int j = taille[1]+1;
	for(int i=0; i < j; i++){
		switch (i) {
		case 0:
			cout << "Delta = ("<< poids[0][i] <<") ";
			break;
		case 1:
			cout << "+ (" << poids[0][i] << ") * x ";
			break;
		case 2:
			cout << "+ (" << poids[0][i] << ") * y ";
			break;
		case 3:
			cout << "+ (" << poids[0][i] << ") * z ";
			break;
		}
	}
	cout << endl;
}

void Reseau::getDelta2(){ // MARCHE QUE POUR 2 INCONNU CAD RELIER A 2 NEURONES
	cout << " y = - ( " << poids[0][1] << " / " << poids[0][2] << ") * x - ( " << poids[0][0] << " / " << poids[0][2] << ")" <<endl;
}

void Reseau::getDelta(int i, int j){ // MARCHE QUE POUR 2 INCONNU CAD RELIER A 2 NEURONES
	int h = (j * (taille[i+1] + 1));
	cout << " y = - ( " << poids[i][h+1] << " / " << poids[i][h+2] << ") * x - ( " << poids[i][h+0] << " / " << poids[i][2] << ")" <<endl;
}

double Reseau::signalErreur(double target, double out) {
	return (target - out) * (out) * (1 - out);
}

double Reseau::majPoid(double signal, double out) {
	return PAS * signal * out;
}


double Reseau::backprop(vector <double> in, double target){
	double erreur;
	double somme;
	int indexPds;
	int memo;
	int indexCouche=0;
	this->input(in);
	this->transfert();
	int memoPds=0;
	for (int nbE=0;nbE < taille[0]; nbE++) { //Couche d'entree
		signal[0][nbE] = signalErreur(target, out[indexCouche][nbE]);
//		cout << "Signal d'erreur : " << signal[0][nbE] << endl;
		int memoPds2= memoPds;
		for (int i = memoPds2; i < (taille[indexCouche + 1] + 1)+memoPds2; i++) { // Mise a jour des poids;
			if (i % (taille[indexCouche + 1] + 1) == 0) { // Si c'est le biais
				poids[indexCouche][i] += majPoid(signal[indexCouche][nbE], 1);
			} else {
				poids[indexCouche][i] += majPoid(signal[indexCouche][nbE], out[indexCouche + 1][i-1-memoPds2]);
			}
		memoPds++;
		}
	}
	indexCouche++; //On passe a la couche suivante

	for (int c = 0; c < (NBCOUCHE - 2); c++) { // Boucle pour les couches cachées
		indexPds=0;
		for (int j = 0; j < taille[indexCouche]; j++) { // Boucle pour le nb de neurone dans la couche cache
			signal[indexCouche][j] = out[indexCouche][j] * (1 - out[indexCouche][j]);
			somme = 0;
			for (int i = 0; i < taille[indexCouche - 1]; i++) { // Boucle nombre de connexion entrante
				somme +=  signal[indexCouche-1][i] * poids[indexCouche - 1][(i*(taille[indexCouche]+1))+1+j]; //avant poids[indexCouche - 1][i+j+1]
			}
			signal[indexCouche][j] *= somme;
			memo=indexPds;
			for(int i=memo; i < (taille[indexCouche+1]+1)+memo; i++){ // boucle pour les nombre de poids a changer
				if(i%(taille[indexCouche+1]+1)==0){
					poids[indexCouche][i] += majPoid(signal[indexCouche][j], 1);
				}else{
					poids[indexCouche][i] += majPoid(signal[indexCouche][j], out[indexCouche+1][i-1-memo]);
				}
				indexPds++;
			}
		}
	indexCouche++; //On passe a la couche suivante
	}
	erreur = abs(out[0][0] - target);
	return erreur;
}

