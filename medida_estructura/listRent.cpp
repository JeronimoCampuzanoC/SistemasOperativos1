#include "listRent.h"

using namespace std;

// Método auxiliar para extraer los últimos dos dígitos del ID
int extraerUltimosDigitos(const std::string &id)
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
char determinarGrupo(const std::string &id)
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
void listarDeclarantesGrupoValor(std::vector<Persona> personas)
{
    // Contadores para cada grupo
    std::vector<Persona> personasA;
    std::vector<Persona> personasB;
    std::vector<Persona> personasC;

    // Contar declarantes por grupo
    for (const auto &persona : personas)
    {
        char grupo = determinarGrupo(persona.id);
        switch (grupo)
        {
        case 'A':
            personasA.push_back(persona);
            break;
        case 'B':
            personasB.push_back(persona);
            break;
        case 'C':
            personasC.push_back(persona);
            break;
        default:
            break;
        }
    }

    // Mostrar resultados
    std::cout << "Declarantes de Renta por Grupo (Valor):" << std::endl;
    std::cout << "Grupo A: " << personasA.size() << std::endl;
    for (size_t i = 0; i < personasA.size(); i++)
    {
        std::cout << " - " << personasA[i].nombre << " (ID: " << personasA[i].id << ")" << std::endl;
    }

    std::cout << "Grupo B: " << personasB.size() << std::endl;
    for (size_t i = 0; i < personasB.size(); i++)
    {
        std::cout << " - " << personasB[i].nombre << " (ID: " << personasB[i].id << ")" << std::endl;
    }
    std::cout << "Grupo C: " << personasC.size() << std::endl;
    for (size_t i = 0; i < personasC.size(); i++)
    {
        std::cout << " - " << personasC[i].nombre << " (ID: " << personasC[i].id << ")" << std::endl;
    }
}

// Métodos para listar declarantes de renta por grupo por referencia
void listarDeclarantesGrupoRef(const std::vector<Persona> &personas)
{
    // Contadores para cada grupo
    std::vector<Persona> personasA;
    std::vector<Persona> personasB;
    std::vector<Persona> personasC;

    // Contar declarantes por grupo
    for (const auto &persona : personas)
    {
        char grupo = determinarGrupo(persona.id);
        switch (grupo)
        {
        case 'A':
            personasA.push_back(persona);
            break;
        case 'B':
            personasB.push_back(persona);
            break;
        case 'C':
            personasC.push_back(persona);
            break;
        default:
            break;
        }
    }

    // Mostrar resultados
    std::cout << "Declarantes de Renta por Grupo (Valor):" << std::endl;
    std::cout << "Grupo A: " << personasA.size() << std::endl;
    for (size_t i = 0; i < personasA.size(); i++)
    {
        std::cout << " - " << personasA[i].nombre << " (ID: " << personasA[i].id << ")" << std::endl;
    }

    std::cout << "Grupo B: " << personasB.size() << std::endl;
    for (size_t i = 0; i < personasB.size(); i++)
    {
        std::cout << " - " << personasB[i].nombre << " (ID: " << personasB[i].id << ")" << std::endl;
    }
    std::cout << "Grupo C: " << personasC.size() << std::endl;
    for (size_t i = 0; i < personasC.size(); i++)
    {
        std::cout << " - " << personasC[i].nombre << " (ID: " << personasC[i].id << ")" << std::endl;
    }
}