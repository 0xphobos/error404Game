#pragma once

// Estados posibles del juego. Juego decide que actualizar y dibujar segun este valor.
enum class EstadoJuego {
    MENU,
    JUGANDO,
    RECORDS,
    LOGROS,
    GAME_OVER,
    SALIR
};
