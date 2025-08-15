#ifndef MAXPATRPAIS_H
#define MAXPATRPAIS_H

#include <iostream>
#include <vector>
#include "persona.h"
using namespace std;

class maxPatr
{
public:
    static Persona personaMayorPatrimonioPaisRef(const std::vector<Persona> &personas);
    static Persona personaMayorPatrimonioPaisValor(const std::vector<Persona> &personas);

    static Persona personaMayorPatrimonioCiudadRef(const std::vector<Persona> &personas, const std::string &ciudad);
    static Persona personaMayorPatrimonioCiudadVal(const std::vector<Persona> &personas, const std::string &ciudad);

    static Persona personaMayorPatrimonioGrupoRef(const std::vector<Persona> &personas, char grupoDeclaracion);
    static Persona personaMayorPatrimonioGrupoValor(const std::vector<Persona> &personas, char grupoDeclaracion);

private:
    // Método auxiliar para determinar el grupo según los últimos dígitos del ID
    static char determinarGrupo(const std::string &id);

    // Método auxiliar para extraer los últimos dos dígitos del ID
    static int extraerUltimosDigitos(const std::string &id);
};

#endif