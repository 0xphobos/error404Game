#include "entidades/Jugador.h"
#include "mundo/Mapa.h"
#include "recursos/Sprites.h"

//valores ajustables xd
const float VELOCIDAD_X = 300.f; //pxls por seg
const float GRAVEDAD = 1800.f;  //pxls por seg para grav
const float FUERZA_SALTO = -760.f; //negativo porq va hacia arriba (sube unos 160 px)
const float SUELO_Y = 600.f; //solo se usa si el jugador no tiene mapa
const float CADENCIA_DISPARO = 0.2f;  //segundos entre disparos
const float VELOCIDAD_BALA = 700.f;   //pxls por seg
const float MARGEN_ATERRIZAJE = 2.f;  //tolerancia para "venia desde arriba de la plataforma"

Jugador::Jugador(float x, float y)
    : Entidad(x,y,40.f,70.f,3),
      velocidadY(0.f),
      enSuelo(false),
      mirandoDireccion(true),
      arma(CADENCIA_DISPARO, 1, VELOCIDAD_BALA, true),
      mapa(nullptr)
{
}

void Jugador::actualizar(float dt){
    procesarEntrada(dt);
    aplicarFisica(dt);
    disparar();
    arma.actualizar(dt);
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

    // No salirse de los bordes del mapa
    if (mapa != nullptr) {
        float limiteDerecho = static_cast<float>(mapa->getAncho()) - ancho;
        if (x < 0.f) x = 0.f;
        if (x > limiteDerecho) x = limiteDerecho;
    }

    bool quiereSaltar = sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
    if (quiereSaltar && enSuelo) {
        velocidadY = FUERZA_SALTO;     // impulso hacia arriba
        enSuelo = false;
    }
}

void Jugador::aplicarFisica(float dt){
    float yAnterior = y;               // donde estaba antes de moverse este fotograma

    velocidadY += GRAVEDAD * dt;
    y += velocidadY * dt;
    enSuelo = false;

    if (mapa == nullptr) {
        // Sin mapa: un suelo fijo
        if (y + alto >= SUELO_Y) {
            y = SUELO_Y - alto;
            velocidadY = 0.f;
            enSuelo = true;
        }
        return;
    }

    // Plataformas "de un solo sentido": solo se aterriza sobre ellas cayendo desde arriba.
    // Desde abajo se pueden atravesar (asi se puede saltar de una a otra).
    if (velocidadY < 0.f) return;      // subiendo: no hay nada que revisar

    for (int i = 0; i < mapa->getCantidadPlataformas(); i++) {
        sf::FloatRect p = mapa->getPlataforma(i).getBounds();

        bool estaSobreLaPlataforma = x + ancho > p.left && x < p.left + p.width;
        bool veniaDeArriba = yAnterior + alto <= p.top + MARGEN_ATERRIZAJE;
        bool llegoALaTapa = y + alto >= p.top;

        if (estaSobreLaPlataforma && veniaDeArriba && llegoALaTapa) {
            y = p.top - alto;
            velocidadY = 0.f;
            enSuelo = true;
        }
    }
}

// Las flechas disparan. Si se pulsan dos a la vez, la bala sale en diagonal.
void Jugador::disparar() {
    float dirX = 0.f;
    float dirY = 0.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) dirX += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  dirX -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  dirY += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    dirY -= 1.f;

    if (dirX == 0.f && dirY == 0.f) return;   // ninguna flecha: no dispara

    // La bala sale del centro del jugador. Arma respeta la cadencia.
    arma.dispararHacia(x + ancho / 2.f, y + alto / 2.f, dirX, dirY);
}

void Jugador::dibujar(sf::RenderWindow& ventana) {
    // El sprite ocupa el mismo rectangulo que la hitbox: la fisica no cambia.
    if (!Sprites::dibujar(ventana, "assets/sprites/jugador.png",
                         x, y, ancho, alto, !mirandoDireccion)) {
        sf::RectangleShape forma(sf::Vector2f(ancho, alto));
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color(70, 130, 230));
        ventana.draw(forma);
    }

    arma.dibujar(ventana);
}

void Jugador::setMapa(const Mapa* nuevoMapa) {
    mapa = nuevoMapa;
}

void Jugador::reiniciar(float nuevaX, float nuevaY) {
    x = nuevaX;
    y = nuevaY;
    velocidadY = 0.f;
    enSuelo = false;
    mirandoDireccion = true;
    arma.limpiar();
}

Arma& Jugador::getArma() {
    return arma;
}

bool Jugador::estaMirandoDireccion() const {
    return mirandoDireccion;
}
