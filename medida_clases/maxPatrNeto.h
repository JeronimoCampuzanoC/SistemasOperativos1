#ifndef MAXPATRNETO_H
#define MAXPATRNETO_H

#include <iostream>
#include <vector>
#include "persona.h"

class maxPatrNeto
{
public:
    // Returns the maximum net worth by value
    static Persona maxPatrNetoValor(std::vector<Persona> personas);

    // Returns the maximum net worth by reference
    static Persona maxPatrNetoRef(const std::vector<Persona> &personas);
};

#endif // MAXPATRNETO_H