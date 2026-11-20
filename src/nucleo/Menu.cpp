#include "nucleo/Menu.h"

Menu::Menu() : fuenteCargada(false), seleccion(0) {
    opciones[0] = "Jugar";
    opciones[1] = "Records";
    opciones[2] = "Logros";
    opciones[3] = "Salir";
    // Pon un archivo .ttf en assets/fuentes/ con este nombre.
    // Si no existe, el menu se dibuja solo con cajas (sigue funcionando).
    fuenteCargada = fuente.loadFromFile("assets/fuentes/fuente.ttf");
}

bool Menu::manejarEvento(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return false;

    switch (evento.key.code) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            seleccion = (seleccion - 1 + TOTAL) % TOTAL;
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            seleccion = (seleccion + 1) % TOTAL;
            break;
        case sf::Keyboard::Return:
        case sf::Keyboard::Space:
            return true;
        default:
            break;
    }
    return false;
}

EstadoJuego Menu::estadoElegido() const {
    switch (seleccion) {
        case 0:  return EstadoJuego::JUGANDO;
        case 1:  return EstadoJuego::RECORDS;
        case 2:  return EstadoJuego::LOGROS;
        default: return EstadoJuego::SALIR;
    }
}

void Menu::dibujar(sf::RenderWindow& ventana) const {
    sf::Vector2u tam = ventana.getSize();
    float centroX = tam.x / 2.f;
    float yInicial = tam.y * 0.40f;
    float separacion = 70.f;

    if (fuenteCargada) {
        sf::Text titulo("RUN AND GUN", fuente, 56);
        sf::FloatRect b = titulo.getLocalBounds();
        titulo.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        titulo.setPosition(centroX, tam.y * 0.20f);
        titulo.setFillColor(sf::Color::White);
        ventana.draw(titulo);
    }

    for (int i = 0; i < TOTAL; i++) {
        bool activa = (i == seleccion);

        sf::RectangleShape caja(sf::Vector2f(300.f, 50.f));
        caja.setOrigin(150.f, 25.f);
        caja.setPosition(centroX, yInicial + i * separacion);
        caja.setFillColor(activa ? sf::Color(200, 60, 60) : sf::Color(60, 60, 80));
        ventana.draw(caja);

        if (fuenteCargada) {
            sf::Text texto(opciones[i], fuente, 28);
            sf::FloatRect b = texto.getLocalBounds();
            texto.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
            texto.setPosition(centroX, yInicial + i * separacion);
            texto.setFillColor(sf::Color::White);
            ventana.draw(texto);
        }
    }
}