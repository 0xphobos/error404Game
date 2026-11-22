#include "enemigos/VirusVolador.h"
#include "recursos/Sprites.h"

// Constructor
VirusVolador::VirusVolador(float x, float y,
                           float limiteIzquierdo,
                           float limiteDerecho)
    : Enemigo(x, y, 45.f, 40.f, 1, 120.f),   // vida 1: muere de un golpe
      limiteIzquierdo(limiteIzquierdo),
      limiteDerecho(limiteDerecho)
{
}

// Actualizar movimiento: solo de izquierda a derecha
void VirusVolador::actualizar(float dt)
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
void VirusVolador::dibujar(sf::RenderWindow& ventana)
{
    if (!estaVivo()) return;

    if (!Sprites::dibujar(ventana, "assets/sprites/virus_volador.png",
                          x, y, ancho, alto, !mirandoDerecha)) {
        sf::RectangleShape forma(sf::Vector2f(ancho, alto));
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color(40, 180, 220));
        ventana.draw(forma);
    }

    dibujarArma(ventana);
}

// Ataque por contacto
void VirusVolador::atacar()
{
    // El daño se aplica desde Nivel cuando el virus toca al jugador.
}
