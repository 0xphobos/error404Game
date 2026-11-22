
#include "enemigos/Enemigo.h"

Enemigo::Enemigo(float x, float y,
                 float ancho, float alto,
                 int vida, float velocidad)
    : Entidad(x, y, ancho, alto, vida),
      velocidad(velocidad),
      mirandoDerecha(true),
      arma()
{
}

void Enemigo::moverHorizontal(float dt)
{
    if (mirandoDerecha)
    {
        x += velocidad * dt;
    }
    else
    {
        x -= velocidad * dt;
    }
}

void Enemigo::invertirDireccion()
{
    mirandoDerecha = !mirandoDerecha;
}

void Enemigo::actualizarArma(float dt)
{
    arma.actualizar(dt);
}

void Enemigo::dibujarArma(sf::RenderWindow& ventana)
{
    arma.dibujar(ventana);
}

int Enemigo::procesarImpactos(Entidad& objetivo)
{
    return arma.procesarImpactos(objetivo);
}

bool Enemigo::impactaA(const Entidad& objetivo)
{
    return arma.hayImpacto(objetivo);
}

float Enemigo::getVelocidad() const
{
    return velocidad;
}

bool Enemigo::estaMirandoDerecha() const
{
    return mirandoDerecha;
}
