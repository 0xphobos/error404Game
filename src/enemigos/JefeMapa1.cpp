#include "recursos/Sprites.h"

#include "enemigos/JefeMapa1.h"

// Constructor
JefeMapa1::JefeMapa1(float x, float y)
    : Jefe(x, y, 70.f, 90.f, 20, 80.f),   // 20 de vida: 20 disparos
      tiempoAtaque(0.f),
      intervaloAtaque(2.f)
{
    mirandoDerecha = false;   // el jugador llega desde la izquierda
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
    if (!estaVivo()) return;

    if (!Sprites::dibujar(ventana, "assets/sprites/jefe1.png",
                          x, y, ancho, alto, false)) {
        sf::RectangleShape forma(sf::Vector2f(ancho, alto));
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color(150, 50, 100));
        ventana.draw(forma);
    }

    dibujarBarraVida(ventana);
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
