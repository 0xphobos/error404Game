#include "persistencia/Partida.h"
#include <iostream>
#include <sstream>

namespace {
    const int NIVEL_MIN = 1;
    const int NIVEL_MAX = 3;
    const int VIDAS_MAX = 99;
    const int VIDAS_INICIALES = 3;
    const int LARGO_LINEA = 100;

    int limitar(int valor, int minimo, int maximo) {
        if (valor < minimo) return minimo;
        if (valor > maximo) return maximo;
        return valor;
    }
}

Partida::Partida()
    : nivelActual(NIVEL_MIN), vidas(VIDAS_INICIALES), puntaje(0), tiempoTotal(0.f) {}

Partida::Partida(int nivel, int numeroVidas, int puntos, float segundos)
    : nivelActual(limitar(nivel, NIVEL_MIN, NIVEL_MAX)),
      vidas(limitar(numeroVidas, 0, VIDAS_MAX)),
      puntaje(puntos < 0 ? 0 : puntos),
      tiempoTotal(segundos < 0.f ? 0.f : segundos) {}

int Partida::getNivelActual() const { return nivelActual; }
int Partida::getVidas() const { return vidas; }
int Partida::getPuntaje() const { return puntaje; }
float Partida::getTiempoTotal() const { return tiempoTotal; }

void Partida::setNivelActual(int nivel) {
    if (nivel >= NIVEL_MIN && nivel <= NIVEL_MAX) nivelActual = nivel;
}

void Partida::setVidas(int numeroVidas) {
    if (numeroVidas >= 0 && numeroVidas <= VIDAS_MAX) vidas = numeroVidas;
}

void Partida::sumarPuntaje(int puntos) {
    if (puntos > 0) puntaje += puntos;
}

void Partida::setTiempoTotal(float segundos) {
    if (segundos >= 0.f) tiempoTotal = segundos;
}

void Partida::mostrar() const {
    std::cout << "Nivel " << nivelActual << "  vidas " << vidas << "  puntaje " << puntaje
              << "  tiempo " << tiempoTotal << " s\n";
}

bool Partida::guardar(std::ofstream& salida) const {
    salida << nivelActual << ' ' << vidas << ' ' << puntaje << ' ' << tiempoTotal << '\n';
    return salida.good();
}

bool Partida::cargar(std::ifstream& entrada) {
    char linea[LARGO_LINEA];
    entrada.getline(linea, LARGO_LINEA);
    if (!entrada) return false;

    std::istringstream datos(linea);
    int nivelLeido = 0;
    int vidasLeidas = 0;
    int puntajeLeido = 0;
    float tiempoLeido = 0.f;
    datos >> nivelLeido >> vidasLeidas >> puntajeLeido >> tiempoLeido;
    if (!datos) return false;

    if (nivelLeido < NIVEL_MIN || nivelLeido > NIVEL_MAX) return false;
    if (vidasLeidas < 0 || vidasLeidas > VIDAS_MAX) return false;
    if (puntajeLeido < 0 || tiempoLeido < 0.f) return false;

    nivelActual = nivelLeido;
    vidas = vidasLeidas;
    puntaje = puntajeLeido;
    tiempoTotal = tiempoLeido;
    return true;
}
