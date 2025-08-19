#include "maxPatr.h"
#include <stdexcept>

// Extrae los últimos dos dígitos de un ID
int extraerUltimosDigitos1(const std::string &id)
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

// Determina el grupo de declaración de una persona
char determinarGrupo1(const std::string &id)
{
    int ultimosDigitos = extraerUltimosDigitos1(id);

    if (ultimosDigitos == -1)
        return 'X'; // Error en el formato de alguna manera

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

    return 'X'; // No clasificado :P
}

// Determina la persona registrada con mayor patrimonio de todo el pais, por Referencia
Persona personaMayorPatrimonioPaisRef(const std::vector<Persona> &personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    const Persona *mayor = &personas[0];
    for (const auto &persona : personas)
    {
        if (persona.patrimonio > mayor->patrimonio)
        {
            mayor = &persona;
        }
    }
    return *mayor;
}

// Determina la persona registrada con mayor patrimonio de todo el pais, por Valor
Persona personaMayorPatrimonioPaisValor(std::vector<Persona> personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    Persona mayor = personas[0];
    for (const auto &persona : personas)
    {
        if (persona.patrimonio > mayor.patrimonio)
        {
            mayor = persona;
        }
    }
    return mayor;
}

// Determina la persona de cada ciudad que esta registrada con el mayor patrimonio, por Referencia
std::map<std::string, const Persona *> personaMayorPatrimonioCiudadRef(const std::vector<Persona> &personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    std::map<std::string, const Persona *> mayoresPorCiudad;

    for (const auto &persona : personas)
    {
        const std::string &ciudad = persona.ciudadNacimiento;

        // Buscar si ya existe esta ciudad en el mapa
        auto it = mayoresPorCiudad.find(ciudad);

        if (it == mayoresPorCiudad.end())
        {
            mayoresPorCiudad.insert(std::make_pair(ciudad, &persona));
        }
        else if (persona.patrimonio > it->second->patrimonio)
        {
            it->second = &persona; // Actualizar con la persona de mayor patrimonio
        }
    }

    return mayoresPorCiudad;
}

// Determina la persona de cada ciudad que esta registrada con el mayor patrimonio, por Valor
std::map<std::string, Persona> personaMayorPatrimonioCiudadVal(std::vector<Persona> personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    std::map<std::string, Persona> mayoresPorCiudad;

    for (const auto &persona : personas)
    {
        const std::string &ciudad = persona.ciudadNacimiento;

        // Buscar si ya existe esta ciudad en el mapa
        auto it = mayoresPorCiudad.find(ciudad);

        if (it == mayoresPorCiudad.end())
        {
            mayoresPorCiudad.insert(std::make_pair(ciudad, persona));
        }
        else if (persona.patrimonio > it->second.patrimonio)
        {
            it->second = persona; // Actualizar con la persona de mayor patrimonio
        }
    }

    return mayoresPorCiudad;
}

// Determina la persona de cada grupo de Declaración de Renta que este registrada con mayor patrimonio, por Referencia
Persona personaMayorPatrimonioGrupoRef(const std::vector<Persona> &personas, char grupoDeclaracion)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    const Persona *mayor = nullptr;
    for (const auto &persona : personas)
    {
        if (determinarGrupo1(persona.id) == grupoDeclaracion)
        {
            if (!mayor || persona.patrimonio > mayor->patrimonio)
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

// Determina la persona de cada grupo de Declaración de Renta que este registrada con mayor patrimonio, por Valor
Persona personaMayorPatrimonioGrupoValor(std::vector<Persona> personas, char grupoDeclaracion)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas en la lista");
    }

    Persona mayor = personas[0];
    bool encontrado = false;
    for (const auto &persona : personas)
    {
        if (determinarGrupo1(persona.id) == grupoDeclaracion)
        {
            if (!encontrado || persona.patrimonio > mayor.patrimonio)
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

// Determina la persona mas importante para la DIAN, la que tiene mayor patrimonio con menos ingresos, por Referencia
Persona maxPatrimonioIngresosRef(const std::vector<Persona> &personas)
{
    Persona maximo = personas[0];

    for (size_t i = 1; i < personas.size(); ++i)
    {
        if (personas[i].patrimonio > maximo.patrimonio)
        {
            if (personas[i].ingresosAnuales < maximo.ingresosAnuales)
            {
                maximo = personas[i];
            }
        }
    }

    return maximo;
}

// Determina la persona mas importante para la DIAN, la que tiene mayor patrimonio con menos ingresos, por Valor
Persona maxPatrimonioIngresosVal(std::vector<Persona> personas)
{
    Persona maximo = personas[0];

    for (size_t i = 1; i < personas.size(); ++i)
    {
        if (personas[i].patrimonio > maximo.patrimonio)
        {
            if (personas[i].ingresosAnuales < maximo.ingresosAnuales)
            {
                maximo = personas[i];
            }
        }
    }

    return maximo;
}