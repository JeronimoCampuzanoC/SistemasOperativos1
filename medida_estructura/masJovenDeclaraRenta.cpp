#include "masJovenDeclaraRenta.h"
#include <ctime>
#include <sstream>
#include <string>

static int ano_actual() {
    time_t tiempo = time(nullptr);
    tm* ahora = localtime(&tiempo);
    return 1900 + ahora->tm_year;
}

std::optional<Persona> masJovenDeclaraRentaValor(const std::vector<Persona> personas) {
    const Persona* mas_joven = nullptr;
    int mejor_edad = 0;

    const int Y = ano_actual();
    for (const auto& p : personas) {
        if (!p.declaranteRenta) continue;
        
        // Extraer el año directamente de la fecha
        std::stringstream ss(p.fechaNacimiento);
        std::string token;
        std::getline(ss, token, '/');  // saltar día
        std::getline(ss, token, '/');  // saltar mes
        std::getline(ss, token, '/');  // obtener año
        int ano_nac = std::stoi(token);
        
        if (ano_nac <= 0 || ano_nac > Y) continue;

        int edad = Y - ano_nac;

        if (mas_joven == nullptr || edad < mejor_edad) {
            mas_joven = &p;
            mejor_edad = edad;
        }
    }
    if (mas_joven) return *mas_joven;   // copia
    return std::nullopt;
}

const Persona* masJovenDeclaraRentaRef(const std::vector<Persona>& personas) {
    const Persona* mejor = nullptr;
    int mejorEdad = 0;

    const int Y = ano_actual();
    for (const auto& p : personas) {
        if (!p.declaranteRenta) continue;
        
        // Extraer el año directamente de la fecha
        std::stringstream ss(p.fechaNacimiento);
        std::string token;
        std::getline(ss, token, '/');  // saltar día
        std::getline(ss, token, '/');  // saltar mes
        std::getline(ss, token, '/');  // obtener año
        int ano_nac = std::stoi(token);
        
        if (ano_nac <= 0 || ano_nac > Y) continue;

        int edad = Y - ano_nac;

        if (mejor == nullptr || edad < mejorEdad) {
            mejor = &p;
            mejorEdad = edad;
        }
    }
    return mejor; // puede ser nullptr si nadie declara
}
