#pragma once
#include "Actor.h"
#include "Animation.h" 
class Mejora : public Actor
{
public:
	Mejora(string image, int tiempoMejora, float x, float y, Game* game);
	void update();
	Animation* aMovement;
	Animation* animation;
	void draw(float scrollX = 0) override;
	int tiempoMejora;
};