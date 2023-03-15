#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("",x, y, 75, 20, game) {
	shootTime = 0;
	animation = new Animation("res/player.png", 76, height,
		455, 20, 5, 6, true, game);

}

void Player::update() {
	animation->update();
	shootTime--;
	timeStickyUpgrade--;
	if (timeStickyUpgrade == 0) {
		revertPegajoso();
	}
	timeSpeedUpgrade--;
	if (timeSpeedUpgrade == 0) {
		revertVelocidad();
	}
	timeSizeUpgrade--;
	if (timeSizeUpgrade == 0) {
		revertTamaño();
	}

	
}

void Player::moveX(float axis) {
	vx = axis * speed;
}

void Player::draw(float scrollX) {
	animation->draw(x, y);

}

Bola* Player::shoot() {
		Bola* projectile = new Bola(x, y-20, game);
		if (shootTime <= 0) {
			shootTime = 100;
			return projectile;
		}
		return NULL;
}

void Player::loseLife() {
		if (lifes > 0) {
			lifes--;
		}
}

void Player::mejorarVelocidad() {
	timeSpeedUpgrade = 150;
	speed = 20;
}
void Player::revertVelocidad() {
	speed = 10;
}
void Player::mejorarTamaño() {
	timeSizeUpgrade = 150;
	width = 125;
	if (pegajoso) {
		animation = new Animation("res/player_expanded_sticky.png", 125, height,
			748, 20, 5, 6, true, game);
	}
	else {
		animation = new Animation("res/player_expanded.png", 125, height,
			748, 20, 5, 6, true, game);
	}
}
void Player::revertTamaño() {
	width = 76;
	if (pegajoso) {
		animation = new Animation("res/player_sticky.png", 76, height,
			455, 20, 5, 6, true, game);
	}
	else {
		animation = new Animation("res/player.png", 76, height,
			455, 20, 5, 6, true, game);
	}
	
}
void Player::volverPegajoso() {
	timeStickyUpgrade = 150;
	pegajoso = true;
	if (width < 100) {
		animation = new Animation("res/player_sticky.png", 76, height,
			455, 20, 5, 6, true, game);
	}
	else {
		animation = new Animation("res/player_expanded_sticky.png", 125, height,
			748, 20, 5, 6, true, game);
	}
}
void Player::revertPegajoso() {
	pegajoso = false;
	if (width < 100) {
		animation = new Animation("res/player.png", 76, height,
			455, 20, 5, 6, true, game);
	}
	else {
		animation = new Animation("res/player_expanded.png", 125, height,
			748, 20, 5, 6, true, game);
	}
}


