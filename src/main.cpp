#include <SFML/Graphics.hpp>
//PRUEBA PANTALLA GRIS PARA VER SI COMPILA 
int main() {
    sf::RenderWindow ventana(sf::VideoMode(1280, 720), "Run and Gun");
    ventana.setFramerateLimit(60);
    sf::Clock reloj;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }
        float dt = reloj.restart().asSeconds();   // tiempo entre frames

        ventana.clear(sf::Color(30, 30, 40));
        // aquí se dibujará todo
        ventana.display();
    }
    return 0;
}

/* PRUEBA PARA MOVIMIENTO DE PERSONAJE
#include <SFML/Graphics.hpp>
#include "entidades/Jugador.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(1280, 720), "Run and Gun");
    ventana.setFramerateLimit(60);

    Jugador jugador(100.f, 100.f);     // objeto normal, sin new
    sf::Clock reloj;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        float dt = reloj.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f;    // evita saltos raros si la ventana se congela

        jugador.actualizar(dt);

        ventana.clear(sf::Color(30, 30, 40));

        sf::RectangleShape suelo(sf::Vector2f(1280.f, 120.f));   // suelo temporal
        suelo.setPosition(0.f, 600.f);
        suelo.setFillColor(sf::Color(60, 140, 70));
        ventana.draw(suelo);

        jugador.dibujar(ventana);
        ventana.display();
    }
    return 0;
}
*/