#include "entidades/Jugador.h"
//valores ajustables xd
const float VELOCIDAD_X = 300.f; //pxls por seg
const float GRAVEDAD = 1800.f;  //pxls por seg para grav
const float FUERZA_SALTO = -700.f; //negativo porq va hacia arriba
const float SUELO_Y = 600.f; //temporal

Jugador::Jugador(float x, float y) : Entidad(x,y,40.f,70.f,3),velocidadY(0.f),enSuelo(false),mirandoDireccion(true){}
void Jugador::actualizar(float dt){
    procesarEntrada(dt);
    aplicarFisica(dt);
}

void Jugador::procesarEntrada(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        x -= VELOCIDAD_X * dt;
        mirandoDireccion = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        x += VELOCIDAD_X * dt;
        mirandoDireccion = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && enSuelo) {
        velocidadY = FUERZA_SALTO;     // impulso hacia arriba
        enSuelo = false;
    }
}

void Jugador::aplicarFisica(float dt){
    velocidadY += GRAVEDAD * dt;
    y += velocidadY * dt;
    if(y + alto >= SUELO_Y){
        y = SUELO_Y - alto;
        velocidadY = 0.f;
        enSuelo = true;
    }
}
void Jugador::dibujar(sf::RenderWindow& ventana) {
    sf::RectangleShape forma(sf::Vector2f(ancho, alto));
    forma.setPosition(x, y);
    forma.setFillColor(sf::Color(70, 130, 230));
    ventana.draw(forma);
}

bool Jugador::estaMirandoDireccion() const {
    return mirandoDireccion;
}