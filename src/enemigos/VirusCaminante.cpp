
#include "enemigos/VirusCaminante.h"

// Constructor
VirusCaminante::VirusCaminante(float x, float y,
                               float limiteIzquierdo,
                               float limiteDerecho)
    : Enemigo(x, y, 40.f, 45.f, 30, 100.f),
      limiteIzquierdo(limiteIzquierdo),
      limiteDerecho(limiteDerecho)
{
}

// Actualizar movimiento
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
}

// Dibujar al virus
void VirusCaminante::dibujar(sf::RenderWindow& ventana)
{
    if (!estaVivo())
    {
        return;
    }

    sf::RectangleShape forma(
        sf::Vector2f(ancho, alto)
    );

    forma.setPosition(x, y);
    forma.setFillColor(sf::Color(40, 180, 70));

    ventana.draw(forma);
}

// Ataque del virus
void VirusCaminante::atacar()
{
    // TODO:
    // Aquí conectaremos el daño por contacto
    // cuando integremos el sistema de combate.
}
