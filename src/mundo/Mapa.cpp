#include "mundo/Mapa.h"

Mapa::Mapa(int ancho)
    : ancho(ancho), cantidadPlataformas(0) {}

void Mapa::limpiar() {
    cantidadPlataformas = 0; // Reinicia contador sin liberar memoria dinamica
}

bool Mapa::agregarPlataforma(float x, float y, float anchoPlat, float altoPlat) {
    if (cantidadPlataformas >= MAX_PLATAFORMAS) {
        std::cout << "Aviso: limite maximo de plataformas alcanzado en Mapa.\n";
        return false;
    }

    plataformas[cantidadPlataformas].configurar(x, y, anchoPlat, altoPlat);
    cantidadPlataformas++;
    return true;
}

bool Mapa::hayColision(const sf::FloatRect& area, sf::FloatRect* plataformaColisionada) const {
    for (int i = 0; i < cantidadPlataformas; i++) {
        sf::FloatRect bounds = plataformas[i].getBounds();
        if (area.intersects(bounds)) { // Comprueba superposicion AABB
            if (plataformaColisionada != nullptr) {
                *plataformaColisionada = bounds; // Guarda el rectangulo con el que choco
            }
            return true;
        }
    }
    return false;
}

void Mapa::dibujar(sf::RenderWindow& ventana) const {
    for (int i = 0; i < cantidadPlataformas; i++) {
        plataformas[i].dibujar(ventana);
    }
}

int Mapa::getAncho() const {
    return ancho;
}

int Mapa::getCantidadPlataformas() const {
    return cantidadPlataformas;
}

const Plataforma& Mapa::getPlataforma(int indice) const {
    return plataformas[indice];
}