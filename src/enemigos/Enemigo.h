#pragma once

#include "entidades/Entidad.h"

class Enemigo : public Entidad
{
protected:

    float velocidad;
    bool mirandoDerecha;

    // Movimiento horizontal compartido
    void moverHorizontal(float dt);

    // Cambiar la dirección del enemigo
    void invertirDireccion();

public:

    Enemigo(float x, float y,
            float ancho, float alto,
            int vida, float velocidad);

    virtual ~Enemigo() override = default;

    // Cada tipo de enemigo tendrá su propio ataque
    virtual void atacar() = 0;

    // Métodos que deberán implementar las clases hijas
    void actualizar(float dt) override = 0;

    void dibujar(sf::RenderWindow& ventana) override = 0;

    float getVelocidad() const;

    bool estaMirandoDerecha() const;
};
