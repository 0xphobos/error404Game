#pragma once

#include "enemigos/Jefe.h"

class JefeMapa2 : public Jefe
{
private:
    float tiempoAtaque;
    float intervaloAtaque;
    bool ataqueAlternativo;

protected:
    void alCambiarFase(int nuevaFase) override;

public:
    JefeMapa2(float x, float y);

    void actualizar(float dt) override;

    void dibujar(sf::RenderWindow& ventana) override;

    void atacar() override;
};
