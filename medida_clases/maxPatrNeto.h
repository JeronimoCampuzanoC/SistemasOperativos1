#ifndef MAXPATRNETO_H
#define MAXPATRNETO_H

#include <iostream>
#include <vector>
#include "persona.h"

class maxPatrNeto
{
public:
    // Devuelve el patrimonio max de una persona por valor
    static Persona maxPatrNetoValor(std::vector<Persona> personas);

    // Devuelve el patrimonio max de una persona por referencia
    static Persona maxPatrNetoRef(const std::vector<Persona> &personas);
};

#endif // MAXPATRNETO_H