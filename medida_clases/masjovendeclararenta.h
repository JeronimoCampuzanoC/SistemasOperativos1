#pragma once
#include <vector>
#include <optional>
#include "persona.h"

class Masjovendeclararenta
{
public:
    // Método para encontrar la persona más joven declarante de renta por valor
    static Persona masjovenDeclaranteRentaValor(std::vector<Persona> personas);

    // Método para encontrar la persona más joven declarante de renta por referencia
    static const Persona masjovenDeclaranteRentaRef(const std::vector<Persona> &personas);
};