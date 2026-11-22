#pragma once
#include "entidades/Entidad.h"

// Proyectil: una "bala" que viaja en linea recta hasta chocar o salir de pantalla.
// Hereda de Entidad: usa 'vida' como interruptor (1 = activo, 0 = libre para reutilizar),
// asi Arma puede tener un arreglo fijo de proyectiles sin new/delete ni vector.
class Proyectil : public Entidad {
private:
    float velocidadX;     // pixeles por segundo
    float velocidadY;
    int   danio;
    bool  delJugador;     // true: dispara el jugador (golpea enemigos). false: golpea al jugador
    float tiempoVida;     // segundos que le quedan antes de desaparecer

public:
    Proyectil();          // nace inactivo

    // (px, py) es el centro del proyectil al salir del arma.
    void activar(float px, float py, float vx, float vy, int danio, bool delJugador);
    void desactivar();

    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;

    int  getDanio() const;
    bool esDelJugador() const;
};