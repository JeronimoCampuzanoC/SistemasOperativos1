#include <iostream>
#include <vector>
#include <limits> // Para manejo de límites de entrada
#include <memory> // Para std::unique_ptr y std::make_unique
#include "persona.h"
#include "generador.h"
#include "monitor.h" // Nuevo header para monitoreo
#include "personalongeva.h"
#include "masJovenDeclaraRenta.h"
#include "listRent.h"
#include "maxPatr.h"
#include "maxPatrNeto.h"

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

int main()
{
    srand(time(nullptr));

    // Usar unique_ptr para manejar la colección de personas
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    Monitor monitor;

    int opcion;
    do
    {
        mostrarMenu();
        std::cin >> opcion;

        size_t tam = 0;
        int indice;
        std::string idBusqueda;

        // Iniciar medición de tiempo y memoria para esta operación
        monitor.iniciar_tiempo();
        long memoria_inicio = monitor.obtener_memoria();

        switch (opcion)
        {
        case 0:
        {
            int n;
            std::cout << "\nIngrese el número de personas a generar: ";
            std::cin >> n;

            if (n <= 0)
            {
                std::cout << "Error: Debe generar al menos 1 persona\n";
                break;
            }

            // Generar el nuevo conjunto de datos
            personas = std::make_unique<std::vector<Persona>>(generarColeccion(n));
            tam = personas->size();

            double tiempo_gen = monitor.detener_tiempo();
            long memoria_gen = monitor.obtener_memoria() - memoria_inicio;

            std::cout << "Generadas " << tam << " personas en "
                      << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";

            monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
            break;
        }

        case 1:
        {
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
        {
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
        {
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

        case 4:
            monitor.mostrar_resumen();
            break;

        case 5:
            monitor.exportar_csv();
            break;

        case 6:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\n No hay datos \n";
                break;
            }
            monitor.iniciar_tiempo();
            long mem0 = monitor.obtener_memoria();
            Persona v = PersonaMasLongevaValor(*personas);
            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem0;
            monitor.registrar("Persona Longeva (Valor): ", t_val, mem_val);
            std::cout << "\nPersona más longeva del País (por valor)\n";
            v.mostrar();
            std::cout << "\n";
            std::cout << "Tiempo: " << t_val << " ms, Memoria: " << mem_val << " KB\n";

            monitor.iniciar_tiempo();
            long mem0_ref = monitor.obtener_memoria();
            const Persona &r = PersonaMasLongevaRef(*personas);
            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem0_ref;
            monitor.registrar("Persona Longeva (Ref): ", t_ref, mem_ref);
            std::cout << "\nPersona más longeva del País (por Referencia)\n";
            r.mostrar();
            std::cout << "\n";
            std::cout << "Tiempo: " << t_ref << " ms, Memoria: " << mem_ref << " KB\n";
            break;
        }
        case 7:
        {
            if (!personas || personas->empty())
            {
                std::cout << "\nNo hay datos.\n";
                break;
            }

            // por valor
            monitor.iniciar_tiempo();
            long mem0 = monitor.obtener_memoria();
            auto mVal = PersonaMasLongevaCiudadValor(*personas);
            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem0;
            monitor.registrar("Longeva por ciudad (valor)", t_val, mem_val);

            std::cout << "\nPersona Más Longeva por ciudad (Valor)\n";
            std::cout << "Ciudades: " << mVal.size() << " | Tiempo: " << t_val << " ms | Memoria: " << mem_val << " KB\n";
            for (auto &kv : mVal)
            {
                std::cout << kv.first << ": ";
                kv.second.mostrarResumen();
                std::cout << "\n";
            }

            // por referencia
            monitor.iniciar_tiempo();
            mem0 = monitor.obtener_memoria();
            auto mRef = PersonaMasLongevaPorCiudadRef(*personas);
            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem0;
            monitor.registrar("Longeva por ciudad (ref)", t_ref, mem_ref);

            std::cout << "\nPersona Más Longeva por ciudad (Referencia)\n";
            std::cout << "Ciudades: " << mRef.size() << " | Tiempo: " << t_ref << " ms | Memoria: " << mem_ref << " KB\n";
            for (auto &kv : mRef)
            {
                std::cout << kv.first << ": ";
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

            const Persona &maxPatrimonio1 = personaMayorPatrimonioPaisRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (país) - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio del pais (POR REFERENCIA)\n";
            maxPatrimonio1.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << "\n";

            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            Persona maxValor1 = personaMayorPatrimonioPaisValor(*personas);

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

            auto mapaVal = personaMayorPatrimonioCiudadVal(*personas);

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

            auto mapaRef = personaMayorPatrimonioCiudadRef(*personas);

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

            Persona maxValor1 = personaMayorPatrimonioGrupoValor(*personas, 'A');

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Mayor patrimonio del grupo " + std::string(1, 'A') + " - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'A') << " (POR VALOR)\n";
            maxValor1.mostrar();

            Persona maxValor2 = personaMayorPatrimonioGrupoValor(*personas, 'B');

            t_val = monitor.detener_tiempo();
            mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Mayor patrimonio del grupo " + std::string(1, 'B') + " - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'B') << " (POR VALOR)\n";
            maxValor2.mostrar();

            Persona maxValor3 = personaMayorPatrimonioGrupoValor(*personas, 'C');

            t_val = monitor.detener_tiempo();
            mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Mayor patrimonio del grupo " + std::string(1, 'C') + " - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'C') << " (POR VALOR)\n";
            maxValor3.mostrar();

            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &maxPatrimonio3 = personaMayorPatrimonioGrupoRef(*personas, 'A');

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (" + std::string(1, 'A') + ") - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'A') << " (POR REFERENCIA)\n";
            maxPatrimonio3.mostrar();

            const Persona &maxPatrimonio4 = personaMayorPatrimonioGrupoRef(*personas, 'B');

            t_ref = monitor.detener_tiempo();
            mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (" + std::string(1, 'B') + ") - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio de " << std::string(1, 'B') << " (POR REFERENCIA)\n";
            maxPatrimonio4.mostrar();

            const Persona &maxPatrimonio5 = personaMayorPatrimonioGrupoRef(*personas, 'C');

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

            listarDeclarantesGrupoValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Listar declarantes calendario - por valor", t_val, mem_val);

            std::cout << "\nListar declarantes calendario - por valor\n";
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            // Referencia
            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            listarDeclarantesGrupoRef(*personas);

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

            Persona v = maxPatrNetoValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Persona con maximo patrimonio neto - por valor", t_val, mem_val);

            std::cout << "\nPersona con maximo patrimonio neto - por valor\n";
            v.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << " KB\n";

            // Referencia
            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &v_ref = maxPatrNetoRef(*personas);

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

            // --- Por VALOR ---
            monitor.iniciar_tiempo();
            long mem_ini_val = monitor.obtener_memoria();

            auto optVal = masJovenDeclaraRentaValor(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;
            monitor.registrar("Más joven declarante (Valor)", t_val, mem_val);

            std::cout << "\n[STRUCT] Persona más joven que DECLARA renta (POR VALOR)\n";
            if (optVal)
            {
                optVal->mostrar(); // usa tu mostrar() de Persona (estructuras)
                std::cout << "\n";
            }
            else
            {
                std::cout << "No hay ningún declarante de renta.\n";
            }
            std::cout << "Tiempo: " << t_val << " ms | Memoria: " << mem_val << " KB\n";

            // --- Por REFERENCIA ---
            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona *pref = masJovenDeclaraRentaRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;
            monitor.registrar("Más joven declarante (Referencia)", t_ref, mem_ref);

            std::cout << "\n[STRUCT] Persona más joven que DECLARA renta (POR REFERENCIA)\n";
            if (pref)
            {
                pref->mostrar();
                std::cout << "\n";
            }
            else
            {
                std::cout << "No hay ningún declarante de renta.\n";
            }
            std::cout << "Tiempo: " << t_ref << " ms | Memoria: " << mem_ref << " KB\n";

            // Comparación
            std::cout << "\nTIEMPO Y MEMORIA\n";
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

            Persona maxPatrimonioIngresos2 = maxPatrimonioIngresosVal(*personas);

            double t_val = monitor.detener_tiempo();
            long mem_val = monitor.obtener_memoria() - mem_ini_val;

            monitor.registrar("Mayor patrimonio (país) con menores ingresos - por valor", t_val, mem_val);

            std::cout << "\nPersona con mayor patrimonio del pais con menores ingresos (POR VALOR)\n";
            maxPatrimonioIngresos2.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_val << " ms, Memoria Usada: " << mem_val << "\n";

            monitor.iniciar_tiempo();
            long mem_ini_ref = monitor.obtener_memoria();

            const Persona &maxPatrimonioIngresos = maxPatrimonioIngresosRef(*personas);

            double t_ref = monitor.detener_tiempo();
            long mem_ref = monitor.obtener_memoria() - mem_ini_ref;

            monitor.registrar("Mayor patrimonio (país) con menores ingresos - por referencia", t_ref, mem_ref);

            std::cout << "\nPersona con mayor patrimonio del pais con menores ingresos (POR REFERENCIA)\n";
            maxPatrimonioIngresos.mostrar();
            std::cout << "Tiempo de Ejecución: " << t_ref << " ms, Memoria Usada: " << mem_ref << "\n";

            break;
        }
        case 15:
            std::cout << "Saliendo...\n";
            break;

        default:
            std::cout << "Opción inválida!\n";
        }

        // Mostrar estadísticas para las operaciones principales
        if (opcion >= 0 && opcion <= 3)
        {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }

    } while (opcion != 15);

    return 0;
}