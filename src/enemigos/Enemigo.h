
#pragma once

#include "entidades/Entidad.h"
#include "entidades/Arma.h"

class Enemigo : public Entidad
{
protected:
    float velocidad;
    bool mirandoDerecha;

    Arma arma;

    void moverHorizontal(float dt);
    void invertirDireccion();

public:
    Enemigo(float x, float y,
            float ancho, float alto,
            int vida, float velocidad);

    virtual ~Enemigo() override = default;

    virtual void atacar() = 0;

    void actualizar(float dt) override = 0;
    void dibujar(sf::RenderWindow& ventana) override = 0;

    void actualizarArma(float dt);
    void dibujarArma(sf::RenderWindow& ventana);

    int procesarImpactos(Entidad& objetivo);

    float getVelocidad() const;
    bool estaMirandoDerecha() const;
};
