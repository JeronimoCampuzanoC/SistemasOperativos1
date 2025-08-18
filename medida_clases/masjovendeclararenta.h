#pragma once
#include <vector>
#include <optional>
#include "persona.h"

class Masjovendeclararenta
{
public:
    static Persona masjovenDeclaranteRentaValor(std::vector<Persona> personas);

    static const Persona masjovenDeclaranteRentaRef(const std::vector<Persona> &personas);
};