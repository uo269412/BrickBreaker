#pragma once

#include "Actor.h"


class Bola : public Actor
{
public:
	Bola(float x, float y, Game* game);
	Bola(Bola* bola, int pos);
	Bola(float x, float y, int width, int height, Game* game);
	bool prendida;
	void horizontalBounce();
	void verticalBounce();
	void update();
	int timeFireUpgrade = 0;
	void prender();
	void revertPrender();	
	bool glued;
	void pegar();
	void despegar();
};

