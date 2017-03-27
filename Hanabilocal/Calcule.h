/*
 * Calcule.h
 *
 *  Created on: 5 mars 2017
 *      Author: louis
 */

#ifndef HANABILOCAL_CALCULE_H_
#define HANABILOCAL_CALCULE_H_

#include <iostream>
#include <string>

using namespace std;


class Calcule{
private:
	char *chemin;
public:
	Calcule(char *c);
	~Calcule();
	float moyenne();
	float max();
	float min();
	int nombreDePartie();
	void afficherInfo();


};





#endif /* HANABILOCAL_CALCULE_H_ */
