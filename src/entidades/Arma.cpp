#include "entidades/Arma.h"
#include <cmath>

Arma::Arma() : Arma(0.f, 1, 350.f, false) {
}

Arma::Arma(float cadencia, int danio, float velocidadProyectil, bool delJugador)
    : cadencia(cadencia), enfriamiento(0.f), danio(danio),
      velocidadProyectil(velocidadProyectil), delJugador(delJugador)
{
}

void Arma::actualizar(float dt) {
    if (enfriamiento > 0.f) {
        enfriamiento -= dt;
        if (enfriamiento < 0.f) enfriamiento = 0.f;
    }
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        proyectiles[i].actualizar(dt);
    }
}

void Arma::dibujar(sf::RenderWindow& ventana) {
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        proyectiles[i].dibujar(ventana);
    }
}

bool Arma::puedeDisparar() const {
    return enfriamiento <= 0.f;
}

bool Arma::disparar(float x, float y, bool haciaDerecha) {
    return dispararHacia(x, y, haciaDerecha ? 1.f : -1.f, 0.f);
}

bool Arma::dispararHacia(float x, float y, float dirX, float dirY) {
    if (!puedeDisparar()) return false;

    float largo = std::sqrt(dirX * dirX + dirY * dirY);
    if (largo <= 0.f) return false;

    for (int i = 0; i < MAX_PROYECTILES; i++) {
        if (!proyectiles[i].estaVivo()) {
            proyectiles[i].activar(x, y,
                                   dirX / largo * velocidadProyectil,
                                   dirY / largo * velocidadProyectil,
                                   danio, delJugador);
            enfriamiento = cadencia;
            return true;
        }
    }
    return false;   // todos los proyectiles estan en el aire
}

int Arma::procesarImpactos(Entidad& objetivo) {
    int total = 0;
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        if (!objetivo.estaVivo()) break;
        if (proyectiles[i].estaVivo() && proyectiles[i].colisionaCon(objetivo)) {
            objetivo.recibirDanio(proyectiles[i].getDanio());
            total += proyectiles[i].getDanio();
            proyectiles[i].desactivar();
        }
    }
    return total;
}

void Arma::limpiar() {
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        proyectiles[i].desactivar();
    }
    enfriamiento = 0.f;
}

int Arma::cantidadActivos() const {
    int n = 0;
    for (int i = 0; i < MAX_PROYECTILES; i++) {
        if (proyectiles[i].estaVivo()) n++;
    }
    return n;
}

int Arma::getDanio() const {
    return danio;
}

float Arma::getCadencia() const {
    return cadencia;
}