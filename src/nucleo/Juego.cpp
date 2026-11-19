#include "nucleo/Juego.h"
#include "mundo/Nivel.h"

namespace {
    const float DT_MAXIMO = 0.05f;   // evita saltos si la ventana se congela
    const float INICIO_X = 100.f;    // donde aparece el jugador al empezar un nivel
    const float INICIO_Y = 500.f;

    bool teclaPulsada(const sf::Event& evento, sf::Keyboard::Key tecla) {
        return evento.type == sf::Event::KeyPressed && evento.key.code == tecla;
    }

    // Convierte un entero a texto sin usar <string> ni <cstdio>.
    void escribirEntero(int valor, char* destino) {
        if (valor < 0) valor = 0;
        char invertido[12];
        int n = 0;
        if (valor == 0) invertido[n++] = '0';
        while (valor > 0) {
            invertido[n++] = static_cast<char>('0' + valor % 10);
            valor /= 10;
        }
        for (int i = 0; i < n; i++) destino[i] = invertido[n - 1 - i];
        destino[n] = '\0';
    }

    // Pega 'origen' al final de 'destino' (el arreglo debe tener espacio).
    void pegar(char* destino, const char* origen) {
        int i = 0;
        while (destino[i] != '\0') i++;
        int j = 0;
        while (origen[j] != '\0') destino[i++] = origen[j++];
        destino[i] = '\0';
    }
}

// ---------------------------------------------------------------------------
// Construccion y destruccion
// ---------------------------------------------------------------------------

Juego::Juego()
    : ventana(sf::VideoMode(ANCHO, ALTO), "Run and Gun"),
      fuenteCargada(false),
      estado(EstadoJuego::MENU),
      jugador(nullptr),
      nivelActual(0),
      tiempoTotal(0.f),
      victoria(false)
{
    ventana.setFramerateLimit(60);
    // Sin repeticion de tecla: mantener Enter no salta de pantalla en pantalla.
    ventana.setKeyRepeatEnabled(false);

    // Pon un .ttf en assets/fuentes/ con este nombre. Si no esta, el juego
    // funciona igual pero sin textos.
    fuenteCargada = fuente.loadFromFile("assets/fuentes/fuente.ttf");

    for (int i = 0; i < TOTAL_NIVELES; i++) niveles[i] = nullptr;
    jugador = new Jugador(INICIO_X, INICIO_Y);
}

Juego::~Juego() {
    liberarNiveles();
    delete jugador;
}

// ---------------------------------------------------------------------------
// Bucle principal
// ---------------------------------------------------------------------------

void Juego::iniciar() {
    estado = EstadoJuego::MENU;
    bucle();
}

void Juego::bucle() {
    sf::Clock reloj;

    while (ventana.isOpen() && estado != EstadoJuego::SALIR) {
        procesarEventos();

        float dt = reloj.restart().asSeconds();   // tiempo entre fotogramas
        if (dt > DT_MAXIMO) dt = DT_MAXIMO;

        actualizar(dt);
        dibujar();
    }

    if (ventana.isOpen()) ventana.close();
}

void Juego::procesarEventos() {
    sf::Event evento;
    while (ventana.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            cambiarEstado(EstadoJuego::SALIR);
            continue;
        }

        switch (estado) {
            case EstadoJuego::MENU:
                if (menu.manejarEvento(evento)) {
                    cambiarEstado(menu.estadoElegido());
                }
                break;

            case EstadoJuego::JUGANDO:
                if (teclaPulsada(evento, sf::Keyboard::Escape)) {
                    cambiarEstado(EstadoJuego::MENU);   // abandona la partida
                }
                break;

            case EstadoJuego::RECORDS:
            case EstadoJuego::LOGROS:
            case EstadoJuego::GAME_OVER:
                if (teclaPulsada(evento, sf::Keyboard::Escape) ||
                    teclaPulsada(evento, sf::Keyboard::Return)) {
                    cambiarEstado(EstadoJuego::MENU);
                }
                break;

            case EstadoJuego::SALIR:
                break;
        }
    }
}

void Juego::actualizar(float dt) {
    if (estado == EstadoJuego::JUGANDO) {
        actualizarJugando(dt);
    }
}

void Juego::actualizarJugando(float dt) {
    Nivel* nivel = niveles[nivelActual];
    if (nivel == nullptr) return;

    tiempoTotal += dt;
    jugador->actualizar(dt);
    nivel->actualizar(*jugador, dt);

    if (!jugador->estaVivo()) {
        terminarPartida(false);
        return;
    }

    if (nivel->jefeDerrotado()) {
        if (nivelActual + 1 < TOTAL_NIVELES) {
            avanzarNivel();
        } else {
            terminarPartida(true);
        }
    }
}

void Juego::dibujar() {
    ventana.clear(sf::Color(30, 30, 40));

    switch (estado) {
        case EstadoJuego::MENU:
            menu.dibujar(ventana);
            break;

        case EstadoJuego::JUGANDO:
            if (niveles[nivelActual] != nullptr) {
                niveles[nivelActual]->dibujar(ventana);
            }
            jugador->dibujar(ventana);
            dibujarHUD();
            break;

        case EstadoJuego::RECORDS:
            // TODO: mostrar los records cuando exista GestorArchivos.
            dibujarPantalla("RECORDS", "Proximamente  -  Esc para volver",
                            sf::Color(60, 60, 110));
            break;

        case EstadoJuego::LOGROS:
            // TODO: mostrar los logros cuando exista GestorArchivos.
            dibujarPantalla("LOGROS", "Proximamente  -  Esc para volver",
                            sf::Color(60, 110, 90));
            break;

        case EstadoJuego::GAME_OVER: {
            if (victoria) {
                dibujarPantalla("VICTORIA", "Enter para volver al menu",
                                sf::Color(40, 130, 60));
            } else {
                dibujarPantalla("GAME OVER", "Enter para volver al menu",
                                sf::Color(150, 40, 40));
            }
            char linea[40] = "Tiempo: ";
            char numero[12];
            escribirEntero(static_cast<int>(tiempoTotal), numero);
            pegar(linea, numero);
            pegar(linea, " s");
            dibujarTexto(linea, 28, ANCHO / 2.f, ALTO * 0.30f + 160.f,
                         sf::Color::White, true);
            break;
        }

        case EstadoJuego::SALIR:
            break;
    }

    ventana.display();
}

// ---------------------------------------------------------------------------
// Estados, partida y niveles
// ---------------------------------------------------------------------------

void Juego::cambiarEstado(EstadoJuego nuevo) {
    if (nuevo == EstadoJuego::JUGANDO && estado != EstadoJuego::JUGANDO) {
        empezarPartida();
    }
    if (nuevo == EstadoJuego::MENU) {
        liberarNiveles();   // al volver al menu no queda ninguna partida viva
    }
    estado = nuevo;
}

EstadoJuego Juego::getEstado() const {
    return estado;
}

void Juego::empezarPartida() {
    delete jugador;
    jugador = new Jugador(INICIO_X, INICIO_Y);

    liberarNiveles();
    tiempoTotal = 0.f;
    victoria = false;
    cargarNivel(0);
}

void Juego::cargarNivel(int indice) {
    if (indice < 0 || indice >= TOTAL_NIVELES) return;

    delete niveles[indice];                 // delete de nullptr es seguro
    niveles[indice] = new Nivel(indice + 1);
    nivelActual = indice;
}

void Juego::avanzarNivel() {
    // El jugador vuelve al inicio pero conserva la vida que le queda.
    int vidaConservada = jugador->getVida();
    delete jugador;
    jugador = new Jugador(INICIO_X, INICIO_Y);
    jugador->recibirDanio(jugador->getVida() - vidaConservada);

    delete niveles[nivelActual];
    niveles[nivelActual] = nullptr;
    cargarNivel(nivelActual + 1);
}

void Juego::liberarNiveles() {
    for (int i = 0; i < TOTAL_NIVELES; i++) {
        delete niveles[i];
        niveles[i] = nullptr;
    }
}

void Juego::terminarPartida(bool gano) {
    victoria = gano;
    estado = EstadoJuego::GAME_OVER;

    // TODO: cuando exista GestorArchivos, guardar aqui el record
    // (tiempoTotal, nivel alcanzado) y desbloquear los logros que correspondan.
}

// ---------------------------------------------------------------------------
// Dibujo auxiliar
// ---------------------------------------------------------------------------

void Juego::dibujarHUD() {
    // Una cajita roja por cada vida que le queda al jugador.
    for (int i = 0; i < jugador->getVida(); i++) {
        sf::RectangleShape corazon(sf::Vector2f(24.f, 24.f));
        corazon.setPosition(20.f + i * 32.f, 20.f);
        corazon.setFillColor(sf::Color(220, 50, 60));
        ventana.draw(corazon);
    }

    char linea[40] = "Nivel ";
    char numero[12];
    escribirEntero(nivelActual + 1, numero);
    pegar(linea, numero);
    pegar(linea, "   Tiempo: ");
    escribirEntero(static_cast<int>(tiempoTotal), numero);
    pegar(linea, numero);
    pegar(linea, " s");
    dibujarTexto(linea, 22, 20.f, 56.f, sf::Color::White, false);
}

void Juego::dibujarPantalla(const char* titulo, const char* ayuda, const sf::Color& banda) {
    sf::RectangleShape franja(sf::Vector2f(ANCHO, 200.f));
    franja.setPosition(0.f, ALTO * 0.30f);
    franja.setFillColor(banda);
    ventana.draw(franja);

    dibujarTexto(titulo, 64, ANCHO / 2.f, ALTO * 0.30f + 20.f, sf::Color::White, true);
    dibujarTexto(ayuda, 24, ANCHO / 2.f, ALTO * 0.30f + 110.f, sf::Color::White, true);
}

void Juego::dibujarTexto(const char* texto, unsigned int tam, float x, float y,
                         const sf::Color& color, bool centrado) {
    if (!fuenteCargada) return;

    sf::Text t(texto, fuente, tam);
    t.setFillColor(color);
    if (centrado) {
        sf::FloatRect b = t.getLocalBounds();
        t.setOrigin(b.left + b.width / 2.f, 0.f);
    }
    t.setPosition(x, y);
    ventana.draw(t);
}
