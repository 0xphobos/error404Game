
#include "enemigos/JefeMapa3.h"

// Constructor
JefeMapa3::JefeMapa3(float x, float y)
    : Jefe(x, y, 110.f, 100.f, 300, 120.f),
      tiempoAtaque(0.f),
      intervaloAtaque(2.f),
      patronAtaque(1)
{
}

// Actualización del jefe
void JefeMapa3::actualizar(float dt)
{
    if (!estaVivo())
    {
        return;
    }

    Jefe::actualizar(dt);

    tiempoAtaque += dt;

    if (tiempoAtaque >= intervaloAtaque)
    {
        atacar();
    }
}

// Dibujar al jefe y sus proyectiles
void JefeMapa3::dibujar(sf::RenderWindow& ventana)
{
    if (!estaVivo())
    {
        return;
    }

    sf::RectangleShape forma(
        sf::Vector2f(ancho, alto)
    );

    forma.setPosition(x, y);

    if (fase == 1)
    {
        forma.setFillColor(sf::Color(80, 80, 180));
    }
    else if (fase == 2)
    {
        forma.setFillColor(sf::Color(180, 50, 120));
    }
    else
    {
        forma.setFillColor(sf::Color(240, 40, 40));
    }

    ventana.draw(forma);

    dibujarArma(ventana);
}

// Ejecutar los patrones de ataque
void JefeMapa3::atacar()
{
    tiempoAtaque = 0.f;

    float origenX = x + ancho / 2.f;
    float origenY = y + alto / 2.f;

    float direccion = mirandoDerecha ? 1.f : -1.f;

    if (fase == 1)
    {
        patronAtaque = 1;
    }
    else if (fase == 2)
    {
        patronAtaque = 2;
    }
    else
    {
        patronAtaque = 3;
    }

    switch (patronAtaque)
    {
    case 1:
        // Fase 1: disparo horizontal
        arma.disparar(
            origenX,
            origenY,
            mirandoDerecha
        );
        break;

    case 2:
        // Fase 2: disparo doble en diagonal
        arma.dispararHacia(
            origenX, origenY,
            direccion, -0.6f
        );

        arma.dispararHacia(
            origenX, origenY,
            direccion, 0.6f
        );
        break;

    case 3:
        // Fase 3: abanico de cinco proyectiles
        arma.dispararHacia(
            origenX, origenY,
            direccion, -1.f
        );

        arma.dispararHacia(
            origenX, origenY,
            direccion, -0.5f
        );

        arma.dispararHacia(
            origenX, origenY,
            direccion, 0.f
        );

        arma.dispararHacia(
            origenX, origenY,
            direccion, 0.5f
        );

        arma.dispararHacia(
            origenX, origenY,
            direccion, 1.f
        );
        break;
    }
}

// Comportamiento al cambiar de fase
void JefeMapa3::alCambiarFase(int nuevaFase)
{
    if (nuevaFase == 1)
    {
        intervaloAtaque = 2.f;
    }
    else if (nuevaFase == 2)
    {
        intervaloAtaque = 1.3f;
    }
    else if (nuevaFase == 3)
    {
        intervaloAtaque = 0.6f;
    }
}
