#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "mundo/Mapa.h"

class Enemigo;
class Jefe;
class Jugador;

// Un nivel: el mapa (plataformas), los enemigos y el jefe.
//   Nivel 1: 2560 de ancho, pocos enemigos, jefe estatico que dispara recto.
//   Nivel 2: 3840 de ancho (mas largo), muchos mas enemigos, jefe que dispara en abanico.
//   Nivel 3: 1280 de ancho (una sola pantalla). El jefe esta ABAJO y dispara hacia
//            arriba en 3 direcciones; el jugador salta entre plataformas y dispara hacia abajo.
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

    void liberarEnemigos();
    void agregarEnemigo(Enemigo* nuevo);
    // sueloY = la altura (y) de la superficie donde camina
    void agregarCaminante(float x, float sueloY, float limiteIzq, float limiteDer);
    void agregarVolador(float x, float y, float limiteIzq, float limiteDer);

    void disenarNivel1();
    void disenarNivel2();
    void disenarNivel3();

public:
    // anchoMapa = 0 -> el ancho se elige segun el numero de nivel
    explicit Nivel(int numero = 1, int anchoMapa = 0);
    ~Nivel();

    // El nivel tiene punteros propios: no se puede copiar.
    Nivel(const Nivel&) = delete;
    Nivel& operator=(const Nivel&) = delete;

    void cargarDisenoBase();

    // Mueve enemigos y jefe, y revisa los golpes:
    //   - las balas del jugador contra enemigos y jefe
    //   - enemigos, jefe y sus balas contra el jugador (o si el jugador cae al vacio)
    // Devuelve true si el jugador fue golpeado (Juego le quita una vida y reinicia el nivel).
    bool actualizar(float dt, Jugador& jugador);

    void dibujar(sf::RenderWindow& ventana) const;
    void actualizarCamara(sf::View& camara, float jugadorX, float anchoVentana, float altoVentana) const;

    bool jefeDerrotado() const;
    Mapa& getMapa();
    const Mapa& getMapa() const;
};
