#pragma once

#include "enemigos/Jefe.h"

class JefeMapa3 : public Jefe
{
private:
    float tiempoAtaque;
    float intervaloAtaque;
    int patronAtaque;

protected:
    void alCambiarFase(int nuevaFase) override;

public:
    JefeMapa3(float x, float y);

    void actualizar(float dt) override;

    void dibujar(sf::RenderWindow& ventana) override;

    void atacar() override;
};
