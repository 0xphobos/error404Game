#include "mundo/Plataforma.h"
#include <algorithm>

// Texturas compartidas: se cargan una sola vez y permanecen vivas
// mientras SFML las utiliza. El juego se ejecuta desde la carpeta raiz.
namespace {
    sf::Texture& texturaPlataforma() {
        static sf::Texture textura;
        static bool cargada = textura.loadFromFile("assets/plataforma.png");
        if (cargada) {
            textura.setRepeated(true);
        }
        return textura;
    }

    sf::Texture& texturaPiso() {
        static sf::Texture textura;
        static bool cargada = textura.loadFromFile("assets/piso.png");
        if (cargada) {
            textura.setRepeated(true);
        }
        return textura;
    }
}

Plataforma::Plataforma()
    : x(0.0f), y(0.0f), ancho(0.0f), alto(0.0f) {
    configurar(0.0f, 0.0f, 0.0f, 0.0f);
}

Plataforma::Plataforma(float x, float y, float ancho, float alto)
    : x(x), y(y), ancho(ancho), alto(alto) {
    configurar(x, y, ancho, alto);
}

void Plataforma::configurar(float nuevaX, float nuevaY,
                            float nuevoAncho, float nuevoAlto) {
    x = nuevaX;
    y = nuevaY;
    ancho = nuevoAncho;
    alto = nuevoAlto;

    forma.setPosition(x, y);
    forma.setSize(sf::Vector2f(ancho, alto));

    // En prueba2, el piso tiene 120 px de alto y las plataformas elevadas 20 px.
    // Solo cambia la apariencia; la caja de colision permanece intacta.
    const bool esPiso = (alto >= 100.0f);
    sf::Texture& textura = esPiso ? texturaPiso() : texturaPlataforma();

    if (textura.getSize().x > 0 && textura.getSize().y > 0) {
        forma.setTexture(&textura, true);
        forma.setTextureRect(sf::IntRect(
            0, 0,
            static_cast<int>(ancho),
            static_cast<int>(alto)
        ));
        forma.setFillColor(sf::Color::White);
    } else {
        // Respaldo si los PNG no se encuentran.
        forma.setTexture(nullptr);
        forma.setFillColor(esPiso
            ? sf::Color(35, 35, 45)
            : sf::Color(65, 65, 78));
    }
}

sf::FloatRect Plataforma::getBounds() const {
    return sf::FloatRect(x, y, ancho, alto);
}

void Plataforma::dibujar(sf::RenderWindow& ventana) const {
    ventana.draw(forma);
}
