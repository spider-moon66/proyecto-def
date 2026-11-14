#include "Ingredientes_UI.hpp"
#include <iostream>
#include <limits>
#include <string>

void UI_Ingredientes::limpiarBuffer(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void UI_Ingredientes::eliminarIngrediente(Lista<Ingrediente>& lista)
{
    std::string solicitud;
    std::cout << "Ingrese el nombre del ingrediente que desea eliminar: ";
    std::getline(std::cin, solicitud);

    auto cmp = [&solicitud](const Ingrediente& a){
        return a.getNombre() == solicitud;
    };

    Lista<Ingrediente>::Position pos = lista.findLineal(cmp);

    if(pos == nullptr){std::cout << "El ingrediente no se encontró o no existe" << std::endl; return;}
    
    lista.del(pos);
}

void UI_Ingredientes::agregarIngrediente(Lista<Ingrediente>& lista)
{
    std::string nombre;
    float cantidad;
    std::string unidad;

    std::cout << "Ingrese el nombre del ingrediente" << std::endl;
    std::getline(std::cin, nombre);
    std::cout << "Ingrese la cantidad de " << nombre << std::endl;
    std::cin >> cantidad;
    limpiarBuffer();
    std::cout << "Ingrese la unidad de medida de la cantidad de " << nombre << std::endl;
    std::getline(std::cin, unidad);

    Ingrediente nuevo(nombre, cantidad, unidad);

    lista.ins(lista.getLast(), nuevo);
}

void UI_Ingredientes::editarNombre(Lista<Ingrediente>& lista, Lista<Ingrediente>::Position pos){
    std::string nuevoNombre;
    std::cout << "Ingrese el nuevo nombre: ";
    std::getline(std::cin, nuevoNombre);
    lista.retrieve(pos).setNombre(nuevoNombre); 
}

void UI_Ingredientes::modificarUnidad(Lista<Ingrediente>& lista, Lista<Ingrediente>::Position pos)
{
    std::string unidad;
    std::cout << "Ingrese la nueva unidad de medida" << std::endl;
    std::getline(std::cin, unidad);
    lista.retrieve(pos).setUnidad(unidad);
}

void UI_Ingredientes::modificarCantidad(Lista<Ingrediente>& lista, Lista<Ingrediente>::Position pos)
{
    float cantidad;
    do{
        std::cout << "Ingrese la nueva cantidad de "<< lista.retrieve(pos).getNombre() << std::endl;
        std::cin >> cantidad;
        lista.retrieve(pos).setCantidad(cantidad);
    }while(lista.retrieve(pos).validarCantidad()==false);
    
}

void UI_Ingredientes::verIngredientes(Lista<Ingrediente>& lista)
{
    if(lista.isEmpty())
    {
        std::cout << "No hay elementos para mostrar" << std::endl;
        return;
    }

    Lista<Ingrediente>::Position pos = lista.getFirst();

    do{
        std::cout << ". " << lista.retrieve(pos).toString() << std::endl;
        pos = lista.getNext(pos);
    }while(pos != nullptr);

    std::cout << "\n";
}

void UI_Ingredientes::modificarIngrediente(Lista<Ingrediente>& lista){
    
    std::string solicitud;
    std::cout << "Estos son los ingredientes: " << std::endl;
    verIngredientes(lista);
    std::cout << "Ingrese el nombre del ingrediente que desea modificar" << std::endl;
    std::getline(std::cin, solicitud);
    
    auto cmp = [&solicitud](const Ingrediente& a){
        return a.getNombre() == solicitud;
    };

    Lista<Ingrediente>::Position pos = lista.findLineal(cmp);

    int op;

    std::cout << "¿Qué desea modificar?" << std::endl;
    do{
        std::cout << "1. Cantidad" << std::endl
                << "2. Unidad de medida" << std::endl
                << "3. Editar nombre" << std::endl
                << "0. Volver" << std::endl;
        std::cin >> op;
        limpiarBuffer();
        switch(op){
        case 1:
            modificarCantidad(lista, pos);
            break;
        case 2:
            modificarUnidad(lista, pos);
            break;
        case 3:
            editarNombre(lista, pos);
            break;
        case 0:
            std::cout << "Volviendo..." << std::endl;
        default:
            break;
    }
    }while(op != 0);
}

void UI_Ingredientes::printOpciones()
{
    std::cout << "1. Eliminar Ingrediente" << std::endl
            << "2. Agregar Ingrediente" << std::endl
            << "3. Modificar Ingrediente" << std::endl
            << "4. Ver ingredientes" << std::endl
            << "0. Regresar" << std::endl;
}

void UI_Ingredientes::control(int& op, Lista<Ingrediente>& lista){
    switch(op){
        case 1:
            eliminarIngrediente(lista);
            break;
        case 2:
            agregarIngrediente(lista);
            break;
        case 3:
            modificarIngrediente(lista);
            break;
        case 4:
            verIngredientes(lista);
            break;
        case 0:
            std::cout << "Regresando..." << std::endl;
            break;
        default:
            std::cout << "Ingrese una opción valida" << std::endl;
            break;
    }
}

void UI_Ingredientes::menu(Lista<Ingrediente>& lista)
{
    int op;
    do{
        printOpciones();
        std::cin >> op;
        limpiarBuffer();
        control(op, lista);
    }while(op != 0);
}