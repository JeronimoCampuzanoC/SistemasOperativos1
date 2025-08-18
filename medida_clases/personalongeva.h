#pragma once
#include <vector>
#include <map>
#include <string>
#include "persona.h"
using namespace std;

class Personalongeva
{
public:
    static Persona getPersonaMasLongevaValor(std::vector<Persona> personas);
    static const Persona &getPersonaMasLongevaRef(const std::vector<Persona> &personas);

    static std::map<std::string, Persona> getPersonaMasLongevaCiudadValor(const std::vector<Persona> &personas);
    static std::map<std::string, const Persona *> getPersonaMasLongevaCiudadRef(const std::vector<Persona> &personas);
};