#include "mundo/Nivel.h"
#include "entidades/Jugador.h"
#include "enemigos/VirusCaminante.h"
#include "enemigos/VirusVolador.h"
#include "enemigos/JefeMapa1.h"
#include "enemigos/JefeMapa2.h"
#include "enemigos/JefeMapa3.h"

namespace {
    const float SUELO_Y = 600.0f;          // altura de la parte de arriba del suelo
    const float ALTO_SUELO = 120.0f;       // hasta el borde inferior de la ventana
    const float ALTO_PLATAFORMA = 20.0f;
    const float ALTO_CAMINANTE = 45.0f;    // el mismo que en VirusCaminante.cpp
    const float LIMITE_CAIDA = 800.0f;     // si el jugador baja mas que esto, cayo al vacio

    int anchoSegunNivel(int numero) {
        if (numero == 2) return 3840;      // nivel mas largo
        if (numero == 3) return 1280;      // una sola pantalla
        return 2560;
    }
}

Nivel::Nivel(int numero, int anchoMapa)
    : numero(numero), tiempo(0.0f),
      mapa(anchoMapa > 0 ? anchoMapa : anchoSegunNivel(numero)),
      cantidadEnemigos(0), jefe(nullptr) {
    for (int i = 0; i < MAX_ENEMIGOS; i++) {
        enemigos[i] = nullptr;
    }
    cargarDisenoBase();
}

Nivel::~Nivel() {
    liberarEnemigos();
}

void Nivel::liberarEnemigos() {
    for (int i = 0; i < MAX_ENEMIGOS; i++) {
        delete enemigos[i];          // delete de nullptr es seguro
        enemigos[i] = nullptr;
    }
    cantidadEnemigos = 0;
    delete jefe;
    jefe = nullptr;
}

void Nivel::agregarEnemigo(Enemigo* nuevo) {
    if (cantidadEnemigos >= MAX_ENEMIGOS) {
        std::cout << "Aviso: limite maximo de enemigos alcanzado en Nivel.\n";
        delete nuevo;                // no cabe: se libera para no perder memoria
        return;
    }
    enemigos[cantidadEnemigos] = nuevo;
    cantidadEnemigos++;
}

void Nivel::agregarCaminante(float x, float sueloY, float limiteIzq, float limiteDer) {
    agregarEnemigo(new VirusCaminante(x, sueloY - ALTO_CAMINANTE, limiteIzq, limiteDer));
}

void Nivel::agregarVolador(float x, float y, float limiteIzq, float limiteDer) {
    agregarEnemigo(new VirusVolador(x, y, limiteIzq, limiteDer));
}

// ---------------------------------------------------------------------------
// Diseno de los niveles
// ---------------------------------------------------------------------------

void Nivel::cargarDisenoBase() {
    mapa.limpiar();
    liberarEnemigos();

    if (numero == 2) {
        disenarNivel2();
    } else if (numero == 3) {
        disenarNivel3();
    } else {
        disenarNivel1();
    }

    std::cout << "Nivel " << numero << " cargado con "
              << mapa.getCantidadPlataformas() << " plataformas y "
              << cantidadEnemigos << " enemigos.\n";
}

void Nivel::disenarNivel1() {
    // Suelo con un hueco (de x = 900 a x = 1080)
    mapa.agregarPlataforma(0.0f,    SUELO_Y, 900.0f,  ALTO_SUELO);
    mapa.agregarPlataforma(1080.0f, SUELO_Y, 1480.0f, ALTO_SUELO);

    // Plataformas
    mapa.agregarPlataforma(350.0f,  490.0f, 200.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(650.0f,  400.0f, 160.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(1250.0f, 480.0f, 220.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(1600.0f, 400.0f, 180.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(2000.0f, 480.0f, 200.0f, ALTO_PLATAFORMA);

    // Enemigos que caminan
    agregarCaminante(600.0f,  SUELO_Y, 450.0f,  850.0f);
    agregarCaminante(1350.0f, SUELO_Y, 1150.0f, 1500.0f);
    agregarCaminante(1800.0f, SUELO_Y, 1650.0f, 2050.0f);

    // Enemigos voladores
    agregarVolador(1250.0f, 410.0f, 1200.0f, 1550.0f);
    agregarVolador(1900.0f, 430.0f, 1850.0f, 2250.0f);

    // Jefe estatico al final del nivel
    jefe = new JefeMapa1(2380.0f, SUELO_Y - 90.0f);
}

void Nivel::disenarNivel2() {
    // Suelo con dos huecos (1000-1180 y 2400-2580)
    mapa.agregarPlataforma(0.0f,    SUELO_Y, 1000.0f, ALTO_SUELO);
    mapa.agregarPlataforma(1180.0f, SUELO_Y, 1220.0f, ALTO_SUELO);
    mapa.agregarPlataforma(2580.0f, SUELO_Y, 1260.0f, ALTO_SUELO);

    // Plataformas
    mapa.agregarPlataforma(300.0f,  490.0f, 180.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(560.0f,  410.0f, 160.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(1030.0f, 500.0f, 100.0f, ALTO_PLATAFORMA);   // sobre el hueco
    mapa.agregarPlataforma(1400.0f, 480.0f, 200.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(1700.0f, 400.0f, 180.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(2000.0f, 490.0f, 200.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(2430.0f, 500.0f, 120.0f, ALTO_PLATAFORMA);   // sobre el hueco
    mapa.agregarPlataforma(2800.0f, 480.0f, 200.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(3100.0f, 400.0f, 180.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(3400.0f, 490.0f, 200.0f, ALTO_PLATAFORMA);

    // Enemigos que caminan por el suelo
    agregarCaminante(600.0f,  SUELO_Y, 450.0f,  850.0f);
    agregarCaminante(1300.0f, SUELO_Y, 1200.0f, 1500.0f);
    agregarCaminante(1700.0f, SUELO_Y, 1550.0f, 1850.0f);
    agregarCaminante(2100.0f, SUELO_Y, 1950.0f, 2350.0f);
    agregarCaminante(2800.0f, SUELO_Y, 2600.0f, 3000.0f);
    agregarCaminante(3150.0f, SUELO_Y, 3050.0f, 3350.0f);
    agregarCaminante(3450.0f, SUELO_Y, 3350.0f, 3550.0f);

    // Enemigos que caminan sobre plataformas
    agregarCaminante(1450.0f, 480.0f, 1400.0f, 1600.0f);
    agregarCaminante(2050.0f, 490.0f, 2000.0f, 2200.0f);

    // Enemigos voladores
    agregarVolador(700.0f,  430.0f, 650.0f,  1000.0f);
    agregarVolador(1300.0f, 440.0f, 1250.0f, 1650.0f);
    agregarVolador(1900.0f, 420.0f, 1850.0f, 2300.0f);
    agregarVolador(2700.0f, 440.0f, 2650.0f, 3000.0f);
    agregarVolador(3200.0f, 430.0f, 3150.0f, 3500.0f);

    // Jefe estatico al final del nivel
    jefe = new JefeMapa2(3640.0f, SUELO_Y - 85.0f);
}

void Nivel::disenarNivel3() {
    // Una sola pantalla. El jefe esta ABAJO, en el centro, y debajo no hay suelo:
    // si el jugador cae al centro toca al jefe; si cae por los lados, cae al vacio.
    mapa.agregarPlataforma(0.0f,    SUELO_Y, 260.0f, ALTO_SUELO);   // zona segura izquierda
    mapa.agregarPlataforma(1020.0f, SUELO_Y, 260.0f, ALTO_SUELO);   // zona segura derecha

    // Escalera de plataformas hacia el centro (simetrica)
    mapa.agregarPlataforma(290.0f, 510.0f, 140.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(480.0f, 430.0f, 130.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(590.0f, 340.0f, 100.0f, ALTO_PLATAFORMA);   // justo encima del jefe
    mapa.agregarPlataforma(670.0f, 430.0f, 130.0f, ALTO_PLATAFORMA);
    mapa.agregarPlataforma(850.0f, 510.0f, 140.0f, ALTO_PLATAFORMA);

    // Jefe: 110 de ancho x 100 de alto, centrado y pegado al borde de abajo
    jefe = new JefeMapa3(640.0f - 55.0f, 620.0f);
}

// ---------------------------------------------------------------------------
// Actualizar, dibujar, camara
// ---------------------------------------------------------------------------

bool Nivel::actualizar(float dt, Jugador& jugador) {
    tiempo += dt; //temp del nivel

    // 1) Mover enemigos y jefe
    for (int i = 0; i < cantidadEnemigos; i++) {
        enemigos[i]->actualizar(dt);
    }
    if (jefe != nullptr) {
        jefe->actualizar(dt);
    }

    // 2) Balas del jugador contra enemigos y jefe (el danio es 1: los virus mueren de 1 golpe)
    Arma& balas = jugador.getArma();
    for (int i = 0; i < cantidadEnemigos; i++) {
        if (enemigos[i]->estaVivo()) {
            balas.procesarImpactos(*enemigos[i]);
        }
    }
    if (jefe != nullptr && jefe->estaVivo()) {
        balas.procesarImpactos(*jefe);
    }

    // 3) Todo lo que puede golpear al jugador
    bool golpeado = false;

    if (jugador.getY() > LIMITE_CAIDA) {
        golpeado = true;                       // cayo al vacio
    }

    for (int i = 0; i < cantidadEnemigos; i++) {
        if (!enemigos[i]->estaVivo()) continue;
        if (jugador.colisionaCon(*enemigos[i]) || enemigos[i]->impactaA(jugador)) {
            golpeado = true;
        }
    }

    if (jefe != nullptr && jefe->estaVivo()) {
        if (jugador.colisionaCon(*jefe) || jefe->impactaA(jugador)) {
            golpeado = true;
        }
    }

    return golpeado;
}

void Nivel::dibujar(sf::RenderWindow& ventana) const {
    mapa.dibujar(ventana);

    for (int i = 0; i < cantidadEnemigos; i++) {
        enemigos[i]->dibujar(ventana);
    }
    if (jefe != nullptr) {
        jefe->dibujar(ventana);
    }
}

void Nivel::actualizarCamara(sf::View& camara, float jugadorX, float anchoVentana, float altoVentana) const {
    float mitadAncho = anchoVentana * 0.5f;
    float maxCentroX = static_cast<float>(mapa.getAncho()) - mitadAncho;

    float centroX = jugadorX;
    if (centroX < mitadAncho) {
        centroX = mitadAncho; //bloqueo de la cam en el borde izq
    } else if (centroX > maxCentroX && maxCentroX >= mitadAncho) {
        centroX = maxCentroX; // bloqueo en el borde dcho
    }

    camara.setSize(anchoVentana, altoVentana);
    camara.setCenter(centroX, altoVentana * 0.5f);
}

bool Nivel::jefeDerrotado() const {
    return jefe == nullptr || !jefe->estaVivo();   // true si el jefe es derrotado
}

Mapa& Nivel::getMapa() {
    return mapa;
}

const Mapa& Nivel::getMapa() const {
    return mapa;
}
