#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();
	init(0);

}


void GameLayer::init(int pointsN) {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.8, HEIGHT * 0.85, 100, 100, game);
	firstShoot = true;

	space = new Space(1);
	tiles.clear();
	tilesDestructibles.clear();
	mejoras.clear();
	bolas.clear();
	bombas.clear();
	eliminatorios.clear();
	tilesMejora.clear();
	explosiones.clear();

	
	audioBalls = new Audio("res/balls.wav", false);
	audioFire = new Audio("res/fire.wav", false);
	audioSlime = new Audio("res/slime.wav", false);
	audioLarge = new Audio("res/large.wav", false);
	audioSpeed = new Audio("res/speed.wav", false);
	audioStick = new Audio("res/stick.wav", false);
	audioExplosion = new Audio("res/explosion.wav", false);
	audioBounce = new Audio("res/bounce.wav", false);


	points = pointsN;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);
	
	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	backgroundCollec = new Actor("res/icono_mejoras_gui.png",
		WIDTH * 0.85, HEIGHT * 0.15, 24, 24, game);

	bolas.clear(); // Vaciar por si reiniciamos el juego

	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			// Por carácter (en cada línea)F
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 91 / 2 + j * 91; // x central
				float y = 30 + i * 30; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case '1': {
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addPlayerActor(player);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/bloque_tierra.png", x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'R': {
		Tile* tile = new Tile("res/sp_rojo.png", x, y, game,1);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tilesDestructibles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}

	case 'V': {
		Tile* tile = new Tile("res/sp_verde.png", x, y, game,1);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tilesDestructibles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'A': {
		Tile* tile = new Tile("res/sp_amarillo.png", x, y, game,1);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tilesDestructibles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'Z': {
		Tile* tile = new Tile("res/sp_azul.png", x, y, game,1);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tilesDestructibles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'E': {
		Tile* tile = new Tile("res/bloque_eliminatorio.png", x, y, game,1);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		eliminatorios.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'B': {
		Tile* tile = new Tile("res/bloque_bomba.png", x, y, game,1);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		bombas.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'F': {
		Tile* tile = new Tile("res/bloque_reforzado.png", x, y, game, 2);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tilesDestructibles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'M': {
		Tile* tile = new Tile("res/bloque_mejora.png", x, y, game, 2);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tilesMejora.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}

void GameLayer::generarMejora(int x, int y, bool siempre) {
	int randNum;
	if (!siempre) {
		randNum = rand() % 20;
	}
	else {
		randNum = rand() % 5;
	}
	if (randNum == 0) {
		Mejora* mejora = new MejoraVelocidad("res/recolectable1.png", 0, x, y, game);
		mejora->y = mejora->y - mejora->height / 2;
		mejoras.push_back(mejora);
	}
	else if (randNum == 1) {
		Mejora* mejora = new MejoraTamaño("res/recolectable2.png", 0, x, y, game);
		mejora->y = mejora->y - mejora->height / 2;
		mejoras.push_back(mejora);
	}
	else if (randNum == 2) {
		Mejora* mejora = new MejoraPegajosa("res/recolectable3.png", 0, x, y, game);
		mejora->y = mejora->y - mejora->height / 2;
		mejoras.push_back(mejora);
	}
	else if (randNum == 3) {
		Mejora* mejora = new MejoraTresBolas("res/recolectable4.png", 0, x, y, game);
		mejora->y = mejora->y - mejora->height / 2;
		mejoras.push_back(mejora);
	}
	else if (randNum == 4) {
		Mejora* mejora = new MejoraFuego("res/recolectable5.png", 0, x, y, game);
		mejora->y = mejora->y - mejora->height / 2;
		mejoras.push_back(mejora);
	}
}


void GameLayer::update() {
	if (pause) {
		return;
	}
	//UPDATES
	srand(time(0));
	space->update();
	background->update();
	player->update();

	for (auto const& mejora : mejoras) {
		mejora->update();
	}
	for (auto const& bola : bolas) {
		bola->update();
	}
	for (auto const& tile : tilesDestructibles) {
		tile->update();
	}
	for (auto const& tile : bombas) {
		tile->update();
	}
	for (auto const& tile : eliminatorios) {
		tile->update();
	}
	for (auto const& tile : tilesMejora) {
		tile->update();
	}
	if (!firstShoot) {
		if (bolas.size() == 0) {
			pause = true;
			init(0);
		}
	}

	if (tilesDestructibles.size() == 0) {
		game->currentLevel++;
		/*
		message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		*/
		pause = true;
		init(points);
	}


	//Mejoras

	for (auto const& mejora : mejoras) {
		if (player->isOverlap(mejora)) {
			points+=5;
			textPoints->content = to_string(points);
			if (MejoraVelocidad* v = dynamic_cast<MejoraVelocidad*>(mejora)) {
				player->mejorarVelocidad();
				audioSpeed->play();
			}
			if (MejoraTamaño* v = dynamic_cast<MejoraTamaño*>(mejora)) {
				player->mejorarTamaño();
				audioLarge->play();
			}
			if (MejoraPegajosa* v = dynamic_cast<MejoraPegajosa*>(mejora)) {
				player->volverPegajoso();
				audioSlime->play();
			}

			if (MejoraTresBolas* v = dynamic_cast<MejoraTresBolas*>(mejora)) {
				list<Bola*> addedBolas;
				for (auto const& bola : bolas) {
					Bola* bola1 = new Bola(bola->x + 5, bola->y, game);
					Bola* bola2 = new Bola(bola->x - 5, bola->y, game);
					bola1->glued = bola->glued;
					bola1->vy = bola->vy;
					bola2->vy = bola->vy;
					bola2->glued = bola->glued;
					bola1->prendida = bola->prendida;
					bola1->texture = bola->texture;
					bola1->timeFireUpgrade = bola->timeFireUpgrade;
					bola2->prendida = bola->prendida;
					bola2->texture = bola->texture;
					bola2->timeFireUpgrade = bola->timeFireUpgrade;
					addedBolas.push_back(bola1);
					addedBolas.push_back(bola2);
				}
				audioBalls->play();
				bolas.insert(bolas.end(), addedBolas.begin(), addedBolas.end());
			}

			if (MejoraFuego* v = dynamic_cast<MejoraFuego*>(mejora)) {
				for (auto const& bola : bolas) {
					bola->prender();
				}
				audioFire->play();
			}

			mejoras.remove(mejora);
			return;
		}
	}


	list<Tile*> deleteTiles;
	list<Bola*> deleteBolas;

	list<Explosion*> deleteExplosiones;

	for (auto const& explosion : explosiones) {
		explosion->update();
		for (auto const& tile : tilesDestructibles) {
			if (explosion->isOverlap(tile)) {
				points += 10;
				if (tile->tocadoYHundido()) {
					points += 10;
					generarMejora(tile->x, tile->y, false);
					deleteTiles.push_back(tile);
				}
				textPoints->content = to_string(points);
			}
		}
		for (auto const& tile : tilesMejora) {
			if (explosion->isOverlap(tile)) {
				points += 10;
				if (tile->tocadoYHundido()) {
					points += 15;
					generarMejora(tile->x, tile->y, false);
					deleteTiles.push_back(tile);
				}
				textPoints->content = to_string(points);
			}
		}
		for (auto const& tile : bombas) {
			if (explosion->isOverlap(tile)) {
				points += 20;
				audioExplosion->play();
				explosiones.push_back(new Explosion(tile->x, tile->y, game));
				textPoints->content = to_string(points);
				deleteTiles.push_back(tile);
			}
		}
		if (explosion->lifespan == 0) {
			deleteExplosiones.push_back(explosion);
		}
	}

	for (auto const& bola : bolas) {
		if (bola->x - bola->width / 2 <= 0 || bola->x + bola->width / 2 >= WIDTH) {
			deleteBolas.push_back(bola);
		}
		if (bola->y - bola->height / 2 <= 0 || bola->y + bola->height / 2 >= HEIGHT) {
			deleteBolas.push_back(bola);
		}
		for (auto const& tile : eliminatorios) {
			if (bola->isOverlap(tile)) {
				deleteBolas.push_back(bola);
			}
		}

	}

	for (auto const& tile : bombas) {
		for (auto const& bola : bolas) {
			if (overlapBolaTile(bola, tile, true)) {
				points += 20;
				if (tile->tocadoYHundido()) {
					points += 20;
					explosiones.push_back(new Explosion(tile->x, tile->y, game));
					deleteTiles.push_back(tile);
				}
				textPoints->content = to_string(points);
			}
		}
	}

	for (auto const& tile : tilesDestructibles) {
		for (auto const& bola : bolas) {
			if (overlapBolaTile(bola, tile, true)) {
				points += 10;
				if (tile->tocadoYHundido()) {
					points += 10;
					generarMejora(tile->x, tile->y, false);
					deleteTiles.push_back(tile);
				}
				textPoints->content = to_string(points);
			}
		}
	}


	for (auto const& tile : tiles) {
		for (auto const& bola : bolas) {
			overlapBolaTile(bola, tile, false);
		}
	}

	for (auto const& tile : tilesMejora) {
		for (auto const& bola : bolas) {
			if (overlapBolaTile(bola, tile, true)) {
				points += 15;
				if (tile->tocadoYHundido()) {
					points += 15;
					generarMejora(tile->x, tile->y, true);
					deleteTiles.push_back(tile);
				}
				textPoints->content = to_string(points);
			}
		}
	}

	for (auto const& bola : bolas) {
		if (bola->isAbove(player)) {
			if (player->pegajoso) {
				if (!bola->glued) {
					audioStick->play();
				}
				bola->pegar();

			}
			else {
				//audioBounce->play();
			}
			bola->vy = -bola->vy;
			if (player->timeSizeUpgrade <= 0) {
				int bolacentro = bola->width / 2 + bola->x;
				int playerWidth = player->width + player->x;
				int playerwidthMIN = player->x - (player->width / 2);
				float velocityBounceMin = (playerwidthMIN - playerWidth) / 5 + 10;
				for (int i = playerwidthMIN - 20; i < playerWidth + 20; i++) {
					if (i == bolacentro) {
						bola->vx = velocityBounceMin;
					}
					if (i % 5 == 0) {
						velocityBounceMin++;
					}
				}
			}
		}
	}

	for (auto const& delTile : deleteTiles) {
	
		tilesDestructibles.remove(delTile);
		bombas.remove(delTile);
		tilesMejora.remove(delTile);
		space->removeStaticActor(delTile);
	}
	for (auto const& delBola : deleteBolas) {
		bolas.remove(delBola);
	}

	for (auto const& delExplosion : deleteExplosiones) {
		explosiones.remove(delExplosion);
	}

	deleteTiles.clear();
	deleteBolas.clear();
	deleteExplosiones.clear();

	//cout << "update GameLayer" << endl;
}


bool GameLayer::overlapBolaTile(Bola* bola, Tile* tile, bool destruible)
{
	int hotfix = -30;
	bool value = false;
	int tileX = tile->x;
	int tileWidth = tile->width;
	int tileY = tile->y;
	int tileHeight = tile->height;
	int bolacentroX = bola->width / 2 + bola->x;
	int bolacentroY = bola->height / 2 + bola->y;

	int tile1X = tile->x  + hotfix;
	int tile1Y = tile->y;

	int tile2X = tile->x + tile->width + hotfix;
	int tile2Y = tile->y;

	int tile3X = tile->x + tile->width + hotfix;
	int tile3Y = tile->y + tile->height;

	int tile4X = tile->x + hotfix;
	int tile4Y = tile->y + tile->height;

	int bola1X = bola->x;
	int bola1Y = bola->y + (bola->height / 2);

	int bola2X = bola->x + (bola->width / 2);
	int bola2Y = bola->y;

	int bola3X = bola->x + bola->width;
	int bola3Y = bola->y + (bola->height / 2);

	int bola4X = bola->x + (bola->width / 2);
	int bola4Y = bola->y + bola->height;

	//Choques verticales
	if (bola2Y >= tile1Y && bola2Y <= tile3Y) { //b2 verticalmente dentro del tile
		if (bola2X >= tile1X && bola2X <= tile2X) {//b2 horizontalmente dentro del tile
			if (!(bola->prendida && destruible)) {
				bola->verticalBounce();
				
			}
			value = true;
		}
	}

	if (bola4Y >= tile3Y && bola4Y <= tile2Y) { //b4 verticalmente dentro del tile
		if (bola4X >= tile1X && bola4X <= tile2X) {//b4 horizontalmente dentro del tile
			if (!(bola->prendida && destruible)) {
				bola->verticalBounce();
				
			}	
			value = true;
		}
	}

	if (bola1X <= tile2X && bola1X >= tile1X) { //b1 horizontalmente dentro del tile
		if (bola1Y >= tile1Y && bola1Y <= tile3Y) { //b1 verticalmente dentro del tile
			if (!(bola->prendida && destruible)) {
				bola->horizontalBounce();
				
			}	
			value = true;
		}
	}

	if (tile1X <= bola3X && tile2X >= bola3X) { //b1 horizontalmente dentro del tile
		if (bola1Y >= tile1Y && bola1Y <= tile3Y) { //b1 verticalmente dentro del tile
			if (!(bola->prendida && destruible)) {
				bola->horizontalBounce();
				
			}	
			value = true;
		}
	}

	if (value && !bola->prendida) {
		//audioBounce->play();
	}
	return value;
	
}

void GameLayer::draw() {
	background->draw();
	for (auto const& explosion : explosiones) {
		explosion->draw();
	}
	for (auto const& tile : tiles) {
		tile->draw();
	}

	for (auto const& tile : eliminatorios) {
		tile->draw();
	}

	for (auto const& tile : bombas) {
		tile->draw();
	}

	for (auto const& tile : tilesDestructibles) {
		tile->draw();
	}

	for (auto const& tile : tilesMejora) {
		tile->draw();
	}

	for (auto const& mejora : mejoras) {
		mejora->draw();
	}

	for (auto const& bola : bolas) {
		bola->draw();
	}

	player->draw();
	backgroundPoints->draw();
	textPoints->draw();
	backgroundCollec->draw();

	// HUD
	if (game->input == game->inputMouse) {
		buttonShoot->draw(); 
		pad->draw(); 
	}
	if (pause) {
		message->draw();
	}
	SDL_RenderPresent(game->renderer); // Renderiza
}


//CONTROLES

void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}
		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
	}

	//procesar controles
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}
	if (controlShoot) {
		if (firstShoot) {
			Bola* newProjectile = player->shoot();
			if (newProjectile != NULL) {
				bolas.push_back(newProjectile);
			}
			firstShoot = false;
		}
		else {
			for (auto const& bola : bolas) {
				if (bola->glued) {
					bola->despegar();
					bola->y-=5;
				}
			}
		}

	}

	// Eje X
	if (controlMoveX > 0) {
		for (auto const& bola : bolas) {
			if (bola->glued) {
				bola->x += player->speed;
			}
		}
		player->moveX(1);

	}
	else if (controlMoveX < 0) {
		for (auto const& bola : bolas) {
			if (bola->glued) {
				bola->x -= player->speed;
			}
		}
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	cout << "stickX" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		controlMoveX = 1;
	}
	else if (stickX < -4000) {
		controlMoveX = -1;
	}
	else {
		controlMoveX = 0;
	}

	if (buttonA) {
		controlShoot = true;
	}
	else {
		controlShoot = false;
	}

	if (buttonB) {
		controlMoveY = -1; // Saltar
	}
	else {
		controlMoveY = 0;
	}
}

void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = true;
			// CLICK TAMBIEN TE MUEVE
			controlMoveX = pad->getOrientationX(motionX);
		}
		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = true;
		}


	}
	// Cada vez que se mueve
	if (event.type == SDL_MOUSEMOTION) {
		if (pad->clicked && pad->containsPoint(motionX, motionY)) {
			controlMoveX = pad->getOrientationX(motionX);
			// Rango de -20 a 20 es igual que 0
			if (controlMoveX > -20 && controlMoveX < 20) {
				controlMoveX = 0;
			}

		}
		else {
			pad->clicked = false; // han sacado el ratón del pad
			controlMoveX = 0;
		}
		if (buttonShoot->containsPoint(motionX, motionY) == false) {
			controlShoot = false;
		}


	}
	// Cada vez que levantan el click
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (pad->containsPoint(motionX, motionY)) {
			pad->clicked = false;
			// LEVANTAR EL CLICK TAMBIEN TE PARA
			controlMoveX = 0;
		}

		if (buttonShoot->containsPoint(motionX, motionY)) {
			controlShoot = false;
		}

	}
}

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
		case SDLK_ESCAPE:
			game->loopActive = false;
			break;
		case SDLK_1:
			game->scale();
			break;
		case SDLK_d: // derecha
			controlMoveX = 1;
			break;
		case SDLK_a: // izquierda
			controlMoveX = -1;
			break;
		case SDLK_w: // arriba
			controlMoveY = -1;
			break;
		case SDLK_s: // abajo
			controlMoveY = 1;
			break;
		case SDLK_SPACE: // dispara
			controlShoot = true;
			break;
		}


	}
	if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
		case SDLK_d: // derecha
			if (controlMoveX == 1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_a: // izquierda
			if (controlMoveX == -1) {
				controlMoveX = 0;
			}
			break;
		case SDLK_w: // arriba
			if (controlMoveY == -1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_s: // abajo
			if (controlMoveY == 1) {
				controlMoveY = 0;
			}
			break;
		case SDLK_SPACE: // dispara
			controlShoot = false;
			break;
		}

	}

}

