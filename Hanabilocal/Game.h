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
	vector<Joueur> joueurs;
	int nombre_joueur;
	int nbcartesmain;
public :
	Game();
	Game(int nb_joueur,int nbcartes,int seed, bool save, bool ia);
	Carte piocher();
	void defausser();
	void poser();
	void afficherJoueur();
	vector<int> gameState();

	list<int> toBool(int n){
		list<int> v;
		while(n != 0){
			if(n%2 == 0){
				v.push_front(0);
			}
			else v.push_front(1);
			n=n/2;
		}
		return v;
	}



};




#endif /* GAME_H_ */
