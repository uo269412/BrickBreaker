#include "Bola.h"

Bola::Bola(float x, float y, Game* game) :
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game) {
	vx = 1;
	vy = -15;
	prendida = false;
	glued = false;
}

Bola::Bola(float x, float y, int vx2, int vy2, Game* game) :
	Actor("res/disparo_jugador2.png", x, y, width, height, game) {
	prendida = false;
	glued = false;
}

Bola::Bola(Bola* bola, int pos) :
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game) {
	x = pos;
	y = bola->y;
	vx = bola->vx;
	vy = bola->vy;
	width = bola->width;
	height = bola->height;
	this->game = bola->game;

	prendida = bola->prendida;
	texture = bola->texture;
	glued = bola->glued;
}

void Bola::update() {
	if (!glued) {
		x = x + vx;
		y = y + vy;
	}
	timeFireUpgrade--;
	if (timeFireUpgrade == 0) {
		revertPrender();
	}
}

void Bola::horizontalBounce() {
	vx *= -1;
}

void Bola::pegar() {
	glued = true;
}

void Bola::despegar() {
	glued = false;
}

void Bola::verticalBounce() {
	vy = vy * -1;
}

void Bola::prender() {
	timeFireUpgrade = 150;
	texture = game->getTexture("res/disparo_fuego.png");
	prendida = true;
}
void Bola::revertPrender() {
	prendida = false;
	texture = game->getTexture("res/disparo_jugador2.png");
}



