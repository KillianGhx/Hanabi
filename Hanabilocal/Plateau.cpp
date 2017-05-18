#include "Plateau.h"
#include <iostream>
using namespace std;

vector<int> listToVector(list<int> liste){
	vector<int> res;
	list<int>::iterator it;
	for (it = liste.begin();it != liste.end();it++){
		res.push_back(*it);
	}
	return res;
}

vector<int> toBool(int n,int nbBits){
	list<int> v;
	list<int>::iterator it ;
//	cout << "nombre : "  << n <<endl;
	while(n != 0){
		if(n%2 == 0){
			v.push_front(0);
		}
		else v.push_front(1);
		n=n/2;
	}
	for (unsigned i = v.size(); i <nbBits; i++){
		v.push_front(0);
	}
//	cout << "resultat : ";
//	for (it = v.begin(); it != v.end(); it++){
//		cout << *it << " " ;
//	}

	return listToVector(v);
}

vector<int> carteToBool(Carte c){
	vector<int> res;
	vector<int> tmp;
	res=toBool(c.getColor().toInt(),3);
	tmp=toBool(c.getNumero(),3);
	res.insert(res.end(),tmp.begin(),tmp.end());
	return res;
}

Plateau::Plateau(){
	bleus.push(Carte(Couleur("bleu"),0));
	jaunes.push(Carte(Couleur("jaune"),0));
	verts.push(Carte(Couleur("vert"),0));
	rouges.push(Carte(Couleur("rouge"),0));
	blancs.push(Carte(Couleur("blanc"),0));
	this->JetonRouge=3;
	this->jeu_fini=false;
}

Plateau::Plateau(int seed) {
	bleus.push(Carte(Couleur("bleu"),0));
	jaunes.push(Carte(Couleur("jaune"),0));
	verts.push(Carte(Couleur("vert"),0));
	rouges.push(Carte(Couleur("rouge"),0));
	blancs.push(Carte(Couleur("blanc"),0));
	this->JetonRouge=3;
	this->jeu_fini=false;
	paquet = Deck(seed);
}

void Plateau::poser(Carte c ){
	int couleur = 0;
	if (!c.getColor().getString().compare("bleu")) couleur = 1; //BLEU
	if (!c.getColor().getString().compare("jaune")) couleur = 2; //JAUNE
	if (!c.getColor().getString().compare("vert"))couleur = 3;  //VERT
	if (!c.getColor().getString().compare("rouge")) couleur = 4; //ROUGE
	if (!c.getColor().getString().compare("blanc")) couleur = 5; //BLANC


	switch (couleur){
	case 1 :
		if (bleus.top().getNumero()+1==c.getNumero()){
			bleus.push(c);
		}
		else{
			this->defausser(c);
			JetonRouge--;
		}

		break;
	case 2 :
		if (jaunes.top().getNumero()+1==c.getNumero()){
			jaunes.push(c);
		}
		else{
			this->defausser(c);
			JetonRouge--;
			}
		break;
	case 3 :
		if (verts.top().getNumero()+1==c.getNumero()){
			verts.push(c);
		}
		else{
					this->defausser(c);
					JetonRouge--;
		}
		break;
	case 4 :
		if (rouges.top().getNumero()+1==c.getNumero()){
			rouges.push(c);
		}
		else{
					this->defausser(c);
					JetonRouge--;
		}
		break;
	case 5 :
		if (blancs.top().getNumero()+1==c.getNumero()){
			blancs.push(c);
		}
		else{
					this->defausser(c);
					JetonRouge--;
		}
		break;
	}
}

int Plateau::calculpoint(){
	int score = 0;
	score += bleus.top().getNumero();
	score += jaunes.top().getNumero();
	score += rouges.top().getNumero();
	score += verts.top().getNumero();
	score += blancs.top().getNumero();
	return score;
}

void Plateau::affiche(){
	cout << "Cartes du plateau : "<< endl;
	bleus.top().affiche();
	jaunes.top().affiche();
	rouges.top().affiche();
	verts.top().affiche();
	blancs.top().affiche();
	cout<<" Jeton : "<<endl;
	cout<<"Nombre de jeton rouge : "<<this->getJetonRouge()<<endl;

	cout << "affichage du deck : " << endl;
//	paquet.affiche();
}

void Plateau::affiche2D(){
	cout << "Cartes du plateau : "<< endl;
	bleus.top().affiche2D();
	jaunes.top().affiche2D();
	rouges.top().affiche2D();
	verts.top().affiche2D();
	blancs.top().affiche2D();
	cout<<"Nombre de jeton rouge : "<<JetonRouge<<" // ";
	cout<<"Carte restante dans le deck : "<<this->paquet.taille()<<endl;
//	cout << "affichage du deck : " << endl;
//	paquet.affiche();
}

void Plateau::fini(){
	if((bleus.top().getNumero()==5) && (jaunes.top().getNumero()==5) && (rouges.top().getNumero()==5) && (verts.top().getNumero()==5) && (blancs.top().getNumero()==5) ){
		this->jeu_fini=true;
	}
}



Carte Plateau::piocher(){
	return paquet.pioche();
}

vector<Carte> Plateau::distribution(int nbcarte){
	vector<Carte> main;
	for(int i=0;i<nbcarte;i++){
		main.push_back(paquet.pioche());
	}
	return main;
}

Plateau::~Plateau(){
//	cout << "Destruction du Plateau" << endl;
}

void Plateau::afficheDefausse(){
	cout << "Affichage de la defausse " << endl;
	vector<Carte>::iterator it;
	for (it = defausse.begin();it!=defausse.end();it++){
		it->affiche();
		cout<<endl;
	}
	cout<<endl;
}

	void Plateau::defausser(Carte c){
		defausse.push_back(c);
	}

	vector<Carte> Plateau::alltop(){
		vector<Carte> tops ;
		vector<Carte>::iterator it;

		tops.push_back(bleus.top());
		tops.push_back(jaunes.top());
		tops.push_back(rouges.top());
		tops.push_back(verts.top());
		tops.push_back(blancs.top());
		return tops;
	}

	vector<double> Plateau::resumedefausse(){
		vector<double> res;
		for (int i = 0;i<25;i++){
			res.push_back(0);
		}
		vector<Carte>::iterator it;
		for (it = defausse.begin();it != defausse.end();it++){
			res[it->getColor().toInt()*5+it->getNumero()]++;
		}
		return res;
	}

	vector<int> Plateau::resumeDefausse2(){
		vector<double> defausse;
		vector<int> res;
		defausse = this->resumedefausse();
		for (int i = 0;i != defausse.size();i++){
			if(i%5 == 0 && defausse[i] >= 3) res.push_back(1);
			else if((i%5 == 1 || i%5 == 2 || i%5 == 3 ) && defausse[i] >= 2) res.push_back(1);
			else if(i%5 == 4 && defausse[i] >= 1) res.push_back(1);
			else res.push_back(0);

		}

		return res;
	}





	vector<int> Plateau::getState(){

		vector<int> res;
		vector<int> tmp;
		vector<int>::iterator itres;
		//ajout du nombre de jeton (sur 2 bits)
		tmp=toBool(this->getJetonRouge(),2);
		res.insert(res.end(),tmp.begin(),tmp.end());


		//ajout du score (sur 5 bits)
		tmp=toBool(this->calculpoint(),5);
		res.insert(res.end(),tmp.begin(),tmp.end());

		//ajout des feu posé sur le plateau
		vector<Carte>::iterator it;
		vector<Carte> feu;
		feu=this->alltop();
		for (it = feu.begin(); it != feu.end();it ++){
			tmp = toBool(it->getNumero(),3);
			res.insert(res.end(),tmp.begin(),tmp.end());
		}

		//ajout des cartes de la defausse
//		vector<double> defausse = resumedefausse();
//		vector<double>::iterator it2;
//		int index =0;
//		for (it2 = defausse.begin();it2 != defausse.end();it2++){
//			if(index % 5 == 4){
//			tmp = toBool(*it2,1);
//			}
//			else tmp = toBool(*it2,2);
//			res.insert(res.end(),tmp.begin(),tmp.end());
//			index++;
//		}

		//ajout du nombres de cartes contenus dans le paquet (sur 6 bits)
		tmp = toBool(paquet.taille(),6);
		res.insert(res.end(),tmp.begin(),tmp.end());

//		cout << "affichage du res" << endl;
//		for (itres = res.begin(); itres != res.end();itres++){
//			cout << *itres << "  ";
//		}
		//retourne le vector symbolisant l'etat du plateau
		return res;

	}

	vector<double> Plateau::getFeu(){
		vector<double> res;
		res.push_back(bleus.top().getNumero());
		res.push_back(rouges.top().getNumero());
		res.push_back(blancs.top().getNumero());
		res.push_back(jaunes.top().getNumero());
		res.push_back(verts.top().getNumero());
		return res;
	}
