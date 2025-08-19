#include "maxPatrNeto.h"
#include <stdexcept>

// Retorna la persona con mayor patrimonio neto (valor)
Persona maxPatrNetoValor(std::vector<Persona> personas)
{
    if (personas.empty())
        throw std::runtime_error("No hay personas disponibles");
    Persona mayor = personas.front();
    double maxNeto = mayor.patrimonio - mayor.deudas;
    for (size_t i = 1; i < personas.size(); ++i)
    {
        double neto = personas[i].patrimonio - personas[i].deudas;
        if (neto > maxNeto)
        {
            mayor = personas[i];
            maxNeto = neto;
        }
    }
    return mayor;
}

// Retorna la persona con mayor patrimonio neto (referencia)
Persona maxPatrNetoRef(const std::vector<Persona> &personas)
{
    if (personas.empty())
        throw std::runtime_error("No hay personas disponibles");
    const Persona *mayor = &personas[0];
    double maxNeto = mayor->patrimonio - mayor->deudas;
    for (size_t i = 1; i < personas.size(); ++i)
    {
        double neto = personas[i].patrimonio - personas[i].deudas;
        if (neto > maxNeto)
        {
            mayor = &personas[i];
            maxNeto = neto;
        }
    }
    return *mayor;
}
