# Makefile para compilación automatizada en Linux

# Configuración del compilador
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g  

# Archivos fuente y objetos
SRCS := generador.cpp main.cpp monitor.cpp personalongeva.cpp masJovenDeclaraRenta.cpp listRent.cpp maxPatrNeto.cpp maxPatr.cpp
OBJS := $(SRCS:.cpp=.o)
EXEC := programa
# Regla para maxPatr
maxPatr.o: maxPatr.cpp maxPatr.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Regla para maxPatrNeto
maxPatrNeto.o: maxPatrNeto.cpp maxPatrNeto.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
# Regla para listRent
listRent.o: listRent.cpp listRent.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Objetivo principal: compilar el ejecutable
all: $(EXEC)

# Enlaza todos los objetos en el ejecutable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas específicas para cada objeto con sus dependencias
generador.o: generador.cpp generador.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

monitor.o: monitor.cpp monitor.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

personalongeva.o: personalongeva.cpp personalongeva.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 👇 Incluimos el header nuevo en las dependencias del main
main.o: main.cpp persona.h generador.h monitor.h personalongeva.h masJovenDeclaraRenta.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@



# 👇 Nueva regla para el medidor de “más joven declarante”
masJovenDeclaraRenta.o: masJovenDeclaraRenta.cpp masJovenDeclaraRenta.h persona.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpia archivos generados
clean:
	rm -f $(OBJS) $(EXEC)

# Recompila todo desde cero
rebuild: clean all

# Ejecuta el programa después de compilar
run: $(EXEC)
	./$(EXEC)

# Declara objetivos que no son archivos
.PHONY: all clean rebuild run
