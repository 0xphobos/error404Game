#pragma once
#include <SFML/Graphics.hpp>
#include "nucleo/EstadoJuego.h"
#include "nucleo/Menu.h"
#include "entidades/Jugador.h"
#include "persistencia/GestorArchivos.h"

class Nivel;   // declaracion adelantada: el .h completo se incluye en Juego.cpp

// Clase principal del juego: duena de la ventana, del bucle y del estado.
//
// Composicion: Juego crea y destruye el Menu, el Jugador y los Niveles
// (solo hay un Nivel vivo a la vez). Tambien tiene un GestorArchivos con el
// que guarda los records y los logros.
//
// Lo que Juego usa de Nivel (mundo/Nivel.h):
//     Nivel(int numero);                       // 1 a 3
//     void actualizar(float dt);
//     void dibujar(sf::RenderWindow&) const;
//     void actualizarCamara(sf::View&, float jugadorX, float ancho, float alto) const;
//     bool jefeDerrotado() const;
class Juego {
private:
    static const int TOTAL_NIVELES = 3;
    static const int ANCHO = 1280;
    static const int ALTO = 720;
    static const int RECORDS_VISIBLES = 10;

    sf::RenderWindow ventana;
    sf::View camara;                // sigue al jugador dentro del mapa
    sf::Font fuente;
    bool fuenteCargada;

    EstadoJuego estado;
    Menu menu;
    Jugador* jugador;
    Nivel* niveles[TOTAL_NIVELES];
    int nivelActual;                // indice 0..2 (el nivel que se ve es nivelActual + 1)
    float tiempoTotal;              // segundos de la partida en curso
    float tiempoNivel;              // segundos del nivel en curso (logro Velocista)
    int vidaAlEmpezarNivel;         // para el logro Intocable
    bool victoria;                  // en GAME_OVER: true si se vencio al ultimo jefe
    int resultadoGuardado;          // en GAME_OVER: si se pudo guardar el record

    // Persistencia (archivos de texto en data/)
    GestorArchivos archivos;
    Record records[GestorArchivos::MAX_RECORDS];
    int cantidadRecords;
    Logro logros[GestorArchivos::MAX_LOGROS];
    int cantidadLogros;

    // Bucle
    void bucle();
    void procesarEventos();
    void actualizar(float dt);
    void actualizarJugando(float dt);
    void dibujar();

    // Partida y niveles
    void empezarPartida();
    void cargarNivel(int indice);
    void alVencerJefe();
    void avanzarNivel();
    void liberarNiveles();
    void terminarPartida(bool gano);

    // Records y logros
    void cargarRecords();
    void desbloquearLogro(int id);

    // Dibujo (sin string: todo con arreglos de char)
    void dibujarHUD();
    void dibujarPantalla(const char* titulo, const char* ayuda, const sf::Color& banda);
    void dibujarRecords();
    void dibujarLogros();
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
