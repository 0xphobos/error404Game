
#pragma once

#include "enemigos/Enemigo.h"

class VirusVolador : public Enemigo
{
private:
    float posicionInicialY;
    float amplitudVuelo;
    float frecuenciaVuelo;
    float tiempoVuelo;

public:
    VirusVolador(float x, float y);

    void actualizar(float dt) override;

    void dibujar(sf::RenderWindow& ventana) override;

    void atacar() override;
};
