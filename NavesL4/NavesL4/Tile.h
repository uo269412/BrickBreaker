#pragma once
#include "Actor.h"
#include "Animation.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, Game* game);
	Tile(string filename, float x, float y, Game* game, int life);
	Animation* animation;
	void update();
	void draw(float scrollX = 0) override;
	int life;
	bool tocadoYHundido();
};

