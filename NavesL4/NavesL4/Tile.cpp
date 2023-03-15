#include "Tile.h"

Tile::Tile(string filename,float x, float y, Game* game)
	: Actor(filename, x, y, 91, 30, game) {
		animation = new Animation(filename, width, height,
			637, 30, 6, 7, true, game);

}

Tile::Tile(string filename, float x, float y, Game* game, int liv)
	: Actor(filename, x, y, 91, 30, game) {
	animation = new Animation(filename, width, height,
		637, 30, 6, 7, true, game);
	life = liv;

}

void Tile::update() {
		animation->update();
}

void Tile::draw(float scrollX) {
		animation->draw(x, y);

}

bool Tile:: tocadoYHundido() {
	return --life == 0;
}


