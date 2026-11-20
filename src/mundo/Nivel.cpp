#include "mundo/Nivel.h"

Nivel::Nivel(int numero, int anchoMapa)
    : numero(numero), tiempo(0.0f), mapa(anchoMapa), cantidadEnemigos(0), jefe(nullptr) {
    for (int i = 0; i < MAX_ENEMIGOS; i++) {
        enemigos[i] = nullptr;
    }
    cargarDisenoBase();
}

void Nivel::cargarDisenoBase() {
    mapa.limpiar();
    cantidadEnemigos = 0;

    // suelo y plataformas de prueba
    mapa.agregarPlataforma(0.0f, 600.0f, static_cast<float>(mapa.getAncho()), 120.0f);
    mapa.agregarPlataforma(350.0f, 470.0f, 220.0f, 24.0f);
    mapa.agregarPlataforma(720.0f, 360.0f, 240.0f, 24.0f);
    mapa.agregarPlataforma(1150.0f, 460.0f, 260.0f, 24.0f);

    std::cout << "Nivel " << numero << " cargado con "
              << mapa.getCantidadPlataformas() << " plataformas.\n";
}

void Nivel::actualizar(float dt) {
    tiempo += dt; //temp del nivel
}

void Nivel::dibujar(sf::RenderWindow& ventana) const {
    mapa.dibujar(ventana);
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
    return jefe == nullptr; // true si el jefe es derrotado
}

Mapa& Nivel::getMapa() {
    return mapa;
}

const Mapa& Nivel::getMapa() const {
    return mapa;
}