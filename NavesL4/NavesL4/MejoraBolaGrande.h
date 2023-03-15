#pragma once
#include "Mejora.h"
#include "Player.h"
class MejoraBolaGrande :
    public Mejora
{
public:
    MejoraBolaGrande(string image, int tiempoMejora, float x, float y, Game* game);
};

