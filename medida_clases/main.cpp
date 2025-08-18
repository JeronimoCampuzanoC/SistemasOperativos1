#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <iomanip>
#include "persona.h"
#include "generador.h"
#include "monitor.h"
#include "personalongeva.h"
#include "maxPatr.h"
#include "listRent.h"
#include "maxPatrNeto.h"
#include "masjovendeclararenta.h"
using namespace std;

/**
 * Muestra el menú principal de la aplicación.
 *
 * POR QUÉ: Guiar al usuario a través de las funcionalidades disponibles.
 * CÓMO: Imprimiendo las opciones en consola.
 * PARA QUÉ: Interacción amigable con el usuario.
 */
void mostrarMenu()
{
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por ID";
    std::cout << "\n4. Mostrar estadísticas de rendimiento";
    std::cout << "\n5. Exportar estadísticas a CSV";

    std::cout << "\n6. Persona más longeva por valor y por referencia";
    std::cout << "\n7. Persona más longeva por ciudad por valor y por referencia";

    std::cout << "\n8. Persona con mayor patrimonio del pais por valor y por referencia";
    std::cout << "\n9. Persona con mayor patrimonio por ciudad por valor y por referencia";
    std::cout << "\n10. Persona con mayor patrimonio por grupo de declaración por valor y por referencia";

    std::cout << "\n11. Listar y contar declarantes de renta por calendario tributario";

    std::cout << "\n12. Persona con mayor patrimonio neto del pais, patrimonio - deudas";

    std::cout << "\n13. Persona más joven declarante de renta por valor y por referencia";

    std::cout << "\n14. Persona con mayor patrimonio y menor ingreso";
    std::cout << "\n15. Salir";
    std::cout << "\nSeleccione una opción: ";
}

/**
 * Punto de entrada principal del programa.
 *
 * POR QUÉ: Iniciar la aplicación y manejar el flujo principal.
 * CÓMO: Mediante un bucle que muestra el menú y procesa la opción seleccionada.
 * PARA QUÉ: Ejecutar las funcionalidades del sistema.
 */
int main()
{
    srand(time(nullptr)); // Semilla para generación aleatoria

    // Puntero inteligente para gestionar la colección de personas
    // POR QUÉ: Evitar fugas de memoria y garantizar liberación automática.
    std::unique_ptr<std::vector<Persona>> personas = nullptr;

    Monitor monitor; // Monitor para medir rendimiento
    int opcion;
    do
    {
        mostrarMenu();
        std::cin >> opcion;

        // Variables locales para uso en los casos
        size_t tam = 0;
        int indice;
        std::string idBusqueda;

        // Iniciar medición de tiempo y memoria para la operación actual
        monitor.iniciar_tiempo();
        long memoria_inicio = monitor.obtener_memoria();

        switch (opcion)
        {
        case 0:
        { // Crear nuevo conjunto de datos
            int n;
            std::cout << "\nIngrese el número de personas a generar: ";
            std::cin >> n;

            if (n <= 0)
            {
                std::cout << "Error: Debe generar al menos 1 persona\n";
                break;
            }

            // Generar el nuevo conjunto de personas
            auto nuevasPersonas = generarColeccion(n);
            tam = nuevasPersonas.size();

            // Mover el conjunto al puntero inteligente (propiedad única)
            personas = std::make_unique<std::vector<Persona>>(std::move(nuevasPersonas));

            // Medir tiempo y memoria usada
            double tiempo_gen = monitor.detener_tiempo();
            long memoria_gen = monitor.obtener_memoria() - memoria_inicio;

            std::cout << "Generadas " << tam << " personas en "
                      << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";

            // Registrar la operación
            monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
            break;
        }

        case 1:
        { // Mostrar resumen de todas las personas
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                break;
            }

            tam = personas->size();
            std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
            for (size_t i = 0; i < tam; ++i)
            {
                std::cout << i << ". ";
                (*personas)[i].mostrarResumen();
                std::cout << "\n";
            }

            double tiempo_mostrar = monitor.detener_tiempo();
            long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
            monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
            break;
        }

        case 2:
        { // Mostrar detalle por índice
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                break;
            }

            tam = personas->size();
            std::cout << "\nIngrese el índice (0-" << tam - 1 << "): ";
            if (std::cin >> indice)
            {
                if (indice >= 0 && static_cast<size_t>(indice) < tam)
                {
                    (*personas)[indice].mostrar();
                }
                else
                {
                    std::cout << "Índice fuera de rango!\n";
                }
            }
            else
            {
                std::cout << "Entrada inválida!\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            double tiempo_detalle = monitor.detener_tiempo();
            long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
            monitor.registrar("Mostrar detalle", tiempo_detalle, memoria_detalle);
            break;
        }

        case 3:
        { // Buscar por ID
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                break;
            }

            std::cout << "\nIngrese el ID a buscar: ";
            std::cin >> idBusqueda;

            if (const Persona *encontrada = buscarPorID(*personas, idBusqueda))
            {
                encontrada->mostrar();
            }
            else
            {
                std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
            }

            double tiempo_busqueda = monitor.detener_tiempo();
            long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
            monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
            break;
        }

        case 4: // Mostrar estadísticas de rendimiento
            monitor.mostrar_resumen();
            break;

        case 5: // Exportar estadísticas a CSV
            monitor.exportar_csv();
            break;

        case 6:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\n No hay Datos disponibles. \n";
                break;
            }

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            Persona v = Personalongeva::getPersonaMasLongevaValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Más longeva (país) - por valor", t_val, mem_val);

            std::cout << "\nPersona más longeva en el país (POR VALOR)\n";
            v.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &r = Personalongeva::getPersonaMasLongevaRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;
            monitor.registrar("Más longeva (país) - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona más longeva en el país (POR REFERENCIA)\n";
            r.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << "\n";
            break;
        }

        case 7:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay Datos disponibles.\n";
                break;
            }

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            auto mapaVal = Personalongeva::getPersonaMasLongevaCiudadValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Más longeva por ciudad - por valor", t_val, mem_val);

            std::cout << "\nMás longeva por ciudad (POR VALOR)\n";
            std::cout << "Ciudades: " << mapaVal.size()
                      << " | Tiempo: " << t_val << " ms | Memoria: " << mem_val << " KB\n";
            for (const auto &kv : mapaVal)
            {
                std::cout << "\nCiudad: " << kv.first << "\n";
                kv.second.mostrarResumen();
                std::cout << "\n";
            }

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            auto mapaRef = Personalongeva::getPersonaMasLongevaCiudadRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;
            monitor.registrar("Más longeva por ciudad - por referencia", t_ref, mem_ref);

            std::cout << "\nMás longeva por ciudad (POR REFERENCIA)\n";
            std::cout << "Ciudades: " << mapaRef.size()
                      << " | Tiempo: " << t_ref << " ms | Memoria: " << mem_ref << " KB\n";
            for (const auto &kv : mapaRef)
            {
                std::cout << "\nCiudad: " << kv.first << "\n";
                kv.second->mostrarResumen();
                std::cout << "\n";
            }

            std::cout << "\nTIEMPO Y MEMORIA\n";
            std::cout << "Valor:      " << t_val << " ms | " << mem_val << " KB\n";
            std::cout << "Referencia: " << t_ref << " ms | " << mem_ref << " KB\n";

            break;
        }

        case 8:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay Datos disponibles.\n";
                break;
            }

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &maxPatrimonio1 = maxPatr::personaMayorPatrimonioPaisRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (país) - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio del pais (POR REFERENCIA)\n";
            maxPatrimonio1.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << "\n";

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            Persona maxValor1 = maxPatr::personaMayorPatrimonioPaisValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;

            monitor.registrar("Mayor patrimonio (país) - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio del pais (POR VALOR)\n";
            maxValor1.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            break;
        }
        case 9:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay Datos disponibles.\n";
                break;
            }

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            auto mapaVal = maxPatr::personaMayorPatrimonioCiudadVal(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;

            monitor.registrar("Mayor patrimonio por ciudad - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio por ciudad (POR VALOR)\n";
            std::cout << "Ciudades: " << mapaVal.size()
                      << " | Tiempo: " << t_val << " ms | Memoria: " << mem_val << " KB\n";
            for (const auto &kv : mapaVal)
            {
                std::cout << "\nCiudad: " << kv.first << "\n";
                kv.second.mostrarResumen();
                std::cout << "\n";
            }

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            auto mapaRef = maxPatr::personaMayorPatrimonioCiudadRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio por ciudad - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio por ciudad (POR REFERENCIA)\n";
            std::cout << "Ciudades: " << mapaRef.size()
                      << " | Tiempo: " << t_ref << " ms | Memoria: " << mem_ref << " KB\n";
            for (const auto &kv : mapaRef)
            {
                std::cout << "\nCiudad: " << kv.first << "\n";
                kv.second->mostrarResumen();
                std::cout << "\n";
            }

            std::cout << "\nTIEMPO Y MEMORIA\n";
            std::cout << "Valor:      " << t_val << " ms | " << mem_val << " KB\n";
            std::cout << "Referencia: " << t_ref << " ms | " << mem_ref << " KB\n";

            break;
        }
        case 10:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay Datos disponibles.\n";
                break;
            }

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            Persona maxValor1 = maxPatr::personaMayorPatrimonioGrupoValor(*personas, 'A');

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Mayor patrimonio del grupo " + std::string(1, 'A') + " - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'A') << " (POR VALOR)\n";
            maxValor1.mostrar();

            Persona maxValor2 = maxPatr::personaMayorPatrimonioGrupoValor(*personas, 'B');

            t_val = monitor.detener_tiempo();
            mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Mayor patrimonio del grupo " + std::string(1, 'B') + " - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'B') << " (POR VALOR)\n";
            maxValor2.mostrar();

            Persona maxValor3 = maxPatr::personaMayorPatrimonioGrupoValor(*personas, 'C');

            t_val = monitor.detener_tiempo();
            mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Mayor patrimonio del grupo " + std::string(1, 'C') + " - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'C') << " (POR VALOR)\n";
            maxValor3.mostrar();

            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &maxPatrimonio3 = maxPatr::personaMayorPatrimonioGrupoRef(*personas, 'A');

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (" + std::string(1, 'A') + ") - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'A') << " (POR REFERENCIA)\n";
            maxPatrimonio3.mostrar();

            const Persona &maxPatrimonio4 = maxPatr::personaMayorPatrimonioGrupoRef(*personas, 'B');

            t_ref = monitor.detener_tiempo();
            mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (" + std::string(1, 'B') + ") - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'B') << " (POR REFERENCIA)\n";
            maxPatrimonio4.mostrar();

            const Persona &maxPatrimonio5 = maxPatr::personaMayorPatrimonioGrupoRef(*personas, 'C');

            t_ref = monitor.detener_tiempo();
            mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (" + std::string(1, 'C') + ") - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'C') << " (POR REFERENCIA)\n";
            maxPatrimonio5.mostrar();

            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << "\n";

            break;
        }

        case 11: // Listar y contar declarantes de renta por calendario tributario
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay Datos disponibles.\n";
                break;
            }

            std::cout << "\n=== DECLARANTES DE RENTA POR CALENDARIO TRIBUTARIO ===\n";
            // Valor
            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            listRent::listarDeclarantesGrupoValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Listar declarantes calendario - por valor", t_val, mem_val);

            std::cout << "\nListar declarantes calendario - por valor\n";
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            // Referencia
            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            listRent::listarDeclarantesGrupoRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;
            monitor.registrar("Listar declarantes calendario - por referencia", t_ref, mem_ref);

            std::cout << "\nListar declarantes calendario - por referencia\n";
            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << "\n";

            std::cout << "\nCOMPARACIÓN:\n";
            std::cout << "Valor:      " << t_val << " ms | " << mem_val << " KB\n";
            std::cout << "Referencia: " << t_ref << " ms | " << mem_ref << " KB\n";
            break;
        }
        case 12:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay Datos disponibles.\n";
                break;
            }

            std::cout << "\n=== Persona con maximo patrimonio neto ===\n";
            // Valor
            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            Persona v = maxPatrNeto::maxPatrNetoValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Persona con maximo patrimonio neto - por valor", t_val, mem_val);

            std::cout << "\nPersona con maximo patrimonio neto - por valor\n";
            v.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << " KB\n";

            // Referencia
            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &v_ref = maxPatrNeto::maxPatrNetoRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;
            monitor.registrar("Persona con maximo patrimonio neto - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con maximo patrimonio neto - por referencia\n";
            v_ref.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << " KB\n";

            std::cout << "\nCOMPARACIÓN:\n";
            std::cout << "Valor:      " << t_val << " ms | " << mem_val << " KB\n";
            std::cout << "Referencia: " << t_ref << " ms | " << mem_ref << " KB\n";
            break;
        }

        case 13:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                break;
            }

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            Persona optVal = Masjovendeclararenta::masjovenDeclaranteRentaValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Más joven declarante - por valor", t_val, mem_val);

            std::cout << "\nPersona más joven que DECLARA (POR VALOR)\n";
            optVal.mostrar();

            std::cout << "Tiempo: " << t_val << " ms | Memoria: " << mem_val << " KB\n";

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona ref = Masjovendeclararenta::masjovenDeclaranteRentaRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;
            monitor.registrar("Más joven declarante - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona más joven que DECLARA (POR REFERENCIA)\n";
            ref.mostrar();
            std::cout << "Tiempo: " << t_ref << " ms | Memoria: " << mem_ref << " KB\n";

            // Comparación
            std::cout << "\nCOMPARACIÓN:\n";
            std::cout << "Valor:      " << t_val << " ms | " << mem_val << " KB\n";
            std::cout << "Referencia: " << t_ref << " ms | " << mem_ref << " KB\n";
            break;
        }
        case 14:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay Datos disponibles.\n";
                break;
            }

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            Persona maxPatrimonioIngresos2 = maxPatr::maxPatrimonioIngresosVal(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;

            monitor.registrar("Mayor patrimonio (país) con menores ingresos - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio del pais con menores ingresos (POR VALOR)\n";
            maxPatrimonioIngresos2.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &maxPatrimonioIngresos = maxPatr::maxPatrimonioIngresosRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (país) con menores ingresos - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio del pais con menores ingresos (POR REFERENCIA)\n";
            maxPatrimonioIngresos.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << "\n";

            break;
        }
        case 15: // Salir
        {
            std::cout << "Saliendo...\n";
            break;
        }
        default:
            std::cout << "Opción inválida!\n";
        }

        // Mostrar estadísticas de la operación (excepto para opciones 4,5,6,...)
        if (opcion >= 0 && opcion <= 3)
        {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }

    } while (opcion != 15);

    return 0;
}