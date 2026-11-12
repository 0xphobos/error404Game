#pragma once
#include "entidades/Entidad.h"

class Jugador : public Entidad {
private:
    float velocidadY;
    bool enSuelo;
    bool mirandoDireccion;

    void procesarEntrada(float dt);
    void aplicarFisica(float dt);
public:
    Jugador(float x, float y);

    void actualizar(float dt) override;
    void dibujar(sf::RenderWindow& ventana) override;

    bool estaMirandoDireccion() const;
};