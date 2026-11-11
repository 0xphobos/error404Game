#include <SFML/Graphics.hpp>

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