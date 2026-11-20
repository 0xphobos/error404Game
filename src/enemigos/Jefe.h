#pragma once

#include "enemigos/Enemigo.h"

class Jefe : public Enemigo
{
protected:
    int vidaMaxima;
    int fase;

    // Comprueba si el jefe debe cambiar de fase
    void actualizarFase();

    // Se ejecuta cuando cambia la fase
    virtual void alCambiarFase(int nuevaFase);

public:
    Jefe(float x, float y,
         float ancho, float alto,
         int vida, float velocidad);

    void actualizar(float dt) override;

    // Cada jefe tendrá su propio dibujo y patrón de ataque
    void dibujar(sf::RenderWindow& ventana) override = 0;
    void atacar() override = 0;

    int getFase() const;
    int getVidaMaxima() const;
};
