#pragma once
#include "Mejora.h"
#include "Player.h"
class MejoraFuego :
    public Mejora
{
public:
    MejoraFuego(string image, int tiempoMejora, float x, float y, Game* game);
};

