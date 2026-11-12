
#include "enemigos/VirusVolador.h"
#include <cmath>

// Constructor
VirusVolador::VirusVolador(float x, float y)
    : Enemigo(x, y, 45.f, 40.f, 25, 120.f),
      posicionInicialY(y),
      amplitudVuelo(50.f),
      frecuenciaVuelo(2.f),
      tiempoVuelo(0.f)
{
}

// Actualizar movimiento
void VirusVolador::actualizar(float dt)
{
    if (!estaVivo())
    {
        return;
    }

    tiempoVuelo += dt;

    // Movimiento vertical oscilatorio
    y = posicionInicialY +
        amplitudVuelo * std::sin(tiempoVuelo * frecuenciaVuelo);
}

// Dibujar al virus
void VirusVolador::dibujar(sf::RenderWindow& ventana)
{
    if (!estaVivo())
    {
        return;
    }

    sf::RectangleShape forma(
        sf::Vector2f(ancho, alto)
    );

    forma.setPosition(x, y);
    forma.setFillColor(sf::Color(40, 180, 220));

    ventana.draw(forma);
}

// Ataque del virus
void VirusVolador::atacar()
{
    // TODO:
    // Aquí conectaremos el ataque con el sistema
    // de proyectiles cuando conozcamos su estructura.
}
