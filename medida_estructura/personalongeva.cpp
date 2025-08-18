#include "personalongeva.h"
#include <stdexcept>
#include <sstream>
#include <string>

Persona PersonaMasLongevaValor(const std::vector<Persona> personas){
    if (personas.empty()) throw std::runtime_error("No se han encontrado personas");
    size_t pos = 0;
    
    // Extraer el año de la primera persona
    std::stringstream ss(personas[0].fechaNacimiento);
    std::string token;
    std::getline(ss, token, '/');  // saltar día
    std::getline(ss, token, '/');  // saltar mes
    std::getline(ss, token, '/');  // obtener año
    int ano_na = std::stoi(token);
    
    for (size_t i = 0; i < personas.size(); i++){
        // Extraer el año de cada persona
        std::stringstream ss2(personas[i].fechaNacimiento);
        std::getline(ss2, token, '/');  // saltar día
        std::getline(ss2, token, '/');  // saltar mes
        std::getline(ss2, token, '/');  // obtener año
        int y = std::stoi(token);
        
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
    
    
    std::stringstream ss(personas[0].fechaNacimiento);
    std::string token;
    std::getline(ss, token, '/');  
    std::getline(ss, token, '/');  
    std::getline(ss, token, '/');  
    int ano_na = std::stoi(token);
    
    for (size_t i = 0; i < personas.size(); i++){
        
        std::stringstream ss2(personas[i].fechaNacimiento);
        std::getline(ss2, token, '/');  
        std::getline(ss2, token, '/');  
        std::getline(ss2, token, '/');  
        int y = std::stoi(token);
        
        if (y != 0 && (ano_na == 0 || y <ano_na)){ ano_na = y; pos = i;}
    }
    return personas[pos];
}


std::map<std::string, Persona> PersonaMasLongevaCiudadValor(const std::vector<Persona> personas){
    std::map<std::string, Persona> resultado;
    for (const auto& p : personas){
        const std::string& c = p.ciudadNacimiento;
        auto it = resultado.find(c);
        if (it == resultado.end()){
            resultado.emplace(c, p);
        }
        else{
            
            std::stringstream ss(p.fechaNacimiento);
            std::string token;
            std::getline(ss, token, '/');
            std::getline(ss, token, '/');
            std::getline(ss, token, '/');
            int y_new = std::stoi(token);
            
            
            std::stringstream ss2(it->second.fechaNacimiento);
            std::getline(ss2, token, '/');
            std::getline(ss2, token, '/');
            std::getline(ss2, token, '/');
            int y_old = std::stoi(token);
            
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
          
            std::stringstream ss(p.fechaNacimiento);
            std::string token;
            std::getline(ss, token, '/');
            std::getline(ss, token, '/');
            std::getline(ss, token, '/');
            int y_new = std::stoi(token);
            
            
            std::stringstream ss2(it->second->fechaNacimiento);
            std::getline(ss2, token, '/');
            std::getline(ss2, token, '/');
            std::getline(ss2, token, '/');
            int y_old = std::stoi(token);
            
            if (y_old == 0 || (y_new != 0 && y_new < y_old)) {
                it->second = &p;                
            }
        }
    }
    return resultado;
}




