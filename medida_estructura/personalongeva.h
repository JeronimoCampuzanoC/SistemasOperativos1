#pragma once
#include <vector>
#include <map>
#include <string>
#include "persona.h"


Persona PersonaMasLongevaValor(const std::vector<Persona> personas);
const Persona& PersonaMasLongevaRef(const std::vector<Persona>& personas);

std::map<std::string, Persona> PersonaMasLongevaCiudadValor(const std::vector<Persona> personas);
std::map<std::string, const Persona*> PersonaMasLongevaPorCiudadRef(const std::vector<Persona>& personas);