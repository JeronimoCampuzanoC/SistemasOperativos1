#pragma once
#include <vector>
#include <optional>
#include "persona.h"

class Masjovendeclararenta {
    public:
        static std::optional<Persona> masjovenDeclaranteRentaValor(const std::vector<Persona>& personas);
        
        static const Persona* masjovenDeclaranteRentaRef(const std::vector<Persona>& personas);


};