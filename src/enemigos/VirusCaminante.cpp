#include "recursos/Sprites.h"

#include "enemigos/VirusCaminante.h"

// Constructor
VirusCaminante::VirusCaminante(float x, float y,
                               float limiteIzquierdo,
                               float limiteDerecho)
    : Enemigo(x, y, 40.f, 45.f, 1, 100.f),   // vida 1: muere de un golpe
      limiteIzquierdo(limiteIzquierdo),
      limiteDerecho(limiteDerecho)
{
}

// Actualizar movimiento y arma
void VirusCaminante::actualizar(float dt)
{
    if (!estaVivo())
    {
        return;
    }

    moverHorizontal(dt);

    // Comprobar el límite izquierdo
    if (x <= limiteIzquierdo)
    {
        x = limiteIzquierdo;
        mirandoDerecha = true;
    }

    // Comprobar el límite derecho
    if (x + ancho >= limiteDerecho)
    {
        x = limiteDerecho - ancho;
        mirandoDerecha = false;
    }

    actualizarArma(dt);
}

// Dibujar al virus
void VirusCaminante::dibujar(sf::RenderWindow& ventana)
{
    if (!estaVivo()) return;

    if (!Sprites::dibujar(ventana, "assets/sprites/virus_caminante.png",
                          x, y, ancho, alto, !mirandoDerecha)) {
        sf::RectangleShape forma(sf::Vector2f(ancho, alto));
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color(40, 180, 70));
        ventana.draw(forma);
    }

    dibujarArma(ventana);
}

// Ataque por contacto
void VirusCaminante::atacar()
{
    // El daño se aplicará desde el sistema de colisiones
    // cuando el virus entre en contacto con el jugador.
}
