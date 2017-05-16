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
#include "Aprenant.h"

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
	~Game(){};
	Game(const Game & g);
	Game(int nb_joueur,int nbcartes,int seed, bool save, bool ia);
	Carte piocher();
	void defausser();
	void poser();
	void afficherJoueur();
	vector<double> gameState();
	vector<vector<double>> nextGameState();
	void jouerCoup(int action,int carte,int joueur);
};




#endif /* GAME_H_ */
