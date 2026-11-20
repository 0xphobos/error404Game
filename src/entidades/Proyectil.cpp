#include "entidades/Proyectil.h"

namespace {
    const float ANCHO_PROYECTIL = 14.f;
    const float ALTO_PROYECTIL  = 6.f;
    const float TIEMPO_VIDA_MAX = 3.f;      // segundos
    const float LIMITE_ANCHO    = 1280.f;   // tamano de la ventana (ver Juego.h)
    const float LIMITE_ALTO     = 720.f;
}

Proyectil::Proyectil()
    : Entidad(0.f, 0.f, ANCHO_PROYECTIL, ALTO_PROYECTIL, 0),
      velocidadX(0.f), velocidadY(0.f), danio(0),
      delJugador(true), tiempoVida(0.f)
{
}

void Proyectil::activar(float px, float py, float vx, float vy, int d, bool deJugador) {
    x = px - ancho / 2.f;      // (px, py) = centro del proyectil
    y = py - alto / 2.f;
    velocidadX = vx;
    velocidadY = vy;
    danio = d;
    delJugador = deJugador;
    tiempoVida = TIEMPO_VIDA_MAX;
    vida = 1;                  // activo
}

void Proyectil::desactivar() {
    vida = 0;
}

void Proyectil::actualizar(float dt) {
    if (!estaVivo()) return;

    x += velocidadX * dt;
    y += velocidadY * dt;
    tiempoVida -= dt;

    bool fuera = x + ancho < 0.f || x > LIMITE_ANCHO ||
                 y + alto  < 0.f || y > LIMITE_ALTO;
    if (tiempoVida <= 0.f || fuera) {
        desactivar();
    }
}

void Proyectil::dibujar(sf::RenderWindow& ventana) {
    if (!estaVivo()) return;

    sf::RectangleShape forma(sf::Vector2f(ancho, alto));
    forma.setPosition(x, y);
    if (delJugador) {
        forma.setFillColor(sf::Color(255, 220, 60));    // amarillo: bala del jugador
    } else {
        forma.setFillColor(sf::Color(255, 90, 40));     // naranja: bala enemiga
    }
    ventana.draw(forma);
}

int Proyectil::getDanio() const {
    return danio;
}

bool Proyectil::esDelJugador() const {
    return delJugador;
}