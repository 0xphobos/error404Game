
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
    // Actualizar las fases
    Jefe::actualizar(dt);

    // Controlar el tiempo entre ataques
    tiempoAtaque += dt;

    if (tiempoAtaque >= intervaloAtaque)
    {
        atacar();
    }
}

// Dibujar al jefe
void JefeMapa3::dibujar(sf::RenderWindow& ventana)
{
    sf::RectangleShape forma(
        sf::Vector2f(ancho, alto)
    );

    forma.setPosition(x, y);

    // Cambiar el color según la fase
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
}

// Ejecutar los patrones de ataque
void JefeMapa3::atacar()
{
    tiempoAtaque = 0.f;

    // Seleccionar el patrón según la fase
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
        // TODO: Ataque básico.
        break;

    case 2:
        // TODO: Ataque doble.
        break;

    case 3:
        // TODO: Ataque especial de la fase final.
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
