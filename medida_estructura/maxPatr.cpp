#include "maxPatr.h"
#include <stdexcept>

struct Persona personaMayorPatrimonioPaisRef(const std::vector<Persona> &personas)
{
    if (personas.empty()) throw std::runtime_error("No se han encontrado personas");
    
    const Persona *maxPais = nullptr;

    for (int i = 0; i < personas.size(); i++){
        if (maxPais->patrimonio < personas[i].patrimonio) {
            maxPais = &personas[i];
        }
    }

    return *maxPais;
}

struct Persona personaMayorPatrimonioPaisValor(const std::vector<Persona> &personas)
{
    if (personas.empty()) throw std::runtime_error("No se han encontrado personas");

    Persona maxPais;

    for (int i = 0; i < personas.size(); i++){
        if (maxPais.patrimonio < personas[i].patrimonio) {
            maxPais = personas[i];
        }
    }

    return maxPais;
}

std::map<std::string, const Persona*> personaMayorPatrimonioCiudadRef(const std::vector<Persona> &personas)
{
    std::map<std::string, const Persona*> resultado;
    for (const auto& persona : personas) {
        std::string ciudad = persona.ciudadNacimiento;
        auto it = resultado.find(ciudad);
        if (it == resultado.end() || persona.patrimonio > it->second->patrimonio) {
            resultado[ciudad] = &persona;
        }
    }
    return resultado;
}


std::map<std::string, Persona> personaMayorPatrimonioCiudadVal(const std::vector<Persona> &personas)
{
    std::map<std::string, Persona> resultado;
    for (const auto& persona : personas) {
        auto ciudad = persona.ciudadNacimiento;
        auto it = resultado.find(ciudad);
        if (it == resultado.end() || persona.patrimonio > it->second.patrimonio) {
            resultado[ciudad] = persona;
        }
    }
    return resultado;
}

struct Persona personaMayorPatrimonioGrupoRef(const std::vector<Persona> &personas, char grupo)
{
    const Persona* maxGrupo = nullptr;
    for (const auto& persona : personas) {
        auto digitos = extraerUltimosDigitos(persona.id);
        auto personaGrupo = determinarGrupo(std::to_string(digitos));
        if (personaGrupo == grupo) {
            if (!maxGrupo || persona.patrimonio > maxGrupo->patrimonio) {
                maxGrupo = &persona;
            }
        }
    }
    if (!maxGrupo) throw std::runtime_error("No se encontró persona en el grupo de declaración especificado");
    return *maxGrupo;
}

struct Persona personaMayorPatrimonioGrupoValor(const std::vector<Persona> &personas, char grupo)
{
    bool encontrado = false;
    Persona maxGrupo;
    for (const auto& persona : personas) {
        auto digitos = extraerUltimosDigitos(persona.id);
        auto personaGrupo = determinarGrupo(std::to_string(digitos));
        if (personaGrupo == grupo) {
            if (!encontrado || persona.patrimonio > maxGrupo.patrimonio) {
                maxGrupo = persona;
                encontrado = true;
            }
        }
    }
    if (!encontrado) throw std::runtime_error("No se encontró persona en el grupo de declaración especificado");
    return maxGrupo;
}

struct Persona maxPatrimonioIngresosRef(const std::vector<Persona> &personas)
{
    if (personas.empty()) throw std::runtime_error("No se han encontrado personas");

    const Persona* maxPtr = &personas[0];
    for (size_t i = 1; i < personas.size(); ++i) {
        // Cambia la lógica según el criterio que desees (ejemplo: máximo patrimonio, mínimo ingresos)
        if (personas[i].patrimonio > maxPtr->patrimonio ||
            (personas[i].patrimonio == maxPtr->patrimonio && personas[i].ingresosAnuales < maxPtr->ingresosAnuales)) {
            maxPtr = &personas[i];
        }
    }
    return *maxPtr;
}

struct Persona maxPatrimonioIngresosVal(const std::vector<Persona> &personas)
{
    if (personas.empty()) throw std::runtime_error("No se han encontrado personas");

    Persona maxPers = personas[0];
    for (size_t i = 1; i < personas.size(); ++i) {
        if (personas[i].patrimonio > maxPers.patrimonio ||
            (personas[i].patrimonio == maxPers.patrimonio && personas[i].ingresosAnuales < maxPers.ingresosAnuales)) {
            maxPers = personas[i];
        }
    }
    return maxPers;
}

int extraerUltimosDigitos(const std::string &id)
{
    if (id.length() < 2)
        return -1;

    std::string ultimosDos = id.substr(id.length() - 2);
    try
    {
        return std::stoi(ultimosDos);
    }
    catch (const std::exception &)
    {
        return -1;
    }
}

// Método auxiliar para determinar el grupo según los últimos dígitos del ID
char determinarGrupo(const std::string &id)
{
    int ultimosDigitos = extraerUltimosDigitos(id);

    if (ultimosDigitos == -1)
        return 'X'; // Error en formato

    // Grupo A: 00-39
    if (ultimosDigitos >= 0 && ultimosDigitos <= 39)
    {
        return 'A';
    }
    // Grupo B: 40-79
    else if (ultimosDigitos >= 40 && ultimosDigitos <= 79)
    {
        return 'B';
    }
    // Grupo C: 80-99
    else if (ultimosDigitos >= 80 && ultimosDigitos <= 99)
    {
        return 'C';
    }

    return 'X'; // No clasificado
}