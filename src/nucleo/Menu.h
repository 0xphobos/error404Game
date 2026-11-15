#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "nucleo/EstadoJuego.h"

// Menu principal: guarda las opciones y cual esta seleccionada.
// No cambia el estado del juego por si mismo: Juego pregunta que eligio el jugador.
class Menu {
private:
    sf::Font fuente;
    bool fuenteCargada;
    std::vector<std::string> opciones;
    int seleccion;

public:
    Menu();

    // Devuelve true cuando el jugador confirma la opcion (Enter o Espacio).
    bool manejarEvento(const sf::Event& evento);

    // Estado al que debe pasar el juego segun la opcion seleccionada.
    EstadoJuego estadoElegido() const;

    void dibujar(sf::RenderWindow& ventana) const;
};
