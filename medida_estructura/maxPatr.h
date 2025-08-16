#pragma once
#include <vector>
#include <map>
#include <string>
#include "persona.h"

Persona personaMayorPatrimonioPaisRef(const std::vector<Persona> &personas);
Persona personaMayorPatrimonioPaisValor(const std::vector<Persona> &personas);

std::map<std::string, const Persona *> personaMayorPatrimonioCiudadRef(const std::vector<Persona> &personas);
std::map<std::string, Persona> personaMayorPatrimonioCiudadVal(const std::vector<Persona> &personas);

Persona personaMayorPatrimonioGrupoRef(const std::vector<Persona> &personas, char grupoDeclaracion);
Persona personaMayorPatrimonioGrupoValor(const std::vector<Persona> &personas, char grupoDeclaracion);

Persona maxPatrimonioIngresosRef(const std::vector<Persona> &personas);
Persona maxPatrimonioIngresosVal(const std::vector<Persona> &personas);

int extraerUltimosDigitos(const std::string &id);
char determinarGrupo(const std::string &id);