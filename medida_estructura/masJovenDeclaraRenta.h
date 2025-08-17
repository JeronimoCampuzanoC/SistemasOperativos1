#pragma once
#include <vector>
#include <optional>
#include "persona.h"


std::optional<Persona> masJovenDeclaraRentaValor(const std::vector<Persona>& personas);
const Persona* masJovenDeclaraRentaRef(const std::vector<Persona>& personas);
