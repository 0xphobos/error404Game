#pragma once
#include <fstream>

// Un record de partida: quien jugo, hasta que nivel llego, en cuanto tiempo y
// con que puntaje. Sin string: el nombre es un arreglo de char de tamano fijo.
//
// Formato en data/records.txt (2 lineas por record):
//     Ana
//     3 142.5 4200        <- nivel  tiempo(s)  puntaje
class Record {
public:
    static const int MAX_NOMBRE = 30;   // incluye el '\0'

private:
    char nombre[MAX_NOMBRE];
    int nivel;        // 1..3
    float tiempo;     // segundos
    int puntaje;

public:
    Record();
    // Los valores invalidos se corrigen: nombre recortado, nivel entre 1 y 3,
    // tiempo y puntaje nunca negativos.
    Record(const char* nombreJugador, int nivelAlcanzado, float segundos, int puntos);

    const char* getNombre() const;
    int getNivel() const;
    float getTiempo() const;
    int getPuntaje() const;
    bool tieneNombre(const char* otroNombre) const;

    // "Menor" significa "mejor": menos tiempo; a igual tiempo, mas puntaje.
    // Asi, ordenar de menor a mayor deja el mejor record primero.
    bool operator<(const Record& otro) const;
    bool operator==(const Record& otro) const;

    void mostrar() const;                          // imprime en consola (depuracion)
    bool guardar(std::ofstream& salida) const;
    // Lee un record. Si falla (fin de archivo, formato roto, valores fuera de
    // rango) devuelve false y deja el objeto como estaba.
    bool cargar(std::ifstream& entrada);
};
