#include "entidades/Entidad.h"

Entidad::Entidad(float x, float y, float ancho, float alto, int vida) : x(x),y(y),ancho(ancho),alto(alto),vida(vida){}

void Entidad::recibirDanio(int d){
    if(d<=0){
        return;
    }else{vida = vida -d;}
    if(vida < 0){
        vida = 0;
    }
}
bool Entidad::estaVivo() const {
    return vida > 0;
}

bool Entidad::colisionaCon(const Entidad& otra) const{
    return x < otra.x + otra.ancho && x + ancho > otra.x && y < otra.y + otra.alto && y + alto >otra.y ;
}

bool Entidad::operator==(const Entidad& otra) const{
    return x == otra.x && y == otra.y && ancho == otra.ancho && alto == otra.alto ;
}

float Entidad::getX() const { return x;}
float Entidad::getY() const { return y;}
float Entidad::getAncho() const { return ancho; }
float Entidad::getAlto() const { return alto; }
int   Entidad::getVida() const { return vida; }