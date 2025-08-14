#include "personalongeva.h"
#include <stdexcept>

Persona PersonaMasLongevaValor(const std::vector<Persona>& personas){
    if (personas.empty()) throw std::runtime_error("No se han encontrado personas");
    size_t pos = 0;
    int ano_na = extraerAno(personas[0].fechaNacimiento);
    for (size_t i = 0; i < personas.size(); i++){
        int y = extraerAno(personas[i].fechaNacimiento);
        if (y != 0 && (ano_na == 0 || y < ano_na)){ 
            ano_na = y; 
            pos = i;
        }
    }
    return personas[pos];
}



const Persona& PersonaMasLongevaRef(const std::vector<Persona>& personas){
    if (personas.empty()) throw std::runtime_error("No se han encontrado personas");
    size_t pos = 0;
    int ano_na = extraerAno(personas[0].fechaNacimiento);
    for (size_t i = 0; i < personas.size(); i++){
        int y = extraerAno(personas[i].fechaNacimiento);
        if (y != 0 && (ano_na == 0 || y <ano_na)){ ano_na = y; pos = i;}
    }
    return personas[pos];
}


std::map<std::string, Persona> PersonaMasLongevaCiudadValor(const std::vector<Persona>& personas){
    std::map<std::string, Persona> resultado;
    for (const auto& p : personas){
        const std::string& c = p.ciudadNacimiento;
        auto it = resultado.find(c);
        if (it == resultado.end()){
            resultado.emplace(c, p);
        }
        else{
            int y_new = extraerAno(p.fechaNacimiento);
            int y_old = extraerAno(it->second.fechaNacimiento);
            if (y_old == 0 || (y_new != 0 && y_new < y_old)){
                it->second = p;
            }
        }
    }
    return resultado;
}


std::map<std::string, const Persona*>PersonaMasLongevaPorCiudadRef(const std::vector<Persona>& personas) {
    std::map<std::string, const Persona*> resultado;
    for (const auto& p : personas) {
        const std::string& c = p.ciudadNacimiento;
        auto it = resultado.find(c);
        if (it == resultado.end()) {
            resultado.emplace(c, &p);                 
        } else {
            int y_new = extraerAno(p.fechaNacimiento);
            int y_old = extraerAno(it->second->fechaNacimiento);
            if (y_old == 0 || (y_new != 0 && y_new < y_old)) {
                it->second = &p;                
            }
        }
    }
    return resultado;
}




