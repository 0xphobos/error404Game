#include "recursos/Sprites.h"

#include "enemigos/JefeMapa3.h"

// Constructor
JefeMapa3::JefeMapa3(float x, float y)
    : Jefe(x, y, 110.f, 100.f, 40, 120.f),   // 40 de vida: 40 disparos
      tiempoAtaque(0.f),
      intervaloAtaque(2.f)
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
    if (!estaVivo()) return;

    if (!Sprites::dibujar(ventana, "assets/sprites/jefe3.png",
                          x, y, ancho, alto, false)) {
        sf::RectangleShape forma(sf::Vector2f(ancho, alto));
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color(150, 50, 100));
        ventana.draw(forma);
    }

    dibujarBarraVida(ventana);
    dibujarArma(ventana);
}

// Ejecutar el ataque: el jefe esta ABAJO y dispara siempre en 3 direcciones
// (izquierda, medio y derecha), todas hacia arriba. Las fases solo lo hacen mas rapido.
void JefeMapa3::atacar()
{
    tiempoAtaque = 0.f;

    float origenX = x + ancho / 2.f;
    float origenY = y;   // sale por la parte de arriba del jefe

    arma.dispararHacia(origenX, origenY, -1.f, -1.f);   // izquierda (diagonal)
    arma.dispararHacia(origenX, origenY,  0.f, -1.f);   // medio (recto hacia arriba)
    arma.dispararHacia(origenX, origenY,  1.f, -1.f);   // derecha (diagonal)
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
        intervaloAtaque = 1.5f;
    }
    else if (nuevaFase == 3)
    {
        intervaloAtaque = 1.0f;
    }
}
