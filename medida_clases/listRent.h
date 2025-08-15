#ifndef LISTRENT_H
#define LISTRENT_H

#include <iostream>
#include <vector>
#include <map>
#include "persona.h"

/**
 * Clase para listar y contar declarantes de renta por calendario tributario.
 *
 * Clasificación de grupos según últimos dos dígitos del ID:
 * - Grupo A: Dígitos 00-39
 * - Grupo B: Dígitos 40-79
 * - Grupo C: Dígitos 80-99
 */
class listRent
{
public:
    // Métodos para listar declarantes de renta por grupo por valor
    static std::vector<Persona> listarDeclarantesGrupoAValor(const std::vector<Persona> &personas);
    static std::vector<Persona> listarDeclarantesGrupoBValor(const std::vector<Persona> &personas);
    static std::vector<Persona> listarDeclarantesGrupoCValor(const std::vector<Persona> &personas);

    // Métodos para listar declarantes de renta por grupo por referencia
    static std::vector<const Persona *> listarDeclarantesGrupoARef(const std::vector<Persona> &personas);
    static std::vector<const Persona *> listarDeclarantesGrupoBRef(const std::vector<Persona> &personas);
    static std::vector<const Persona *> listarDeclarantesGrupoCRef(const std::vector<Persona> &personas);

    // Métodos para contar declarantes de renta por grupo
    static int contarDeclarantesGrupoA(const std::vector<Persona> &personas);
    static int contarDeclarantesGrupoB(const std::vector<Persona> &personas);
    static int contarDeclarantesGrupoC(const std::vector<Persona> &personas);

    // Método para obtener todos los declarantes agrupados por calendario (valor)
    static std::map<char, std::vector<Persona>> obtenerDeclarantesPorGrupoValor(const std::vector<Persona> &personas);

    // Método para obtener todos los declarantes agrupados por calendario (referencia)
    static std::map<char, std::vector<const Persona *>> obtenerDeclarantesPorGrupoRef(const std::vector<Persona> &personas);

private:
    // Método auxiliar para determinar el grupo según los últimos dígitos del ID
    static char determinarGrupo(const std::string &id);

    // Método auxiliar para extraer los últimos dos dígitos del ID
    static int extraerUltimosDigitos(const std::string &id);
};

#endif
