#pragma once
#include "persistencia/Partida.h"
#include "persistencia/Record.h"
#include "persistencia/Logro.h"

// Se encarga de todo lo que se lee y escribe en archivos: la partida guardada,
// los records y los logros. Cada clase de datos sabe leerse y escribirse
// (guardar/cargar); el gestor decide en que archivo y se ocupa de ordenar y buscar.
//
// Sin vector: las colecciones son arreglos que pasa quien llama
// (por ejemplo "Record records[GestorArchivos::MAX_RECORDS];").
//
// Las rutas son relativas a la carpeta desde donde se ejecuta el juego
// (CMake copia data/ junto al ejecutable). Si la carpeta no existe, guardar
// devuelve false y cargar devuelve 0 / false; el juego no se rompe.
class GestorArchivos {
public:
    static const int MAX_RECORDS = 50;    // el archivo conserva los 50 mejores
    static const int MAX_LOGROS = 20;

private:
    const char* rutaPartida;
    const char* rutaRecords;
    const char* rutaLogros;

public:
    GestorArchivos();   // data/partida.txt, data/records.txt, data/logros.txt
    GestorArchivos(const char* archivoPartida, const char* archivoRecords,
                   const char* archivoLogros);

    // --- Partida (un solo registro; guardar reemplaza el anterior) ---
    bool guardarPartida(const Partida& partida) const;
    bool cargarPartida(Partida& partida) const;          // false si no hay partida valida

    // --- Records ---
    // Agrega el record, ordena y conserva solo los MAX_RECORDS mejores.
    bool guardarRecord(const Record& record) const;
    // Llena 'destino' con hasta 'max' records; devuelve cuantos leyo.
    int cargarRecords(Record* destino, int max) const;
    // Ordena de mejor a peor (insercion, usando operator<).
    void ordenarRecords(Record* v, int n) const;
    // Sobrecarga de buscarRecord: por nombre o por nivel. Devuelven el indice o -1.
    int buscarRecord(const char* nombre, const Record* v, int n) const;   // primero con ese nombre
    int buscarRecord(int nivel, const Record* v, int n) const;            // el mejor de ese nivel

    // --- Logros ---
    bool guardarLogros(const Logro* v, int n) const;
    // Si el archivo no existe o esta vacio, crea los logros base y los guarda.
    int cargarLogros(Logro* destino, int max) const;
};
