#include "listRent.h"

using namespace std;

// Método auxiliar para extraer los últimos dos dígitos del ID
int listRent::extraerUltimosDigitos(const std::string &id)
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
char listRent::determinarGrupo(const std::string &id)
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

// Métodos para listar declarantes de renta por grupo por valor
std::vector<Persona> listRent::listarDeclarantesGrupoAValor(const std::vector<Persona> &personas)
{
    std::vector<Persona> grupoA;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'A')
        {
            grupoA.push_back(persona); // Copia por valor
        }
    }

    return grupoA;
}

std::vector<Persona> listRent::listarDeclarantesGrupoBValor(const std::vector<Persona> &personas)
{
    std::vector<Persona> grupoB;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'B')
        {
            grupoB.push_back(persona); // Copia por valor
        }
    }

    return grupoB;
}

std::vector<Persona> listRent::listarDeclarantesGrupoCValor(const std::vector<Persona> &personas)
{
    std::vector<Persona> grupoC;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'C')
        {
            grupoC.push_back(persona); // Copia por valor
        }
    }

    return grupoC;
}

// Métodos para listar declarantes de renta por grupo por referencia
std::vector<const Persona *> listRent::listarDeclarantesGrupoARef(const std::vector<Persona> &personas)
{
    std::vector<const Persona *> grupoA;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'A')
        {
            grupoA.push_back(&persona); // Referencia/puntero
        }
    }

    return grupoA;
}

std::vector<const Persona *> listRent::listarDeclarantesGrupoBRef(const std::vector<Persona> &personas)
{
    std::vector<const Persona *> grupoB;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'B')
        {
            grupoB.push_back(&persona); // Referencia/puntero
        }
    }

    return grupoB;
}

std::vector<const Persona *> listRent::listarDeclarantesGrupoCRef(const std::vector<Persona> &personas)
{
    std::vector<const Persona *> grupoC;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'C')
        {
            grupoC.push_back(&persona); // Referencia/puntero
        }
    }

    return grupoC;
}

// Métodos para contar declarantes de renta por grupo
int listRent::contarDeclarantesGrupoA(const std::vector<Persona> &personas)
{
    int contador = 0;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'A')
        {
            contador++;
        }
    }

    return contador;
}

int listRent::contarDeclarantesGrupoB(const std::vector<Persona> &personas)
{
    int contador = 0;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'B')
        {
            contador++;
        }
    }

    return contador;
}

int listRent::contarDeclarantesGrupoC(const std::vector<Persona> &personas)
{
    int contador = 0;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta() && determinarGrupo(persona.getId()) == 'C')
        {
            contador++;
        }
    }

    return contador;
}

// Método para obtener todos los declarantes agrupados por calendario (valor)
std::map<char, std::vector<Persona>> listRent::obtenerDeclarantesPorGrupoValor(const std::vector<Persona> &personas)
{
    std::map<char, std::vector<Persona>> grupos;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta())
        {
            char grupo = determinarGrupo(persona.getId());
            if (grupo != 'X')
            {                                     // Solo si el grupo es válido
                grupos[grupo].push_back(persona); // Copia por valor
            }
        }
    }

    return grupos;
}

// Método para obtener todos los declarantes agrupados por calendario (referencia)
std::map<char, std::vector<const Persona *>> listRent::obtenerDeclarantesPorGrupoRef(const std::vector<Persona> &personas)
{
    std::map<char, std::vector<const Persona *>> grupos;

    for (const auto &persona : personas)
    {
        if (persona.getDeclaranteRenta())
        {
            char grupo = determinarGrupo(persona.getId());
            if (grupo != 'X')
            {                                      // Solo si el grupo es válido
                grupos[grupo].push_back(&persona); // Referencia/puntero
            }
        }
    }

    return grupos;
}
