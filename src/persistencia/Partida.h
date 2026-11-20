#pragma once
#include <fstream>

// Estado de una partida guardada: nivel, vidas, puntaje y tiempo acumulado.
//
// Formato en data/partida.txt (1 linea):
//     2 3 1500 95.5        <- nivel  vidas  puntaje  tiempo(s)
class Partida {
private:
    int nivelActual;     // 1..3
    int vidas;           // 0..99
    int puntaje;         // >= 0
    float tiempoTotal;   // segundos, >= 0

public:
    Partida();                                       // partida nueva: nivel 1, 3 vidas
    // Los valores invalidos se corrigen al rango permitido.
    Partida(int nivel, int numeroVidas, int puntos, float segundos);

    int getNivelActual() const;
    int getVidas() const;
    int getPuntaje() const;
    float getTiempoTotal() const;

    // Los setters ignoran los valores fuera de rango (encapsulamiento).
    void setNivelActual(int nivel);
    void setVidas(int numeroVidas);
    void sumarPuntaje(int puntos);                   // solo suma si puntos > 0
    void setTiempoTotal(float segundos);

    void mostrar() const;                            // imprime en consola (depuracion)
    bool guardar(std::ofstream& salida) const;
    // Lee una partida. Si falla devuelve false y deja el objeto como estaba.
    bool cargar(std::ifstream& entrada);
};
