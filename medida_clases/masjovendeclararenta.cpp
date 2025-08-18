#include "masjovendeclararenta.h"

Persona Masjovendeclararenta::masjovenDeclaranteRentaValor(std::vector<Persona> personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas disponibles");
    }
    // Obtener la fecha de nacimiento de la primera persona
    size_t pos = 0;
    std::stringstream ss(personas[pos].getFechaNacimiento());
    std::string token;
    int dayM, monthM, yearM;

    std::getline(ss, token, '/');
    dayM = std::stoi(token);
    std::getline(ss, token, '/');
    monthM = std::stoi(token);
    std::getline(ss, token, '/');
    yearM = std::stoi(token);

    for (size_t i = 1; i < personas.size(); i++)
    {
        if (personas[pos].getDeclaranteRenta() == false && personas[i].getDeclaranteRenta() == true)
        {
            std::stringstream ss2(personas[i].getFechaNacimiento());
            std::string token2;
            int day, month, year;

            std::getline(ss2, token2, '/');
            day = std::stoi(token2);
            std::getline(ss2, token2, '/');
            month = std::stoi(token2);
            std::getline(ss2, token2, '/');
            year = std::stoi(token2);

            if (year > yearM || (year == yearM && month > monthM) || (year == yearM && month == monthM && day > dayM))
            {
                pos = i;
                yearM = year;
                monthM = month;
                dayM = day;
            }
        }
    }
    return personas[pos];
}

const Persona Masjovendeclararenta::masjovenDeclaranteRentaRef(const std::vector<Persona> &personas)
{
    if (personas.empty())
    {
        throw std::runtime_error("No hay personas disponibles");
    }
    // Obtener la fecha de nacimiento de la primera persona
    size_t pos = 0;
    std::stringstream ss(personas[pos].getFechaNacimiento());
    std::string token;
    int dayM, monthM, yearM;

    std::getline(ss, token, '/');
    dayM = std::stoi(token);
    std::getline(ss, token, '/');
    monthM = std::stoi(token);
    std::getline(ss, token, '/');
    yearM = std::stoi(token);

    for (size_t i = 1; i < personas.size(); i++)
    {
        if (personas[pos].getDeclaranteRenta() == false && personas[i].getDeclaranteRenta() == true)
        {
            std::stringstream ss2(personas[i].getFechaNacimiento());
            std::string token2;
            int day, month, year;

            std::getline(ss2, token2, '/');
            day = std::stoi(token2);
            std::getline(ss2, token2, '/');
            month = std::stoi(token2);
            std::getline(ss2, token2, '/');
            year = std::stoi(token2);

            if (year > yearM || (year == yearM && month > monthM) || (year == yearM && month == monthM && day > dayM))
            {
                pos = i;
                yearM = year;
                monthM = month;
                dayM = day;
            }
        }
    }
    return personas[pos];
}
