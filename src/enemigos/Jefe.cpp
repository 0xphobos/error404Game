
#include "enemigos/Jefe.h"

Jefe::Jefe(float x, float y,
           float ancho, float alto,
           int vida, float velocidad)
    : Enemigo(x, y, ancho, alto, vida, velocidad),
      vidaMaxima(vida),
      fase(1)
{
}

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

void Jefe::alCambiarFase(int nuevaFase)
{
}

void Jefe::actualizar(float dt)
{
    int faseAnterior = fase;

    actualizarFase();

    if (fase != faseAnterior)
    {
        alCambiarFase(fase);
    }

    actualizarArma(dt);
}

int Jefe::getFase() const
{
    return fase;
}

int Jefe::getVidaMaxima() const
{
    return vidaMaxima;
}

void Jefe::dibujarBarraVida(sf::RenderWindow& ventana) const
{
    if (vidaMaxima <= 0)
    {
        return;
    }

    float porcentaje = static_cast<float>(vida) / vidaMaxima;

    sf::RectangleShape fondo(sf::Vector2f(ancho, 8.f));
    fondo.setPosition(x, y - 16.f);
    fondo.setFillColor(sf::Color(60, 60, 60));
    ventana.draw(fondo);

    sf::RectangleShape barra(sf::Vector2f(ancho * porcentaje, 8.f));
    barra.setPosition(x, y - 16.f);
    barra.setFillColor(sf::Color(220, 50, 60));
    ventana.draw(barra);
}
