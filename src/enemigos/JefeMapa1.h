#pragma once

#include "enemigos/Jefe.h"

class JefeMapa1 : public Jefe
{
private:
    float tiempoAtaque;
    float intervaloAtaque;

protected:
    void alCambiarFase(int nuevaFase) override;

public:
    JefeMapa1(float x, float y);

    void actualizar(float dt) override;

    void dibujar(sf::RenderWindow& ventana) override;

    void atacar() override;
};
