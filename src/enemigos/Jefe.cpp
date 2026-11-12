
#include "enemigos/Jefe.h"

Jefe::Jefe(float x, float y,
           float ancho, float alto,
           int vida, float velocidad)
    : Enemigo(x, y, ancho, alto, vida, velocidad),
      vidaMaxima(vida),
      fase(1)
{
}

// Comprueba si el jefe debe cambiar de fase
void Jefe::actualizarFase()
{
    if (vidaMaxima <= 0)
    {
        return;
    }

    float porcentajeVida =
        static_cast<float>(vida) / vidaMaxima;

    if (porcentajeVida <= 0.30f)
    {
        fase = 3;
    }
    else if (porcentajeVida <= 0.60f)
    {
        fase = 2;
    }
    else
    {
        fase = 1;
    }
}

// Método que las clases hijas pueden personalizar
void Jefe::alCambiarFase(int nuevaFase)
{
    // Cada jefe podrá definir su propio comportamiento
    // cuando cambie de fase.
}

// Actualización común de los jefes
void Jefe::actualizar(float dt)
{
    int faseAnterior = fase;

    actualizarFase();

    if (fase != faseAnterior)
    {
        alCambiarFase(fase);
    }
}

// Obtener la fase actual
int Jefe::getFase() const
{
    return fase;
}

// Obtener la vida máxima
int Jefe::getVidaMaxima() const
{
    return vidaMaxima;
}
