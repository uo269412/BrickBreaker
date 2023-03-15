#include "Explosion.h"

Explosion::Explosion(float x, float y, Game* game) : Actor("res/explosion.png", x, y, 100, 100, game) {
}

void Explosion::update() {
	lifespan--;
}
