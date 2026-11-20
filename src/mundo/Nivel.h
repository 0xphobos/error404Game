#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "mundo/Mapa.h"

class Enemigo;
class Jefe;  

class Nivel {
public:
    static const int MAX_ENEMIGOS = 32; //lim. max. de enemigos

private:
    int numero;
    float tiempo;
    Mapa mapa;
    int cantidadEnemigos;
    Enemigo* enemigos[MAX_ENEMIGOS];
    Jefe* jefe; //ptr al jefe del nivel

public:
    explicit Nivel(int numero = 1, int anchoMapa = 2560);

    void cargarDisenoBase();
    void actualizar(float dt);
    void dibujar(sf::RenderWindow& ventana) const;
    void actualizarCamara(sf::View& camara, float jugadorX, float anchoVentana, float altoVentana) const;

    bool jefeDerrotado() const;
    Mapa& getMapa();
    const Mapa& getMapa() const;
};