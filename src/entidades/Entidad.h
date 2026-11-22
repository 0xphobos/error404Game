#pragma once
#include <SFML/Graphics.hpp>
class Entidad{
protected:
    float x, y;
    float ancho, alto;
    int vida;
public: 
    Entidad(float x, float y, float ancho, float alto, int vida);
    virtual ~Entidad(){}

    virtual void actualizar(float dt) = 0;
    virtual void dibujar(sf::RenderWindow& ventana) = 0;

    void recibirDanio(int d);
    bool estaVivo()const ;
    bool colisionaCon(const Entidad& otra) const;
    bool operator ==(const Entidad& otra) const;

    float getX() const;
    float getY() const;
    float getAncho() const;
    float getAlto() const;
    int getVida() const;
};