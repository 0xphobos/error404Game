#pragma once
#include <SFML/Graphics.hpp>

// Un fondo hecho con una imagen PNG. Sirve para el menu (la imagen se estira a
// toda la ventana) y para los niveles (la imagen sigue a la camara).
//
// Si el archivo no existe, el fondo "no esta cargado" y simplemente no dibuja
// nada: el juego sigue funcionando con el color liso de siempre.
//
// Tamanos recomendados (la ventana mide 1280 x 720):
//   - Menu:            1280 x 720 (o 1920 x 1080: misma proporcion 16:9).
//   - Fondo de nivel:  720 px de alto y
//         * 2560 px de ancho = el mapa completo, sin repetir; o
//         * 1280 px de ancho que se pueda repetir sin costura (se mueve mas
//           lento que el mapa, efecto "paralaje").
class Fondo {
private:
    sf::Texture textura;    // declarada antes que el sprite: el sprite apunta a ella
    sf::Sprite sprite;
    bool cargado;
    float escala;           // escala que iguala el alto de la imagen al de la ventana

public:
    Fondo();

    // El sprite apunta a la textura de este mismo objeto: no se puede copiar.
    Fondo(const Fondo&) = delete;
    Fondo& operator=(const Fondo&) = delete;

    // Carga la imagen. Devuelve false si el archivo no existe o no se puede leer.
    bool cargar(const char* ruta, float altoVentana);
    bool estaCargado() const;

    // Cubre toda la ventana (menu). Si la imagen no es 16:9 se deforma un poco.
    void dibujarEstirado(sf::RenderWindow& ventana, float anchoVentana, float altoVentana) const;

    // Fondo de nivel: se llama con la camara activa (coordenadas del mundo).
    //   izquierdaCamara: borde izquierdo de lo que se ve, en coordenadas del mundo.
    // Si la imagen es tan ancha como el mapa se queda fija al mundo; si es mas
    // angosta se repite y se mueve a la mitad de velocidad.
    void dibujarConScroll(sf::RenderWindow& ventana, float izquierdaCamara,
                          float anchoVentana, float anchoMapa) const;
};
