#pragma once
#include "entidades/Entidad.h"
#include "entidades/Arma.h"

class Mapa;   // el .h completo se incluye en Jugador.cpp

// Controles: A / D mueven, W (o Espacio) salta, las FLECHAS disparan
// (arriba, abajo, izquierda, derecha y diagonales). Municion ilimitada.
class Jugador : public Entidad {
private:
    float velocidadY;
    bool enSuelo;
    bool mirandoDireccion;
    Arma arma;            // las balas del jugador
    const Mapa* mapa;     // plataformas sobre las que camina (lo asigna Juego)

    void procesarEntrada(float dt);
    void aplicarFisica(float dt);
    void disparar();
public:
    Jugador(float x, float y);

    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;

    // Mapa del nivel actual. Con nullptr el jugador usa un suelo fijo (pruebas).
    void setMapa(const Mapa* nuevoMapa);

    // Vuelve al punto de inicio de un nivel. Conserva las vidas.
    void reiniciar(float nuevaX, float nuevaY);

    Arma& getArma();
    bool estaMirandoDireccion() const;
};
