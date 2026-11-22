#pragma once
#include <SFML/Graphics.hpp>
#include "nucleo/EstadoJuego.h"

// Menu principal: guarda las opciones y cual esta seleccionada.
// No cambia el estado del juego por si mismo: Juego pregunta que eligio el jugador.
// Sin vector ni string: las opciones son un arreglo fijo de cadenas de C.
class Menu {
private:
    static const int TOTAL = 4;

    sf::Font fuente;
    sf::Texture fondoTexture;
    bool fondoCargado;
    bool fuenteCargada;
    const char* opciones[TOTAL];
    int seleccion;

public:
    Menu();

    // Devuelve true cuando el jugador confirma la opcion (Enter o Espacio).
    bool manejarEvento(const sf::Event& evento);

    // Estado al que debe pasar el juego segun la opcion seleccionada.
    EstadoJuego estadoElegido() const;

    void dibujar(sf::RenderWindow& ventana) const;
};
