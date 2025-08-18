#include "personalongeva.h"
#include <stdexcept>
#include <map>

Persona Personalongeva::getPersonaMasLongevaValor(std::vector<Persona> personas)
{
    if (personas.empty())
        throw std::runtime_error("No hay personas disponibles");
    Persona mayor = personas.front(); // hago una copia de la primera persona con la que pibotearemos para ver quien es mayor
    for (size_t i = 1; i < personas.size(); i++)
    {
        if (personas[i].getEdad() > mayor.getEdad())
        {
            mayor = personas[i];
        }
    }
    return mayor;
}

const Persona &Personalongeva::getPersonaMasLongevaRef(const std::vector<Persona> &personas)
{
    if (personas.empty())
        throw std::runtime_error("No hay personas disponibles");
    size_t pos = 0;
    for (size_t i = 1; i < personas.size(); i++)
    {
        if (personas[i].getEdad() > personas[pos].getEdad())
        {
            pos = i;
        }
    }
    return personas[pos];
}

std::map<std::string, Persona> Personalongeva::getPersonaMasLongevaCiudadValor(const std::vector<Persona> &personas)
{
    std::map<std::string, Persona> res;

    for (const auto &p : personas)
    {
        const std::string &ciudad = p.getCiudadNacimiento();
        auto it = res.find(ciudad);

        if (it == res.end())
        {
            res.emplace(ciudad, p);
        }
        else
        {

            if (p.getEdad() > it->second.getEdad())
            {
                it->second = p;
            }
        }
    }
    return res;
}

std::map<std::string, const Persona *> Personalongeva::getPersonaMasLongevaCiudadRef(const std::vector<Persona> &personas)
{
    std::map<std::string, const Persona *> res;

    for (const auto &p : personas)
    {
        const std::string &ciudad = p.getCiudadNacimiento();
        auto it = res.find(ciudad);

        if (it == res.end())
        {
            res.emplace(ciudad, &p);
        }
        else
        {
            if (p.getEdad() > it->second->getEdad())
            {
                it->second = &p;
            }
        }
    }
    return res;
}
