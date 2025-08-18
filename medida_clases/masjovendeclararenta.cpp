#include "masjovendeclararenta.h"
/*
std::optional<Persona> Masjovendeclararenta::masjovenDeclaranteRentaValor(const std::vector<Persona>& personas) {
    const Persona* masjoven = nullptr;

    for (const auto& p : personas) {
        if (p.getDeclaranteRenta()) {
            if (masjoven == nullptr || p.getEdad() < masjoven->getEdad()) {
                masjoven = &p;
            }
        }
    }

    if (masjoven) {
        return *masjoven;  // devuelve una copia
    } else {
        return std::nullopt; // no hay ninguno
    }
}

const Persona* Masjovendeclararenta::masjovenDeclaranteRentaRef(const std::vector<Persona>& personas) {
    const Persona* masjoven = nullptr;

    for (const auto& p : personas) {
        if (p.getDeclaranteRenta()) {
            if (masjoven == nullptr || p.getEdad() < masjoven->getEdad()) {
                masjoven = &p;
            }
        }
    }

    return masjoven;  // puede ser nullptr si no hay ninguno
}
*/