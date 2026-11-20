
#include "enemigos/JefeMapa1.h"

// Constructor
JefeMapa1::JefeMapa1(float x, float y)
    : Jefe(x, y, 70.f, 90.f, 150, 80.f),
      tiempoAtaque(0.f),
      intervaloAtaque(2.f)
{
}

// Actualización del jefe
void JefeMapa1::actualizar(float dt)
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
void JefeMapa1::dibujar(sf::RenderWindow& ventana)
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
        forma.setFillColor(sf::Color(120, 40, 180));
    }
    else if (fase == 2)
    {
        forma.setFillColor(sf::Color(200, 70, 40));
    }
    else
    {
        forma.setFillColor(sf::Color(220, 20, 60));
    }

    ventana.draw(forma);

    dibujarArma(ventana);
}

// Ejecutar el ataque
void JefeMapa1::atacar()
{
    tiempoAtaque = 0.f;

    float origenX = x + ancho / 2.f;
    float origenY = y + alto / 2.f;

    arma.disparar(origenX, origenY, mirandoDerecha);
}

// Comportamiento al cambiar de fase
void JefeMapa1::alCambiarFase(int nuevaFase)
{
    if (nuevaFase == 1)
    {
        intervaloAtaque = 2.f;
    }
    else if (nuevaFase == 2)
    {
        intervaloAtaque = 1.5f;
    }
    else if (nuevaFase == 3)
    {
        intervaloAtaque = 0.8f;
    }
}
