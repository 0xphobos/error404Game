#include "nucleo/Juego.h"
#include "mundo/Nivel.h"

namespace {
    const float DT_MAXIMO = 0.05f;   // evita saltos si la ventana se congela
    const float INICIO_X = 100.f;    // donde aparece el jugador al empezar un nivel
    const float INICIO_Y = 500.f;

    // Ids de los logros: coinciden con los logros base de GestorArchivos.
    const int LOGRO_ANTIVIRUS = 1;   // derrotar al primer jefe
    const int LOGRO_SIN_BUGS = 2;    // completar el juego
    const int LOGRO_INTOCABLE = 3;   // vencer a un jefe sin perder vida en ese nivel
    const int LOGRO_VELOCISTA = 4;   // completar un nivel en menos de 2 minutos
    const float TIEMPO_VELOCISTA = 120.f;

    const char* const NOMBRE_JUGADOR = "Jugador";

    // Valores de Juego::resultadoGuardado
    const int SIN_GUARDAR = 0;
    const int RECORD_GUARDADO = 1;
    const int ERROR_AL_GUARDAR = 2;

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
      tiempoNivel(0.f),
      vidaAlEmpezarNivel(0),
      victoria(false),
      resultadoGuardado(SIN_GUARDAR),
      cantidadRecords(0),
      cantidadLogros(0)
{
    ventana.setFramerateLimit(60);
    // Sin repeticion de tecla: mantener Enter no salta de pantalla en pantalla.
    ventana.setKeyRepeatEnabled(false);
    camara.reset(sf::FloatRect(0.f, 0.f, ANCHO, ALTO));

    // Pon un .ttf en assets/fuentes/ con este nombre. Si no esta, el juego
    // funciona igual pero sin textos.
    fuenteCargada = fuente.loadFromFile("assets/fuentes/fuente.ttf");

    for (int i = 0; i < TOTAL_NIVELES; i++) niveles[i] = nullptr;
    jugador = new Jugador(INICIO_X, INICIO_Y);

    // Si data/logros.txt no existe o esta vacio, se crea con los logros base.
    cantidadLogros = archivos.cargarLogros(logros, GestorArchivos::MAX_LOGROS);
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
    tiempoNivel += dt;

    jugador->actualizar(dt);
    nivel->actualizar(dt);
    nivel->actualizarCamara(camara, jugador->getX() + jugador->getAncho() / 2.f,
                            static_cast<float>(ANCHO), static_cast<float>(ALTO));

    if (!jugador->estaVivo()) {
        terminarPartida(false);
        return;
    }

    if (nivel->jefeDerrotado()) {
        alVencerJefe();
    }
}

void Juego::dibujar() {
    ventana.clear(sf::Color(30, 30, 40));
    ventana.setView(ventana.getDefaultView());   // pantallas fijas, sin camara

    switch (estado) {
        case EstadoJuego::MENU:
            menu.dibujar(ventana);
            break;

        case EstadoJuego::JUGANDO:
            if (niveles[nivelActual] != nullptr) {
                ventana.setView(camara);         // el mundo se ve a traves de la camara
                niveles[nivelActual]->dibujar(ventana);
                jugador->dibujar(ventana);
                ventana.setView(ventana.getDefaultView());
            }
            dibujarHUD();                        // el HUD no se mueve con la camara
            break;

        case EstadoJuego::RECORDS:
            dibujarRecords();
            break;

        case EstadoJuego::LOGROS:
            dibujarLogros();
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

            if (resultadoGuardado == RECORD_GUARDADO) {
                dibujarTexto("Record guardado", 24, ANCHO / 2.f, ALTO * 0.30f + 230.f,
                             sf::Color(120, 220, 120), true);
            } else if (resultadoGuardado == ERROR_AL_GUARDAR) {
                dibujarTexto("No se pudo guardar el record (existe la carpeta data?)", 24,
                             ANCHO / 2.f, ALTO * 0.30f + 230.f,
                             sf::Color(230, 160, 80), true);
            }
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
    if (nuevo == EstadoJuego::RECORDS) {
        cargarRecords();    // se leen al entrar, asi se ve el ultimo guardado
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
    resultadoGuardado = SIN_GUARDAR;
    cargarNivel(0);
}

void Juego::cargarNivel(int indice) {
    if (indice < 0 || indice >= TOTAL_NIVELES) return;

    delete niveles[indice];                 // delete de nullptr es seguro
    niveles[indice] = new Nivel(indice + 1);
    nivelActual = indice;

    tiempoNivel = 0.f;
    vidaAlEmpezarNivel = jugador->getVida();
    niveles[indice]->actualizarCamara(camara, INICIO_X, static_cast<float>(ANCHO),
                                      static_cast<float>(ALTO));
}

void Juego::alVencerJefe() {
    // Logros que se ganan al vencer a un jefe.
    if (nivelActual == 0) desbloquearLogro(LOGRO_ANTIVIRUS);
    if (jugador->getVida() == vidaAlEmpezarNivel) desbloquearLogro(LOGRO_INTOCABLE);
    if (tiempoNivel < TIEMPO_VELOCISTA) desbloquearLogro(LOGRO_VELOCISTA);

    if (nivelActual + 1 < TOTAL_NIVELES) {
        avanzarNivel();
    } else {
        terminarPartida(true);
    }
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
    resultadoGuardado = SIN_GUARDAR;
    estado = EstadoJuego::GAME_OVER;

    if (gano) {
        desbloquearLogro(LOGRO_SIN_BUGS);

        // Solo las partidas completas entran al ranking: el record es el tiempo
        // total. (El puntaje es 0 hasta que el juego lleve puntos.)
        Record record(NOMBRE_JUGADOR, TOTAL_NIVELES, tiempoTotal, 0);
        resultadoGuardado = archivos.guardarRecord(record) ? RECORD_GUARDADO
                                                           : ERROR_AL_GUARDAR;
    }
}

// ---------------------------------------------------------------------------
// Records y logros
// ---------------------------------------------------------------------------

void Juego::cargarRecords() {
    cantidadRecords = archivos.cargarRecords(records, GestorArchivos::MAX_RECORDS);
    archivos.ordenarRecords(records, cantidadRecords);   // mejor primero
}

void Juego::desbloquearLogro(int id) {
    for (int i = 0; i < cantidadLogros; i++) {
        if (logros[i].getId() == id) {
            if (!logros[i].estaDesbloqueado()) {
                logros[i].desbloquear();
                archivos.guardarLogros(logros, cantidadLogros);
            }
            return;
        }
    }
}

// ---------------------------------------------------------------------------
// Dibujo
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

void Juego::dibujarRecords() {
    sf::RectangleShape franja(sf::Vector2f(ANCHO, 120.f));
    franja.setFillColor(sf::Color(60, 60, 110));
    ventana.draw(franja);
    dibujarTexto("RECORDS", 56, ANCHO / 2.f, 25.f, sf::Color::White, true);

    if (cantidadRecords == 0) {
        dibujarTexto("Todavia no hay records. Completa el juego para registrar uno.",
                     24, ANCHO / 2.f, 200.f, sf::Color::White, true);
    }

    int visibles = (cantidadRecords < RECORDS_VISIBLES) ? cantidadRecords : RECORDS_VISIBLES;
    for (int i = 0; i < visibles; i++) {
        char linea[96] = "";
        char numero[12];
        escribirEntero(i + 1, numero);
        pegar(linea, numero);
        pegar(linea, ".  ");
        pegar(linea, records[i].getNombre());
        pegar(linea, "   Nivel ");
        escribirEntero(records[i].getNivel(), numero);
        pegar(linea, numero);
        pegar(linea, "   ");
        escribirEntero(static_cast<int>(records[i].getTiempo()), numero);
        pegar(linea, numero);
        pegar(linea, " s");
        dibujarTexto(linea, 26, ANCHO / 2.f, 160.f + i * 42.f, sf::Color::White, true);
    }

    dibujarTexto("Esc para volver", 22, ANCHO / 2.f, ALTO - 60.f,
                 sf::Color(180, 180, 190), true);
}

void Juego::dibujarLogros() {
    sf::RectangleShape franja(sf::Vector2f(ANCHO, 120.f));
    franja.setFillColor(sf::Color(60, 110, 90));
    ventana.draw(franja);
    dibujarTexto("LOGROS", 56, ANCHO / 2.f, 25.f, sf::Color::White, true);

    for (int i = 0; i < cantidadLogros; i++) {
        bool conseguido = logros[i].estaDesbloqueado();
        char linea[140] = "";
        pegar(linea, conseguido ? "[x] " : "[ ] ");
        pegar(linea, logros[i].getNombre());
        pegar(linea, " - ");
        pegar(linea, logros[i].getDescripcion());
        dibujarTexto(linea, 26, ANCHO / 2.f, 160.f + i * 42.f,
                     conseguido ? sf::Color(120, 220, 120) : sf::Color(160, 160, 170), true);
    }

    dibujarTexto("Esc para volver", 22, ANCHO / 2.f, ALTO - 60.f,
                 sf::Color(180, 180, 190), true);
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
