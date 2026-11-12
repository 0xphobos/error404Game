
#pragma once

#include "enemigos/Enemigo.h"

class VirusCaminante : public Enemigo
{
private:
    float limiteIzquierdo;
    float limiteDerecho;

public:
    VirusCaminante(float x, float y,
                   float limiteIzquierdo,
                   float limiteDerecho);

    void actualizar(float dt) override;

    void dibujar(sf::RenderWindow& ventana) override;

    void atacar() override;
};
