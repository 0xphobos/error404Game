
#pragma once

#include "enemigos/Enemigo.h"

// Virus volador: vuela en linea recta de izquierda a derecha (sin subir ni bajar)
// entre dos limites. Muere de un golpe.
class VirusVolador : public Enemigo
{
private:
    float limiteIzquierdo;
    float limiteDerecho;

public:
    VirusVolador(float x, float y,
                 float limiteIzquierdo,
                 float limiteDerecho);

    void actualizar(float dt) override;

    void dibujar(sf::RenderWindow& ventana) override;

    void atacar() override;
};

