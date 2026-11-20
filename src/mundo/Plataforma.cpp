#include "mundo/Plataforma.h"

Plataforma::Plataforma()
    : x(0.0f), y(0.0f), ancho(0.0f), alto(0.0f) {
    forma.setFillColor(sf::Color(60, 140, 70));
}

Plataforma::Plataforma(float x, float y, float ancho, float alto)
    : x(x), y(y), ancho(ancho), alto(alto) {
    configurar(x, y, ancho, alto);
}

void Plataforma::configurar(float nuevaX, float nuevaY, float nuevoAncho, float nuevoAlto) {
    x = nuevaX;
    y = nuevaY;
    ancho = nuevoAncho;
    alto = nuevoAlto;
    forma.setPosition(x, y); //sincroniza posicion grafica
    forma.setSize(sf::Vector2f(ancho, alto)); //sincroniza tamano grafico
    forma.setFillColor(sf::Color(60, 140, 70));
}

sf::FloatRect Plataforma::getBounds() const {
    return sf::FloatRect(x, y, ancho, alto); //devuelve rectangulo para colisiones
}

void Plataforma::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(forma);
}