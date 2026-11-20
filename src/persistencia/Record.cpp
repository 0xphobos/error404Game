#include "persistencia/Record.h"
#include <iostream>
#include <sstream>

namespace {
    const int NIVEL_MIN = 1;
    const int NIVEL_MAX = 3;
    const int LARGO_LINEA = 100;

    // Copia como mucho max-1 caracteres y siempre termina en '\0'.
    // Los caracteres de control (como '\n') se cambian por espacio para no
    // romper el formato del archivo.
    void copiarTexto(char* destino, const char* origen, int max) {
        int i = 0;
        if (origen != nullptr) {
            while (origen[i] != '\0' && i < max - 1) {
                bool control = static_cast<unsigned char>(origen[i]) < 32;
                destino[i] = control ? ' ' : origen[i];
                i++;
            }
        }
        destino[i] = '\0';
    }

    bool textosIguales(const char* a, const char* b) {
        int i = 0;
        while (a[i] != '\0' && a[i] == b[i]) i++;
        return a[i] == b[i];
    }
}

Record::Record() : nivel(NIVEL_MIN), tiempo(0.f), puntaje(0) {
    nombre[0] = '\0';
}

Record::Record(const char* nombreJugador, int nivelAlcanzado, float segundos, int puntos)
    : nivel(nivelAlcanzado), tiempo(segundos), puntaje(puntos)
{
    copiarTexto(nombre, nombreJugador, MAX_NOMBRE);
    if (nivel < NIVEL_MIN) nivel = NIVEL_MIN;
    if (nivel > NIVEL_MAX) nivel = NIVEL_MAX;
    if (tiempo < 0.f) tiempo = 0.f;
    if (puntaje < 0) puntaje = 0;
}

const char* Record::getNombre() const { return nombre; }
int Record::getNivel() const { return nivel; }
float Record::getTiempo() const { return tiempo; }
int Record::getPuntaje() const { return puntaje; }

bool Record::tieneNombre(const char* otroNombre) const {
    if (otroNombre == nullptr) return false;
    return textosIguales(nombre, otroNombre);
}

bool Record::operator<(const Record& otro) const {
    if (tiempo != otro.tiempo) return tiempo < otro.tiempo;
    return puntaje > otro.puntaje;
}

bool Record::operator==(const Record& otro) const {
    return textosIguales(nombre, otro.nombre) && nivel == otro.nivel &&
           tiempo == otro.tiempo && puntaje == otro.puntaje;
}

void Record::mostrar() const {
    std::cout << nombre << "  nivel " << nivel << "  " << tiempo << " s  "
              << puntaje << " pts\n";
}

bool Record::guardar(std::ofstream& salida) const {
    salida << nombre << '\n' << nivel << ' ' << tiempo << ' ' << puntaje << '\n';
    return salida.good();
}

bool Record::cargar(std::ifstream& entrada) {
    char nombreLeido[MAX_NOMBRE];
    char linea[LARGO_LINEA];

    // Linea 1: el nombre (falla en fin de archivo o si es demasiado largo).
    entrada.getline(nombreLeido, MAX_NOMBRE);
    if (!entrada) return false;

    // Linea 2: nivel, tiempo y puntaje. Se separa con un istringstream.
    entrada.getline(linea, LARGO_LINEA);
    if (!entrada) return false;

    std::istringstream datos(linea);
    int nivelLeido = 0;
    float tiempoLeido = 0.f;
    int puntajeLeido = 0;
    datos >> nivelLeido >> tiempoLeido >> puntajeLeido;
    if (!datos) return false;

    if (nivelLeido < NIVEL_MIN || nivelLeido > NIVEL_MAX) return false;
    if (tiempoLeido < 0.f || puntajeLeido < 0) return false;

    copiarTexto(nombre, nombreLeido, MAX_NOMBRE);
    nivel = nivelLeido;
    tiempo = tiempoLeido;
    puntaje = puntajeLeido;
    return true;
}
