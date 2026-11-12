
#include "enemigos/Enemigo.h"

// Constructor
Enemigo::Enemigo(float x, float y,
                 float ancho, float alto,
                 int vida, float velocidad)
    : Entidad(x, y, ancho, alto, vida),
      velocidad(velocidad),
      mirandoDerecha(true)
{
}

// Movimiento horizontal compartido
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

// Cambiar dirección
void Enemigo::invertirDireccion()
{
    mirandoDerecha = !mirandoDerecha;
}

// Obtener velocidad
float Enemigo::getVelocidad() const
{
    return velocidad;
}

// Consultar dirección
bool Enemigo::estaMirandoDerecha() const
{
    return mirandoDerecha;
}
