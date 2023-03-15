#pragma once
#include "Actor.h"
class Explosion : public Actor
{ public:
	Explosion(float x, float y, Game* game);
	void update();
	int lifespan = 20;
};

