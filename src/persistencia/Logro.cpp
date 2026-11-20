#include "persistencia/Logro.h"
#include <iostream>
#include <sstream>

namespace {
    const int LARGO_LINEA = 100;

    // Copia como mucho max-1 caracteres y siempre termina en '\0'.
    // Los caracteres de control se cambian por espacio para no romper el archivo.
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
}

Logro::Logro() : id(0), desbloqueado(false) {
    nombre[0] = '\0';
    descripcion[0] = '\0';
}

Logro::Logro(int idLogro, const char* nombreLogro, const char* descripcionLogro)
    : id(idLogro), desbloqueado(false)
{
    if (id < 0) id = 0;
    copiarTexto(nombre, nombreLogro, MAX_NOMBRE);
    copiarTexto(descripcion, descripcionLogro, MAX_DESCRIPCION);
}

int Logro::getId() const { return id; }
const char* Logro::getNombre() const { return nombre; }
const char* Logro::getDescripcion() const { return descripcion; }

void Logro::desbloquear() { desbloqueado = true; }
bool Logro::estaDesbloqueado() const { return desbloqueado; }

bool Logro::operator==(const Logro& otro) const {
    return id == otro.id;
}

void Logro::mostrar() const {
    std::cout << (desbloqueado ? "[x] " : "[ ] ") << nombre << " - " << descripcion << "\n";
}

bool Logro::guardar(std::ofstream& salida) const {
    salida << id << ' ' << (desbloqueado ? 1 : 0) << '\n'
           << nombre << '\n' << descripcion << '\n';
    return salida.good();
}

bool Logro::cargar(std::ifstream& entrada) {
    char linea[LARGO_LINEA];
    char nombreLeido[MAX_NOMBRE];
    char descripcionLeida[MAX_DESCRIPCION];

    // Linea 1: id y estado. Se separa con un istringstream.
    entrada.getline(linea, LARGO_LINEA);
    if (!entrada) return false;

    std::istringstream datos(linea);
    int idLeido = 0;
    int estadoLeido = 0;
    datos >> idLeido >> estadoLeido;
    if (!datos) return false;

    // Lineas 2 y 3: nombre y descripcion.
    entrada.getline(nombreLeido, MAX_NOMBRE);
    if (!entrada) return false;
    entrada.getline(descripcionLeida, MAX_DESCRIPCION);
    if (!entrada) return false;

    if (idLeido <= 0 || (estadoLeido != 0 && estadoLeido != 1)) return false;

    id = idLeido;
    desbloqueado = (estadoLeido == 1);
    copiarTexto(nombre, nombreLeido, MAX_NOMBRE);
    copiarTexto(descripcion, descripcionLeida, MAX_DESCRIPCION);
    return true;
}
