
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
void JefeMapa2::dibujar(sf::RenderWindow& ventana)
{
    sf::RectangleShape forma(
        sf::Vector2f(ancho, alto)
    );

    forma.setPosition(x, y);

    // Diferenciar visualmente las fases
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

    // Diferenciar las dos variantes de ataque
    if (ataqueAlternativo)
    {
        forma.setOutlineThickness(5.f);
        forma.setOutlineColor(sf::Color::White);
    }

    ventana.draw(forma);
}

// Ejecutar el ataque
void JefeMapa2::atacar()
{
    tiempoAtaque = 0.f;

    // Alternar entre los dos patrones de ataque
    ataqueAlternativo = !ataqueAlternativo;

    if (ataqueAlternativo)
    {
        // TODO: Primer patrón de ataque.
        // Aquí conectaremos los proyectiles.
    }
    else
    {
        // TODO: Segundo patrón de ataque.
        // Aquí conectaremos los proyectiles.
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
