#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Bola.h"
#include "Text.h"
#include "Tile.h"
#include "Mejora.h"
#include "MejoraVelocidad.h"
#include "MejoraTamaño.h"
#include "MejoraPegajosa.h"
#include "MejoraTresBolas.h"
#include "MejoraFuego.h"
#include "MejoraBolaGrande.h"
#include "Pad.h"
#include "Explosion.h"

#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init(int points);
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void generarMejora(int x, int y, bool siempre);
	bool overlapBolaTile(Bola* bola, Tile* tile, bool destruible);
	bool firstShoot = true;
	Actor* message;
	bool pause;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonShoot;

	Space* space;
	int mapWidth;
	list<Tile*> tiles;
	list<Tile*> tilesDestructibles;
	list<Tile*> eliminatorios;
	list<Tile*> bombas;
	list<Tile*> tilesMejora;
	list<Mejora*> mejoras;
	list<Explosion*> explosiones;

	Audio* audioBackground;
	Audio* audioBounce;
	Audio* audioBalls;
	Audio* audioFire;
	Audio* audioSlime;
	Audio* audioLarge;
	Audio* audioSpeed;
	Audio* audioStick;
	Audio* audioExplosion;


	Text* textPoints;
	Text* textCollectables;
	int points;
	int pointsCollectables;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundCollec;
	list<Bola*> bolas;

	bool controlContinue = false;
	bool controlShoot = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	


};

