/*
 * Game.h
 *
 *  Created on: 24 févr. 2017
 *      Author: ubuntu
 */

#ifndef GAME_H_
#define GAME_H_
#include "Plateau.h"
#include "Joueur.h"

class Game{
private:
	Plateau plateau;
	int nombre_joueur;
	vector<Joueur> joueurs;
	int nbcartesmain;
	int compteurFin;
	int indexJoueurCourant;
public :
	Game();
	Game(int joueur,int seed);
	~Game(){};
	Game(const Game & g);
	Game(int nb_joueur,int nbcartes,int seed, bool save, bool ia);
	Carte piocher();
	void defausser();
	void poser();
	void afficherJoueur();
	Game(int n);
	vector<double> gameState();
	vector<vector<double>> nextGameState();
	void jouerCoup(int action,int carte);
	void afficheGS(vector<double> gs);
};




#endif /* GAME_H_ */
