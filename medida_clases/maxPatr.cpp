#include "maxPatr.h"

using namespace std;

// Método auxiliar para extraer los últimos dos dígitos del ID
int maxPatr::extraerUltimosDigitos(const std::string &id)
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
char maxPatr::determinarGrupo(const std::string &id)
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

// Método que retorna la persona con mayor patrimonio en el país por referencia
Persona maxPatr::personaMayorPatrimonioPaisRef(const std::vector<Persona> &personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    const Persona *mayor = &personas[0];
    for (const auto &persona : personas)
    {
        if (persona.getPatrimonio() > mayor->getPatrimonio())
        {
            mayor = &persona;
        }
    }
    return *mayor;
}

// Método que retorna la persona con mayor patrimonio en el país por valor
Persona maxPatr::personaMayorPatrimonioPaisValor(const std::vector<Persona> &personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    Persona mayor = personas[0];
    for (const auto &persona : personas)
    {
        if (persona.getPatrimonio() > mayor.getPatrimonio())
        {
            mayor = persona;
        }
    }
    return mayor;
}

// Método que retorna la persona con mayor patrimonio en una ciudad específica por referencia
Persona maxPatr::personaMayorPatrimonioCiudadRef(const std::vector<Persona> &personas, const std::string &ciudad)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    const Persona *mayor = nullptr;
    for (const auto &persona : personas)
    {
        if (persona.getCiudadNacimiento() == ciudad)
        {
            if (!mayor || persona.getPatrimonio() > mayor->getPatrimonio())
            {
                mayor = &persona;
            }
        }
    }
    if (!mayor)
    {
        throw std::runtime_error("No se encontró persona en la ciudad especificada");
    }
    return *mayor;
}

// Método que retorna la persona con mayor patrimonio en una ciudad específica por valor
Persona maxPatr::personaMayorPatrimonioCiudadVal(const std::vector<Persona> &personas, const std::string &ciudad)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    bool encontrado = false;
    Persona mayor("", "", "", "", "", 0.0, 0.0, 0.0, false); // Constructor completo
    for (const auto &persona : personas)
    {
        if (persona.getCiudadNacimiento() == ciudad)
        {
            if (!encontrado)
            {
                mayor = persona;
                encontrado = true;
            }
            else if (persona.getPatrimonio() > mayor.getPatrimonio())
            {
                mayor = persona;
            }
        }
    }
    if (!encontrado)
    {
        throw std::runtime_error("No se encontró persona en la ciudad especificada");
    }
    return mayor;
}

// Método que retorna la persona con mayor patrimonio en un grupo de declaración por referencia
Persona maxPatr::personaMayorPatrimonioGrupoRef(const std::vector<Persona> &personas, char grupoDeclaracion)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    const Persona *mayor = nullptr;
    for (const auto &persona : personas)
    {
        if (determinarGrupo(persona.getId()) == grupoDeclaracion)
        {
            if (!mayor || persona.getPatrimonio() > mayor->getPatrimonio())
            {
                mayor = &persona;
            }
        }
    }
    if (!mayor)
    {
        throw std::runtime_error("No se encontró persona en el grupo de declaración especificado");
    }
    return *mayor;
}

// Método que retorna la persona con mayor patrimonio en un grupo de declaración por valor
Persona maxPatr::personaMayorPatrimonioGrupoValor(const std::vector<Persona> &personas, char grupoDeclaracion)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    Persona mayor("", "", "", "", "", 0.0, 0.0, 0.0, false); // Constructor completo
    bool encontrado = false;
    for (const auto &persona : personas)
    {
        if (determinarGrupo(persona.getId()) == grupoDeclaracion)
        {
            if (!encontrado || persona.getPatrimonio() > mayor.getPatrimonio())
            {
                mayor = persona;
                encontrado = true;
            }
        }
    }
    if (!encontrado)
    {
        throw std::runtime_error("No se encontró persona en el grupo de declaración especificado");
    }
    return mayor;
}
