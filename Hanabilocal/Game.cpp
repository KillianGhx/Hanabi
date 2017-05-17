/*
 * Game.cpp
 *
 *  Created on: 24 fÃ©vr. 2017
 *      Author: ubuntu
 */
#include "Game.h"
#include "Aprenant.h"


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
	this->compteurFin = this->nombre_joueur;
	this->indexJoueurCourant =0;

}


Game::Game(const Game &g){
	this->compteurFin=g.compteurFin;
	this->indexJoueurCourant=g.indexJoueurCourant;
	this->nombre_joueur=g.nombre_joueur;
	this->joueurs=g.joueurs;
	this->nbcartesmain=g.nbcartesmain;
	this->plateau=g.plateau;
}

Game::Game(int n,int seed){

	bool affiche=false;
	vector<Joueur>::iterator it;
	vector<int> choix;
	Joueur *killian;
	Joueur *louis;
	Aprenant *ap = new Aprenant({1,80,93});
	srand(seed);

	for (int i = 0;i<5000;i++){
		cout << "Iteration : " << i << endl;
		vector<Carte> main;

		//************************* phase d'initialisation*****************************

		vector<vector<double>> sauvegarde;
		this->nombre_joueur = 2;
		this->compteurFin = this->nombre_joueur;
		this->plateau=Plateau(rand());
		this->indexJoueurCourant=0;
		this->nbcartesmain=4;
		//creation des joueurs

		killian = new Joueur("killian",0,true,main);
		louis = new Joueur("louis",1,true,main);
		main = vector<Carte>();
		killian->setMain(plateau.distribution(nbcartesmain));
		louis->setMain(plateau.distribution(nbcartesmain));

		this->joueurs=vector<Joueur>();
		this->joueurs.push_back(*killian);
		this->joueurs.push_back(*louis);

		//******************************** debut de la partie ************************************
		cout << "debut de la partie" << endl;

		while(this->plateau.getJetonRouge() > 0 && !plateau.isJeuFini() && compteurFin > 0){

			//initialisation de la sauvegarde
			sauvegarde = vector<vector<double>>();
			//On fait joueur tout les joueurs

			for (int x=0;x != this->nombre_joueur;x++){
				sauvegarde.push_back(this->gameState());
				if(affiche){
					plateau.affiche2D();
				}

				choix= ap->previsionCoup(*this);
				//cout << "test" << endl;
				jouerCoup(choix[0],choix[1]);
				plateau.fini();
				if(this->plateau.paquet.taille()== 0){
					compteurFin--;
				}
				//cout << indexJoueurCourant << endl;
			}
		}
		ap->learn(sauvegarde,plateau.calculpoint());
		cout << "Jeu fini : score : " << plateau.calculpoint() << endl;
	}
}

Game::Game(int nb_joueur, int nombrecarte, int seed, bool save, bool ia) {

	for (int n=0;n<50000;n++){
	this->nombre_joueur=nb_joueur;
	this->compteurFin = this->nombre_joueur;
	this->indexJoueurCourant =0;
	vector<int> v;
	v.push_back(1);
	v.push_back(80);
	v.push_back(100);
	Aprenant ap = Aprenant(v);

	//sauvegarde de la partis pour l'apprenant
	vector<vector<double>> sauvegarde;

	//Initialisation des 5 joueurs
	vector<Carte> mainDeLouis;
	Joueur louis = Joueur("Louis", 1, ia, mainDeLouis);
	vector<Carte> mainDeKillian;
	Joueur killian = Joueur("Killian", 2, ia, mainDeKillian);
	vector<Carte> mainDeHamid;
	Joueur hamid = Joueur("Hamid", 3, ia, mainDeHamid);
	vector<Carte> mainDeMargot;
	Joueur margot = Joueur("Margot", 4, ia, mainDeMargot);
	vector<Carte> mainDeDavid;
	Joueur david = Joueur("David", 5, ia, mainDeDavid);

	joueurs = vector<Joueur>();
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
	plateau = Plateau(rand()%10000);

	//Cr�ations des variables utilis�s
	int num_carte; // Celle qui va etre jou�
	int choix = 0;
	int compteurFin = joueurs.size() - 1; // D�compte lorsque que la pioche est vide
	vector<Joueur>::iterator it;
	vector<Joueur>::iterator it2;
	indexJoueurCourant=-1;
	for (it = joueurs.begin(); it != joueurs.end(); it++) {
		indexJoueurCourant++;
		it->main = plateau.distribution(nombrecarte);
	} // Distribution des cartes pour chaque joueurs






	vector<int> coupAprenant;

	//************************************* debut du jeu ************************************************
	while (plateau.getJetonRouge() > 0 && !plateau.isJeuFini()
			&& compteurFin > 0) { //Boucle while pour le d�roulement de la partie
		coupAprenant = ap.previsionCoup(*this);
		indexJoueurCourant=0;
		sauvegarde.push_back(this->gameState());
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
					vector<double> gs;
//					if(it->peutJouer(this->plateau)){
//						choix = 1;
//					}
//					else {
//						choix = 2;
//					}
					choix = coupAprenant[0];
					cout << "Choix de l'IA : " << choix << endl;
				} else { // Si pas d'IA
					cin >> choix;
				}
			}

			switch (choix) {
			case 1: //Jouer une carte

				if (it->isIsIa()) { //Si IA
					//num_carte = it->IArandomnumerocarte(nombrecarte); // IA LVL 1
//					num_carte=it->JouerCoup(this->plateau);
					num_carte=coupAprenant[1];
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
					compteurFin--;
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
					compteurFin--;
				break;

			case 3: //Affiche defausse
				plateau.afficheDefausse();
				it--; //Pour revenir au joueur precedent
				break;

			}
			if (!(plateau.getJetonRouge() > 0 && !plateau.isJeuFini()
					&& compteurFin > 0)) { // SI LE JEU SE TERMINE AVANT LA FIN DE LA BOUCLE FOR QUI PARCOURT TOUT LES JOUEURS
				break;
			}
			choix = 0;
			plateau.fini();
			indexJoueurCourant++;
		}
	}
	ap.learn(sauvegarde,plateau.calculpoint());
	cout << "Jeu fini : score : " << plateau.calculpoint() << endl;
	if (save) {
		ofstream fichierSauvegarde(
				"/home/ubuntu/git/Hanabi2/Hanabilocal/sauvegarde/IA_LVL2/Save_score_lvl2_2J_3C.txt",
				ios::app); //T'as juste a mettre le chemin vers la sauvegarde // le ios::app pour ecrire � la suite
		fichierSauvegarde << plateau.calculpoint() << endl;
		fichierSauvegarde.close();

	}
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

void afficheCarte(Carte c){
	cout << "carte : " ;
	cout << c.getColor().getString() << "  " << c.getNumero() << endl;
}

vector<double> conversion(vector<int> v){
	vector<int>::iterator it;
	vector<double> res;
	for (it = v.begin();it != v.end();it++){
		res.push_back(*it);
	}
	return res;
}

vector<vector<double>> Game::nextGameState(){
	vector<vector<double>> next;
	Game *g;
	vector<double> v;
	for (int action = 1;action<3;action++){
		for( int carte = 0;carte<nbcartesmain;carte++){
			g= new Game(*this);
			g->jouerCoup(action,carte);
			v=g->gameState();
			next.push_back(v);
		}
	}
	return next;
}

void Game::jouerCoup(int action,int indexCarte){

	if(action == 1){
		plateau.poser(joueurs[this->indexJoueurCourant].main[indexCarte]);
		if(plateau.sizePaquet()> 0){
			joueurs[this->indexJoueurCourant].main[indexCarte]=piocher();
		}
	}
	else {
		plateau.defausser(joueurs[this->indexJoueurCourant].main[indexCarte]);
		if(plateau.sizePaquet()> 0){
			joueurs[this->indexJoueurCourant].main[indexCarte]=piocher();
		}
	}
	this->indexJoueurCourant++;
	this->indexJoueurCourant%=2;
}

// Creation de la gameState representant l'etat du jeu en binaire
vector<double> Game::gameState(){

	vector<int> res;
	vector<Carte>::iterator it;
	vector<double>::iterator it2;
	vector<int>::iterator itres;
	vector<int> tmp;
	vector<double> valuedesfeux = this->plateau.getFeu();
	vector<double> carteDouble;
	vector<int> carteDefausse = plateau.resumeDefausse2();
	vector<Carte>::iterator itCarte;
	vector<double> resumedefausse = plateau.resumedefausse();
	vector<double> v;


	// dans un premier temps on enregistre les données du plateau dans res
	res = this->plateau.getState();
	//on enregistre la valeur des feux dans une liste de double pour correcponde aux fonctions de test
//	for(it2 = valuedesfeux.begin();it2 != valuedesfeux.end();it2++){
//		// on insert la valeur des feux sur 3 bits 5 feux * 3 bits 15 bits
//		tmp = toBool(*it2,3);
//		res.insert(res.end(),tmp.begin(),tmp.end());
//	}

	// On enregistre toute les cartes des mains des joueurs (sur 6 bits)
	for(itCarte = joueurs[this->indexJoueurCourant].main.begin();itCarte != joueurs[this->indexJoueurCourant].main.end();itCarte++){
		tmp = carteToBool(*itCarte);
		res.insert(res.end(),tmp.begin(),tmp.end());

		//On insere dans la gamestate si les cartes sont jouable/morte/defaussable (3 bits par cartes)
//		afficheCarte(*itCarte);
		carteDouble.clear();
		carteDouble.push_back(itCarte->getColor().toInt());
		carteDouble.push_back(itCarte->getNumero());
		carteDouble.insert(carteDouble.end(),valuedesfeux.begin(),valuedesfeux.end());
//		cout << "posable :" << peutPoser2(carteDouble) << endl;
		res.push_back(peutPoser2(carteDouble));
//		cout << "morte :" << dispensable(carteDouble) << endl;
		res.push_back(dispensable(carteDouble));

		carteDouble.clear();
		carteDouble.push_back(itCarte->getNumero());
		carteDouble.push_back(itCarte->getColor().toInt());
		carteDouble.insert(carteDouble.end(),resumedefausse.begin(),resumedefausse.end());
		res.push_back(defaussable(carteDouble));

	}

	if (this->joueurs[this->indexJoueurCourant].main.size()<(unsigned)nbcartesmain){
		for (int i = 0;i<9;i++){
			res.push_back(0);
		}
	}

	//On insert les cartes de la defausse sur 25 bits
	for (itres = carteDefausse.begin();itres != carteDefausse.end();itres++){
		res.push_back(*itres);
	}

	//on enregistre le nombre de tours restant sur 3bits
	vector<int> nbTourRestant;

	if (this->plateau.paquet.taille() !=  0){
		for (int val = 0;val < 3;val ++){
			res.push_back(0);
		}
	}
	else{
		nbTourRestant = toBool(this->compteurFin,3);
		res.insert(res.end(),nbTourRestant.begin(),nbTourRestant.end());
	}

//	vector<int> nbTourRestant = vector<int>();
//	nbTourRestant = toBool(this->plateau.sizePaquet()+compteurFin,6);
//	res.insert(res.end(),nbTourRestant.begin(),nbTourRestant.end());


//	cout << "affichage de la gamestate : "  << endl;
//	for (itres = res.begin();itres != res.end();itres++){
//		cout << *itres ;
//	}

//	int i = 0;
//	cout << "nombre de jetons : " << endl;
//	for (i = 0;i<2;i++){
//		cout << res[i];
//	}
//	cout << endl;
//	cout << "score actuel : " <<endl;
//	for ( ; i< 7 ; i++){
//		cout << res[i];
//	}
//	cout << endl ;
//	int c = 0;
//	cout << "valeur des feus" << endl;
//	for (; i< 22 ; i++){
//		c++;
//		cout << res[i];
//		if (c%3 == 0) cout << " ";
//	}
//
//	cout << endl << "nombre de cartes du paquet" << endl;
//	for (;i<28;i++){
//		cout << res[i];
//	}
//	cout << endl << "affichage des cartes de la main" << endl;
//	c=0;
//	for (;i < 28 + 9*nbcartesmain;i++){
//		cout << res[i];
//		c++;
//		if (c%3 == 0) cout << " ";
//		if (c%9 == 0) cout << endl;
//	}
//	cout << endl;
//
//	cout << "affichage de la defausse : " << endl;
//	for(;i < 28 + 9*nbcartesmain +25;i++){
//		cout << res[i];
//	}
//	cout << endl;
//	cout << "affichage du nombre de tour restant" << endl;
//	for (;i<28 + 9*nbcartesmain+31;i++){
//		cout << res[i] ;
//	}
//	cout << endl;

	return conversion(res);


}
