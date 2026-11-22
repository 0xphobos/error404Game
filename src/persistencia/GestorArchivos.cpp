#include "persistencia/GestorArchivos.h"

namespace {
    const int LOGROS_BASE = 4;

    // Logros con los que empieza el juego (el archivo se crea con estos).
    int logrosPorDefecto(Logro* destino, int max) {
        Logro base[LOGROS_BASE] = {
            Logro(1, "Antivirus",  "Derrota al primer jefe"),
            Logro(2, "Sin bugs",   "Completa el juego"),
            Logro(3, "Intocable",  "Vence a un jefe sin recibir dano"),
            Logro(4, "Velocista",  "Completa un nivel en menos de 2 minutos")
        };
        int cantidad = (max < LOGROS_BASE) ? max : LOGROS_BASE;
        for (int i = 0; i < cantidad; i++) destino[i] = base[i];
        return cantidad;
    }
}

GestorArchivos::GestorArchivos()
    : rutaPartida("data/partida.txt"),
      rutaRecords("data/records.txt"),
      rutaLogros("data/logros.txt") {}

GestorArchivos::GestorArchivos(const char* archivoPartida, const char* archivoRecords,
                               const char* archivoLogros)
    : rutaPartida(archivoPartida),
      rutaRecords(archivoRecords),
      rutaLogros(archivoLogros) {}

// ---------------------------------------------------------------------------
// Partida
// ---------------------------------------------------------------------------

bool GestorArchivos::guardarPartida(const Partida& partida) const {
    std::ofstream salida(rutaPartida);
    if (!salida) return false;
    return partida.guardar(salida);
}

bool GestorArchivos::cargarPartida(Partida& partida) const {
    std::ifstream entrada(rutaPartida);
    if (!entrada) return false;
    return partida.cargar(entrada);
}

// ---------------------------------------------------------------------------
// Records
// ---------------------------------------------------------------------------

bool GestorArchivos::guardarRecord(const Record& record) const {
    // Lee los existentes, agrega el nuevo, ordena y se queda con los mejores.
    Record todos[MAX_RECORDS + 1];
    int cantidad = cargarRecords(todos, MAX_RECORDS);

    todos[cantidad] = record;
    cantidad++;
    ordenarRecords(todos, cantidad);
    if (cantidad > MAX_RECORDS) cantidad = MAX_RECORDS;

    std::ofstream salida(rutaRecords);
    if (!salida) return false;
    for (int i = 0; i < cantidad; i++) {
        if (!todos[i].guardar(salida)) return false;
    }
    return true;
}

int GestorArchivos::cargarRecords(Record* destino, int max) const {
    if (destino == nullptr || max <= 0) return 0;

    std::ifstream entrada(rutaRecords);
    if (!entrada) return 0;

    int cantidad = 0;
    while (cantidad < max && destino[cantidad].cargar(entrada)) {
        cantidad++;
    }
    return cantidad;
}

void GestorArchivos::ordenarRecords(Record* v, int n) const {
    if (v == nullptr) return;

    // Ordenamiento por insercion usando operator< (el mejor record queda primero).
    for (int i = 1; i < n; i++) {
        Record clave = v[i];
        int j = i - 1;
        while (j >= 0 && clave < v[j]) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = clave;
    }
}

int GestorArchivos::buscarRecord(const char* nombre, const Record* v, int n) const {
    if (v == nullptr || nombre == nullptr) return -1;

    for (int i = 0; i < n; i++) {
        if (v[i].tieneNombre(nombre)) return i;
    }
    return -1;
}

int GestorArchivos::buscarRecord(int nivel, const Record* v, int n) const {
    if (v == nullptr) return -1;

    int mejor = -1;
    for (int i = 0; i < n; i++) {
        if (v[i].getNivel() == nivel && (mejor == -1 || v[i] < v[mejor])) {
            mejor = i;
        }
    }
    return mejor;
}

// ---------------------------------------------------------------------------
// Logros
// ---------------------------------------------------------------------------

bool GestorArchivos::guardarLogros(const Logro* v, int n) const {
    if (v == nullptr && n > 0) return false;

    std::ofstream salida(rutaLogros);
    if (!salida) return false;
    for (int i = 0; i < n; i++) {
        if (!v[i].guardar(salida)) return false;
    }
    return true;
}

int GestorArchivos::cargarLogros(Logro* destino, int max) const {
    if (destino == nullptr || max <= 0) return 0;

    int cantidad = 0;
    std::ifstream entrada(rutaLogros);
    if (entrada) {
        while (cantidad < max && destino[cantidad].cargar(entrada)) {
            cantidad++;
        }
    }

    if (cantidad == 0) {
        // Primera vez (o archivo vacio/danado): se crean los logros base
        // y se guardan para que el archivo quede listo.
        cantidad = logrosPorDefecto(destino, max);
        guardarLogros(destino, cantidad);
    }
    return cantidad;
}
