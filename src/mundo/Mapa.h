#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "mundo/Plataforma.h"

class Mapa {
public:
    static const int MAX_PLATAFORMAS = 64;//capacidad maxima

private:
    int ancho;//ancho total del escenario
    int cantidadPlataformas;
    Plataforma plataformas[MAX_PLATAFORMAS]; //arreglo de plataformas

public:
    explicit Mapa(int ancho = 2560);

    void limpiar();
    bool agregarPlataforma(float x, float y, float anchoPlat, float altoPlat);
    bool hayColision(const sf::FloatRect& area, sf::FloatRect* plataformaColisionada = nullptr) const;
    void dibujar(sf::RenderWindow& ventana) const;

    int getAncho() const;
    int getCantidadPlataformas() const;
    const Plataforma& getPlataforma(int indice) const;
};
