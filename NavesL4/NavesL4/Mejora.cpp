#include "Mejora.h"
Mejora::Mejora(string image, int tm, float x, float y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 40, game) {


	aMovement = new Animation(image, width, height,
		256, 32, 6, 8, true, game);
	/*
	aMovement = new Animation("res/recolectable.png", width, height,
		256, 32, 6, 8, true, game);
	*/
	tiempoMejora = tm;
	animation = aMovement;
	vy = 5;
	tiempoMejora = 0;
}

void Mejora::update() {
	y = y + vy;
	animation->update();
}

void Mejora::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}


