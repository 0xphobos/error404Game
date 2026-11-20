#pragma once
#include <SFML/Graphics.hpp>
#include "entidades/Entidad.h"
#include "entidades/Proyectil.h"

// Arma: dispara y administra sus propios proyectiles.
// Tiene un arreglo fijo (MAX_PROYECTILES) que se reutiliza: sin vector, sin new/delete.
// La usan el Jugador (cadencia propia) y los Enemigos (ellos ya controlan su ritmo
// con intervaloAtaque, por eso el arma por defecto no tiene enfriamiento).
class Arma {
public:
    static const int MAX_PROYECTILES = 20;

private:
    Proyectil proyectiles[MAX_PROYECTILES];
    float cadencia;            // segundos minimos entre disparos (0 = sin limite)
    float enfriamiento;        // segundos que faltan para poder disparar otra vez
    int   danio;
    float velocidadProyectil;  // pixeles por segundo
    bool  delJugador;

public:
    Arma();                    // arma enemiga basica
    Arma(float cadencia, int danio, float velocidadProyectil, bool delJugador);

    // Enfria el arma y mueve todos los proyectiles activos.
    void actualizar(float dt);
    void dibujar(sf::RenderWindow& ventana);

    bool puedeDisparar() const;

    // Disparo horizontal desde (x, y). Respeta la cadencia.
    bool disparar(float x, float y, bool haciaDerecha);

    // Disparo en cualquier direccion (no hace falta que dirX/dirY esten normalizados).
    // Respeta la cadencia. Para abanicos, el enemigo llama varias veces (cadencia 0).
    bool dispararHacia(float x, float y, float dirX, float dirY);

    // Revisa todos los proyectiles contra 'objetivo'. Cada impacto le aplica el danio
    // y consume el proyectil. Devuelve el danio total causado en esta llamada.
    int procesarImpactos(Entidad& objetivo);

    void limpiar();                    // desactiva todos (al cambiar de nivel, etc.)
    int  cantidadActivos() const;

    int   getDanio() const;
    float getCadencia() const;
};