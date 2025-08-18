#include "personalongeva.h"
#include <stdexcept>
#include <map>

Persona Personalongeva::getPersonaMasLongevaValor(std::vector<Persona> personas)
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
        std::stringstream ss2(personas[i].getFechaNacimiento());
        std::string token2;
        int day, month, year;

        std::getline(ss2, token2, '/');
        day = std::stoi(token2);
        std::getline(ss2, token2, '/');
        month = std::stoi(token2);
        std::getline(ss2, token2, '/');
        year = std::stoi(token2);

        if (year < yearM || (year == yearM && month < monthM) || (year == yearM && month == monthM && day < dayM))
        {
            pos = i;
            yearM = year;
            monthM = month;
            dayM = day;
        }
    }
    return personas[pos];
}

const Persona &Personalongeva::getPersonaMasLongevaRef(const std::vector<Persona> &personas)
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
        std::stringstream ss2(personas[i].getFechaNacimiento());
        std::string token2;
        int day, month, year;

        std::getline(ss2, token2, '/');
        day = std::stoi(token2);
        std::getline(ss2, token2, '/');
        month = std::stoi(token2);
        std::getline(ss2, token2, '/');
        year = std::stoi(token2);

        if (year < yearM || (year == yearM && month < monthM) || (year == yearM && month == monthM && day < dayM))
        {
            pos = i;
            yearM = year;
            monthM = month;
            dayM = day;
        }
    }
    return personas[pos];
}

std::map<std::string, Persona> Personalongeva::getPersonaMasLongevaCiudadValor(std::vector<Persona> personas)
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

           stringstream ss1(p.getFechaNacimiento());
            string token1;
            int day1, month1, year1;

            getline(ss1, token1, '/');
            day1 = stoi(token1);
            getline(ss1, token1, '/');
            month1 = stoi(token1);
            getline(ss1, token1, '/');
            year1 = stoi(token1);

            stringstream ss2(it->second.getFechaNacimiento());
            string token2;
            int day2, month2, year2;

            getline(ss2, token2, '/');
            day2 = stoi(token2);
            getline(ss2, token2, '/');
            month2 = stoi(token2);
            getline(ss2, token2, '/');
            year2 = stoi(token2);

            if (year1 < year2 || (year1 == year2 && month1 < month2) || (year1 == year2 && month1 == month2 && day1 < day2))
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
            stringstream ss1(p.getFechaNacimiento());
            string token1;
            int day1, month1, year1;

            getline(ss1, token1, '/');
            day1 = stoi(token1);
            getline(ss1, token1, '/');
            month1 = stoi(token1);
            getline(ss1, token1, '/');
            year1 = stoi(token1);

            stringstream ss2(it->second->getFechaNacimiento());
            string token2;
            int day2, month2, year2;

            getline(ss2, token2, '/');
            day2 = stoi(token2);
            getline(ss2, token2, '/');
            month2 = stoi(token2);
            getline(ss2, token2, '/');
            year2 = stoi(token2);

            if (year1 < year2 || (year1 == year2 && month1 < month2) || (year1 == year2 && month1 == month2 && day1 < day2))
            {
                it->second = &p;
            }
        }
    }
    return res;
}


