/*
 * Fonction.h
 *
 *  Created on: 21 mars 2017
 *      Author: if00777
 */
#include "Fonction.h"

// vérifie si la carte est posable ou non sur le plateau

static int peutPoser2 (vector<double> exemple){

	double cCarte=exemple[0];
	double nCarte=exemple[1];
	double nFeu1=exemple[2];
	double nFeu2=exemple[3];
	double nFeu3=exemple[4];
	double nFeu4=exemple[5];
	double nFeu5=exemple[6];

	if(cCarte == 0 && nCarte == (nFeu1+1)) return 1;
	if(cCarte == 1 && nCarte == (nFeu2+1)) return 1;
	if(cCarte == 2 && nCarte == (nFeu3+1)) return 1;
	if(cCarte == 3 && nCarte == (nFeu4+1)) return 1;
	if(cCarte == 4 && nCarte == (nFeu5+1)) return 1;
	return 0;
	vector<double> poids;
	poids.push_back(0);
	poids.push_back(-1);

	vector<double> in;
	in.push_back(0);
	in.push_back(0);

	vector<double> in2;
	in2.push_back(0);
	in2.push_back(1);

	vector<double> in3;
	in3.push_back(1);
	in3.push_back(0);

	vector<double> in4;
	in4.push_back(1);
	in4.push_back(1);

	Reseau r = Reseau(2, 2, 1, 1);
	r.affiche();

	r.backprop(in, 0);

	cout << endl;

	r.affiche();

	cout << endl;

	r.backprop(in2,1);

	cout << endl;

	r.affiche();

	r.getDelta(r.sortie.neurones.at(0));
	cout << endl;
	r.getDelta(r.cacher.neurones.at(0));
	r.getDelta(r.cacher.neurones.at(1));

	system("PAUSE"); // Juste pour faire une pause au debut pour noter l'equation
	int i = 0;
	double signal;

	double seuil = 0.00001;


	while (i < 5000) {
		cout << " Mal classe " << endl;
		signal = r.backprop(in, 0);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}
		r.affiche();

		cout << " Mal classe " << endl;
		signal = r.backprop(in2, 1);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}
		r.affiche();

		cout << " Bien classe " << endl;
		signal = r.backprop(in3, 1);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}
		r.affiche();

		cout << " Bien classe " << endl;
		signal = r.backprop(in4, 0);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}

		r.affiche();
		cout << "Nombre d'iteration : i = " << i << endl;
		i++;


	}
	cout << signal << endl;

	r.getDelta(r.sortie.neurones.at(0));
	cout << endl;
	r.getDelta(r.cacher.neurones.at(0));
	r.getDelta(r.cacher.neurones.at(1));
	r.input({1,0});
	r.transfert();
	cout << r.sortie.neurones[0].getValeur() << endl;


}


// vérifie si la carte est posable ou non sur un feu

static int peutPoser(vector<double> exemple){
	double cCarte=exemple[0];
	double nCarte=exemple[1];
	double cFeu=exemple[2];
	double nFeu=exemple[3];
	if(cCarte==cFeu && nCarte == (nFeu+1)) return 1;
	return 0;
}


int Fonction::reseaupeutposer1(){


	//creation des exemples de la fonction pour poser les cartes



	//creation de la liste des exemples
	vector< vector<double> > exemplesPeutPoser;

	//couleur de la carte en premier
	for(double i=0;i<5;i++){
		//hauteur de la carte
		for(double j=1;j<6;j++){
			//couleur du feu
			for(double k=0;k<5;k++){
				//hauteur du feu
				for(double l=0;l<5;l++){
					exemplesPeutPoser.push_back({i,j,k,l});
				}
			}
		}
	}

	//creation de la liste des targets
	vector<double> targetPeutposer;
	vector<vector<double>> valide;
	vector<vector<double>> invalide;
	vector<vector<double>>::iterator itExemple;

	for(itExemple=exemplesPeutPoser.begin();itExemple!=exemplesPeutPoser.end();itExemple++){
		targetPeutposer.push_back(peutPoser(*itExemple));
		if(peutPoser(*itExemple)){
			valide.push_back(*itExemple);
		}
		else invalide.push_back(*itExemple);
	}

	cout << "nombre d'exemples " << exemplesPeutPoser.size() << endl;
	int aleavalide;
	int aleainvalide;
	Reseau r = Reseau(4,4,1,0.5);
	double signal;

	for(int j = 0;j<1000;j++){
	for(int i=0;i<625;i++){

				r.backprop(exemplesPeutPoser[i],targetPeutposer[i]);
//				aleavalide = rand()%valide.size();
//				r.backprop(exemplesPeutPoser[aleavalide],targetPeutposer[aleavalide]);
//				aleainvalide = rand()%invalide.size();
//				r.backprop(exemplesPeutPoser[aleainvalide],targetPeutposer[aleainvalide]);
	}
	}
	int count = 0;
	for(unsigned int i=0;i<valide.size();i++){
		r.input(valide[i]);
		r.transfert();
		if (r.sortie.neurones[0].getValeur()>=0.5) count++;
	}
	cout << "nombre de bien classé positif : " << count << endl;

	count =0;
	for(unsigned int i=0;i<invalide.size();i++){
		r.input(invalide[i]);
		r.transfert();
		if (r.sortie.neurones[0].getValeur()<=0.5) count++;
	}

	cout << "nombre de bien classé négatif : " << count << endl;



	//retourne 0 si la fonction a bien été executer
	return 0;
}


/**
 * Apprentissage pour poser une carte sur le plazteau de jeu
 */
int Fonction::reseaupeutposer2(int sizeAp,int sizeTest){

	vector< vector<double> > exemple2;
	vector<double> target2;

	//céation d'exemple de façon random

	double cc,nc,nf1,nf2,nf3,nf4,nf5;
	srand(0);

	for(int i =0;i<sizeAp;i++){
		cc = rand()%5;
		nc = (rand()%5+1);

		nf1=rand()%5;

		nf2=rand()%5;

		nf3=rand()%5;

		nf4=rand()%5;

		nf5=rand()%5;

		exemple2.push_back({cc,nc,nf1,nf2,nf3,nf4,nf5});
		target2.push_back(peutPoser2({cc,nc,nf1,nf2,nf3,nf4,nf5}));

	}

	vector<vector<double>> testExemple;
	vector<double> testTarget;

	for(int i =0;i<sizeTest;i++){

		cc = rand()%5;
		nc = (rand()%5+1);

		nf1=rand()%5;

		nf2=rand()%5;

		nf3=rand()%5;

		nf4=rand()%5;

		nf5=rand()%5;

		testExemple.push_back({cc,nc,nf1,nf2,nf3,nf4,nf5});
		testTarget.push_back(peutPoser2({cc,nc,nf1,nf2,nf3,nf4,nf5}));

		// création du reseau de neurones a 4 couches

		Reseau r = Reseau(12,20,1,0.5);

		for(unsigned int i = 0;i< exemple2.size();i++){
			r.backprop(exemple2[i],target2[i]);
		}

		//test des exemples
		int count = 0;
		int countpos =0;
		int countn=0;

		for(unsigned int i = 0 ; i < testExemple.size() && i < testTarget.size() ; i++ ){
			r.input(testExemple[i]);
			r.transfert();
			if(r.sortie.neurones[0].getValeur() >= 0.5 && testTarget[i]==1){
				count ++;
			}
			else if(r.sortie.neurones[0].getValeur() <= 0.5 && testTarget[i]==0){
				count ++;
			}

		}

		cout << "nombre d'exemples bien classés" << count <<  "sur" << sizeTest << " exemples "<<endl;
	}

	//retourne 0 si la fonction a été correctement executer
	return 0;
}

int Fonction::ReseauPorte(){
	vector<double> poids;
	poids.push_back(0);
	poids.push_back(-1);

	vector<double> in;
	in.push_back(0);
	in.push_back(0);

	vector<double> in2;
	in2.push_back(0);
	in2.push_back(1);

	vector<double> in3;
	in3.push_back(1);
	in3.push_back(0);

	vector<double> in4;
	in4.push_back(1);
	in4.push_back(1);

	Reseau r = Reseau(2, 2, 1, 1);
	r.affiche();

	r.backprop(in, 0);

	cout << endl;

	r.affiche();

	cout << endl;

	r.backprop(in2,1);

	cout << endl;

	r.affiche();

	r.getDelta(r.sortie.neurones.at(0));
	cout << endl;
	r.getDelta(r.cacher.neurones.at(0));
	r.getDelta(r.cacher.neurones.at(1));

	system("PAUSE"); // Juste pour faire une pause au debut pour noter l'equation
	int i = 0;
	double signal;

	double seuil = 0.00001;


	while (i < 5000) {
		cout << " Mal classe " << endl;
		signal = r.backprop(in, 0);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}
		r.affiche();

		cout << " Mal classe " << endl;
		signal = r.backprop(in2, 1);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}
		r.affiche();

		cout << " Bien classe " << endl;
		signal = r.backprop(in3, 1);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}
		r.affiche();

		cout << " Bien classe " << endl;
		signal = r.backprop(in4, 0);
		if (signal < seuil && signal > -seuil) {
			cout << "Nombre d'iteration : i = " << i << endl;
			cout << "Signal d'erreur : " << signal << endl;
			break;
		}

		r.affiche();
		cout << "Nombre d'iteration : i = " << i << endl;
		i++;


	}
	cout << signal << endl;

	r.getDelta(r.sortie.neurones.at(0));
	cout << endl;
	r.getDelta(r.cacher.neurones.at(0));
	r.getDelta(r.cacher.neurones.at(1));
	r.input({1,0});
	r.transfert();
	cout << r.sortie.neurones[0].getValeur() << endl;


	// retourne 0 si le programme a bien été executé
	return 0;

}

