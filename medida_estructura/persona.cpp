#include "persona.h"

int extraerAno(const std::string& fechaNacimiento){
    size_t t = fechaNacimiento.rfind("/");
    int ano = 0;
    for (size_t i = (t == std::string::npos ? 0 : t +1); i < fechaNacimiento.size(); i++ ){
        char c = fechaNacimiento[i];
        if (c < '0' || c > '9') break;
        ano = ano * 10 + (c - '0');
    }
    return ano;
}

