#pragma once
#include "Mejora.h"
#include "Player.h"
class MejoraVelocidad :
    public Mejora
{
public:
    MejoraVelocidad(string image, int tiempoMejora, float x, float y, Game* game);
};

