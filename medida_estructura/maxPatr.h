#pragma once
#include <vector>
#include <map>
#include <string>
#include "persona.h"

int extraerUltimosDigitos1(const std::string &id);
char determinarGrupo1(const std::string &id);

Persona personaMayorPatrimonioPaisRef(const std::vector<Persona> &personas);
Persona personaMayorPatrimonioPaisValor(std::vector<Persona> personas);

std::map<std::string, const Persona *> personaMayorPatrimonioCiudadRef(const std::vector<Persona> &personas);
std::map<std::string, Persona> personaMayorPatrimonioCiudadVal(std::vector<Persona> personas);

Persona personaMayorPatrimonioGrupoRef(const std::vector<Persona> &personas, char grupoDeclaracion);
Persona personaMayorPatrimonioGrupoValor(std::vector<Persona> personas, char grupoDeclaracion);

Persona maxPatrimonioIngresosRef(const std::vector<Persona> &personas);
Persona maxPatrimonioIngresosVal(std::vector<Persona> personas);
