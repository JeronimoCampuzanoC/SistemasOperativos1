#ifndef MAXPATRNETO_H
#define MAXPATRNETO_H

#include <iostream>
#include <vector>
#include "persona.h"

// Returns the maximum net worth by value
Persona maxPatrNetoValor(std::vector<Persona> personas);

// Returns the maximum net worth by reference
Persona maxPatrNetoRef(const std::vector<Persona> &personas);

#endif // MAXPATRNETO_H