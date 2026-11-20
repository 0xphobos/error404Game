
#include "enemigos/JefeMapa2.h"

// Constructor
JefeMapa2::JefeMapa2(float x, float y)
    : Jefe(x, y, 85.f, 85.f, 200, 100.f),
      tiempoAtaque(0.f),
      intervaloAtaque(2.2f),
      ataqueAlternativo(false)
{
}

// Actualización del jefe
void JefeMapa2::actualizar(float dt)
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
void JefeMapa2::dibujar(sf::RenderWindow& ventana)
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
        forma.setFillColor(sf::Color(30, 150, 170));
    }
    else if (fase == 2)
    {
        forma.setFillColor(sf::Color(230, 150, 30));
    }
    else
    {
        forma.setFillColor(sf::Color(180, 30, 70));
    }

    if (ataqueAlternativo)
    {
        forma.setOutlineThickness(5.f);
        forma.setOutlineColor(sf::Color::White);
    }

    ventana.draw(forma);

    dibujarArma(ventana);
}

// Ejecutar los patrones de ataque
void JefeMapa2::atacar()
{
    tiempoAtaque = 0.f;

    ataqueAlternativo = !ataqueAlternativo;

    float origenX = x + ancho / 2.f;
    float origenY = y + alto / 2.f;

    float direccion = mirandoDerecha ? 1.f : -1.f;

    if (ataqueAlternativo)
    {
        // Patrón 1: disparo horizontal
        arma.disparar(
            origenX,
            origenY,
            mirandoDerecha
        );
    }
    else
    {
        // Patrón 2: disparo en abanico
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
    }
}

// Comportamiento al cambiar de fase
void JefeMapa2::alCambiarFase(int nuevaFase)
{
    if (nuevaFase == 1)
    {
        intervaloAtaque = 2.2f;
    }
    else if (nuevaFase == 2)
    {
        intervaloAtaque = 1.5f;
    }
    else if (nuevaFase == 3)
    {
        intervaloAtaque = 0.9f;
    }
}
