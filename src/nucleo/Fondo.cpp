#include "nucleo/Fondo.h"

namespace {
    const float FACTOR_PARALAJE = 0.5f;   // velocidad relativa de un fondo que se repite
}

Fondo::Fondo() : cargado(false), escala(1.f) {}

bool Fondo::cargar(const char* ruta, float altoVentana) {
    cargado = textura.loadFromFile(ruta);
    if (!cargado) return false;

    sprite.setTexture(textura, true);
    // Se escala para que la imagen tenga el mismo alto que la ventana.
    escala = altoVentana / static_cast<float>(textura.getSize().y);
    sprite.setScale(escala, escala);
    return true;
}

bool Fondo::estaCargado() const {
    return cargado;
}

void Fondo::dibujarEstirado(sf::RenderWindow& ventana, float anchoVentana,
                            float altoVentana) const {
    if (!cargado) return;

    sf::Sprite completo(sprite);
    completo.setScale(anchoVentana / static_cast<float>(textura.getSize().x),
                      altoVentana / static_cast<float>(textura.getSize().y));
    completo.setPosition(0.f, 0.f);
    ventana.draw(completo);
}

void Fondo::dibujarConScroll(sf::RenderWindow& ventana, float izquierdaCamara,
                             float anchoVentana, float anchoMapa) const {
    if (!cargado) return;

    float anchoPieza = static_cast<float>(textura.getSize().x) * escala;
    if (anchoPieza <= 0.f) return;

    // Imagen del tamano del mapa: se mueve con el mundo (factor 1).
    // Imagen mas angosta: se repite y avanza mas despacio que el mundo.
    float factor = (anchoPieza >= anchoMapa) ? 1.f : FACTOR_PARALAJE;

    float desplazamiento = izquierdaCamara * factor;
    if (desplazamiento < 0.f) desplazamiento = 0.f;
    // Se queda con el resto dentro de una pieza (sin usar cmath).
    desplazamiento -= static_cast<int>(desplazamiento / anchoPieza) * anchoPieza;

    // Se dibujan piezas pegadas hasta cubrir todo el ancho de la ventana.
    float x = izquierdaCamara - desplazamiento;
    sf::Sprite pieza(sprite);
    while (x < izquierdaCamara + anchoVentana) {
        pieza.setPosition(x, 0.f);
        ventana.draw(pieza);
        x += anchoPieza;
    }
}
