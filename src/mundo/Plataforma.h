#pragma once
#include <SFML/Graphics.hpp>

class Plataforma {
private:
    float x;
    float y;
    float ancho;
    float alto;
    sf::RectangleShape forma; //representacion visual de la plataforma

public:
    Plataforma();
    Plataforma(float x, float y, float ancho, float alto);

    void configurar(float x, float y, float ancho, float alto);
    sf::FloatRect getBounds() const; //caja de colision
    void dibujar(sf::RenderWindow& ventana) const;
};