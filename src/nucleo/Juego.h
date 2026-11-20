#pragma once
#include <SFML/Graphics.hpp>
#include "nucleo/EstadoJuego.h"
#include "nucleo/Menu.h"
#include "entidades/Jugador.h"

class Nivel;   // declaracion adelantada: el .h completo se incluye en Juego.cpp

// Clase principal del juego: poseedora de la ventana, del bucle y del estado.

// Composicion: Juego crea y destruye el Menu, el Jugador y los Niveles.
// Solo hay un Nivel vivo a la vez (se libera al pasar al siguiente).
//
// Interfaz que Juego espera de Nivel (mundo/Nivel.h):
//     Nivel(int numero);                              // numero de 1 a 3
//     ~Nivel();
//     void actualizar(Jugador& jugador, float dt);
//     void dibujar(sf::RenderWindow& ventana);
//     bool jefeDerrotado() const;
class Juego {
private:
    static const int TOTAL_NIVELES = 3;
    static const int ANCHO = 1280;
    static const int ALTO = 720;

    sf::RenderWindow ventana;
    sf::Font fuente;
    bool fuenteCargada;

    EstadoJuego estado;
    Menu menu;
    Jugador* jugador;
    Nivel* niveles[TOTAL_NIVELES];
    int nivelActual;       // indice 0..2 (el nivel que se ve es nivelActual + 1)
    float tiempoTotal;     // segundos de la partida en curso (para el record)
    bool victoria;         // en GAME_OVER: true si se vencio al ultimo jefe

    // Bucle
    void bucle();
    void procesarEventos();
    void actualizar(float dt);
    void actualizarJugando(float dt);
    void dibujar();

    // Partida y niveles
    void empezarPartida();
    void cargarNivel(int indice);
    void avanzarNivel();
    void liberarNiveles();
    void terminarPartida(bool gano);

    // Dibujo auxiliar (sin string: todo con arreglos de char)
    void dibujarHUD();
    void dibujarPantalla(const char* titulo, const char* ayuda, const sf::Color& banda);
    void dibujarTexto(const char* texto, unsigned int tam, float x, float y,
                      const sf::Color& color, bool centrado);

public:
    Juego();
    ~Juego();

    // Un Juego tiene punteros propios: no se puede copiar.
    Juego(const Juego&) = delete;
    Juego& operator=(const Juego&) = delete;

    // Arranca el juego en el menu y no vuelve hasta que se cierra.
    void iniciar();

    void cambiarEstado(EstadoJuego nuevo);
    EstadoJuego getEstado() const;
};
