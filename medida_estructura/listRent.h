#ifndef LISTRENT_H
#define LISTRENT_H

#include <iostream>
#include <vector>
#include "persona.h"

/**
 * Clase para listar y contar declarantes de renta por calendario tributario.
 *
 * Clasificación de grupos según últimos dos dígitos del ID:
 * - Grupo A: Dígitos 00-39
 * - Grupo B: Dígitos 40-79
 * - Grupo C: Dígitos 80-99
 */
void listarDeclarantesGrupoValor(std::vector<Persona> personas);

// Métodos para listar declarantes de renta por grupo por referencia
void listarDeclarantesGrupoRef(const std::vector<Persona> &personas);

// Método auxiliar para determinar el grupo según los últimos dígitos del ID
char determinarGrupo(const std::string &id);

// Método auxiliar para extraer los últimos dos dígitos del ID
int extraerUltimosDigitos(const std::string &id);

#endif
