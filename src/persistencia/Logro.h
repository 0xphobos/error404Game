#pragma once
#include <fstream>

// Un logro del juego (por ejemplo "Intocable"). Empieza bloqueado y se
// desbloquea una vez. Sin string: texto en arreglos de char.
//
// Formato en data/logros.txt (3 lineas por logro):
//     2 1                      <- id  desbloqueado(0/1)
//     Sin bugs                 <- nombre
//     Completa el juego        <- descripcion
class Logro {
public:
    static const int MAX_NOMBRE = 30;
    static const int MAX_DESCRIPCION = 80;

private:
    int id;
    char nombre[MAX_NOMBRE];
    char descripcion[MAX_DESCRIPCION];
    bool desbloqueado;

public:
    Logro();
    Logro(int idLogro, const char* nombreLogro, const char* descripcionLogro);

    int getId() const;
    const char* getNombre() const;
    const char* getDescripcion() const;

    void desbloquear();
    bool estaDesbloqueado() const;

    // Dos logros son iguales si tienen el mismo id.
    bool operator==(const Logro& otro) const;

    void mostrar() const;                          // imprime en consola (depuracion)
    bool guardar(std::ofstream& salida) const;
    // Lee un logro. Si falla devuelve false y deja el objeto como estaba.
    bool cargar(std::ifstream& entrada);
};
