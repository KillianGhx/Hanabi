/*
 * Game.cpp
 *
 *  Created on: 24 fÃ©vr. 2017
 *      Author: ubuntu
 */
#include "Game.h"

Game::Game() {
	nbcartesmain = 0;
	cout << "rentrer le nombre de cartes par main" << endl;
	cin >> nbcartesmain;
	nombre_joueur = 0;
	while (nombre_joueur < 2) {
		cout << "entrer le nombre de joueurs : " << endl;
		cin >> nombre_joueur;
	}
	for (int i = 0; i < nombre_joueur; i++) {
		joueurs.push_back(Joueur(i));
	}
	plateau = Plateau();

}

Game::Game(int nb_joueur, int nombrecarte, int seed, bool save, bool ia) {

	//Initialisation des 5 joueurs
	vector<Carte> mainDeLouis;
	Joueur louis = Joueur("Louis", 1, ia, mainDeLouis); // TRUE = IA, FALSE = HUMAN
	vector<Carte> mainDeKillian;
	Joueur killian = Joueur("Killian", 2, ia, mainDeKillian);
	vector<Carte> mainDeHamid;
	Joueur hamid = Joueur("Hamid", 3, ia, mainDeHamid);
	vector<Carte> mainDeMargot;
	Joueur margot = Joueur("Margot", 4, ia, mainDeMargot);
	vector<Carte> mainDeDavid;
	Joueur david = Joueur("David", 5, ia, mainDeDavid);

	if (nb_joueur == 2) {
		joueurs.push_back(louis);
		joueurs.push_back(killian);
	}

	if (nb_joueur == 3) {
		joueurs.push_back(louis);
		joueurs.push_back(killian);
		joueurs.push_back(hamid);
	}

	if (nb_joueur == 4) {
		joueurs.push_back(louis);
		joueurs.push_back(killian);
		joueurs.push_back(hamid);
		joueurs.push_back(margot);
	}

	if (nb_joueur == 5) {
		joueurs.push_back(louis);
		joueurs.push_back(killian);
		joueurs.push_back(hamid);
		joueurs.push_back(margot);
		joueurs.push_back(david);
	}
	//Init des variables
	nbcartesmain = nombrecarte;
	nombre_joueur = nb_joueur;
	plateau = Plateau(seed);

	//Cr�ations des variables utilis�s
	int num_carte; // Celle qui va etre jou�
	int choix = 0;
	int countBeforeEnd = joueurs.size() - 1; // D�compte lorsque que la pioche est vide
	vector<Joueur>::iterator it;
	vector<Joueur>::iterator it2;
	for (it = joueurs.begin(); it != joueurs.end(); it++) {
		it->main = plateau.distribution(nombrecarte);
	} // Distribution des cartes pour chaque joueurs

	while (plateau.getJetonRouge() > 0 && !plateau.isJeuFini()
			&& countBeforeEnd > 0) { //Boucle while pour le d�roulement de la partie

		for (it = joueurs.begin(); it != joueurs.end(); it++) { // Boucle pour chaque joueurs
			plateau.affiche2D();
			for (it2 = joueurs.begin(); it2 != joueurs.end(); it2++) {
				it2->afficher(); // Affichage de la main de chaque joueurs
				cout << endl;
			}
			cout << "Tour de " << it->getNom() << endl << endl;
			while (choix != 1 && choix != 2 && choix != 3) { // Boucle tant que choix est incorrecte
				cout
						<< "Jouer (1) ou defausser (2) une carte ? Ou afficher la defausse (3) ? "
						<< endl;
				if (it->isIsIa()) { // Si IA
					//choix = it->IArandomchose(); // IA LVL1
					if(it->peutJouer(this->plateau)){
						choix = 1;
					}
					else {
						choix = 2;
					}
					cout << "Choix de l'IA : " << choix << endl;
				} else { // Si pas d'IA
					cin >> choix;
				}
			}

			switch (choix) {
			case 1: //Jouer une carte

				if (it->isIsIa()) { //Si IA
					//num_carte = it->IArandomnumerocarte(nombrecarte); // IA LVL 1
					num_carte=it->JouerCoup(this->plateau);
					cout << "Carte jouer par l'IA : " << num_carte << endl;
				} else { // Pas d'IA
					do { // Verifie que la carte entre est valable
						cout << "Quel carte jouer ? ";
						cin >> num_carte;
					} while (num_carte >= nombrecarte);
				}
				plateau.poser(it->getMain().at(num_carte)); //Poser la carte sur le plateau
				it->jeterCarte(num_carte); // jeter la carte en question de la main du joueur
				if (plateau.paquet.taille() != 0)
					it->main.push_back(plateau.piocher());
				else
					countBeforeEnd--;
				break;

			case 2: // Defausser une carte

				if (it->isIsIa()) { // Avec IA
					//num_carte = it->IArandomnumerocarte(nombrecarte); // IA LVL 1 && 2
					num_carte = it->DefausseIA3(this->plateau); // IA LVL 3
					cout << "Carte defausser par l'IA : " << num_carte << endl;

				} else { //Pas d'IA
					do { // Verifie que la carte entre est valable
						cout << "Quel carte defausser ? ";
						cin >> num_carte;
					} while (num_carte >= nombrecarte);

				}
				plateau.defausser(*(it->main.begin() + num_carte));
				it->jeterCarte(num_carte);
				if (plateau.paquet.taille() != 0)
					it->main.push_back(plateau.piocher());
				else
					countBeforeEnd--;
				break;

			case 3: //Affiche defausse
				plateau.afficheDefausse();
				it--; //Pour revenir au joueur precedent
				break;

			}

			if (!(plateau.getJetonRouge() > 0 && !plateau.isJeuFini()
					&& countBeforeEnd > 0)) { // SI LE JEU SE TERMINE AVANT LA FIN DE LA BOUCLE FOR QUI PARCOURT TOUT LES JOUEURS
				break;
			}
			choix = 0;
			plateau.fini();

		}
	}

	cout << "Jeu fini : score : " << plateau.calculpoint() << endl;
	if (save) {
		ofstream fichierSauvegarde(
				"/home/ubuntu/git/Hanabi2/Hanabilocal/sauvegarde/IA_LVL2/Save_score_lvl2_2J_3C.txt",
				ios::app); //T'as juste a mettre le chemin vers la sauvegarde // le ios::app pour ecrire � la suite
		fichierSauvegarde << plateau.calculpoint() << endl;
		fichierSauvegarde.close();

	}

}

Carte Game::piocher() {
	return plateau.piocher();
}

void Game::afficherJoueur() {
	vector<Joueur>::iterator it;
	for (it = joueurs.begin(); it != joueurs.end(); it++) {
		it->afficher();
	}
}

vector<int> Game::gameState(int indexJoueur){

	vector<int> res;
	res = this->plateau.getState();
	vector<Carte>::iterator it;
	vector<int> tmp;
	for (it = joueurs[indexJoueur].getMain().begin();it != joueurs[indexJoueur].getMain().end(); it++){
		tmp=carteToBool(*it);
		res.insert(res.begin(),tmp.begin(),tmp.end());
	}
	return res;

}
