#pragma once

#include "Actor.h"
#include "Bola.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Bola* shoot();
	int shootTime;
	bool firstShoot = true;
	void update();
	void moveX(float axis);
	void loseLife();
	int lifes = 3;
	bool pegajoso;
	int timeStickyUpgrade;
	void volverPegajoso();
	void revertPegajoso();
	int speed = 10;
	int timeSpeedUpgrade;
	void mejorarVelocidad();
	void revertVelocidad();
	int timeSizeUpgrade = 0;
	void mejorarTamaño();
	void revertTamaño();
	Animation* animation;
	void draw(float scrollX = 0) override;
};

