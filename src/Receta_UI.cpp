#include "Receta_UI.hpp"
#include "Ingredientes_UI.hpp"
#include <limits>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

void Receta_UI::limpiarBuffer(){
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Para confirmar que no existan recetas con el mismo nombre y la misma descripcion
//Podria existir una receta con el mismo nombre pero que sea una variación y eso se notaría en la desc.
bool Receta_UI::validarReceta(LDLCCED <Receta>& lista, Receta& nueva)
{
    if(lista.isEmpty()){return true;}

    auto cmp = [nueva](const Receta& a){
        return a.getNombre() == nueva.getNombre() && a.getDescripcion() == nueva.getDescripcion();
    };

    LDLCCED<Receta>::Position pos = lista.findLineal(cmp);

    if(pos == nullptr){return true;}

    return false;
}

void Receta_UI::modificarInstrucciones(Receta& receta)
{
    char op;
    std::cout << "Seleccione una acción" << std::endl;
    std::cout << "[V]er lista de instrucciones" << std::endl;
    std::cout << "[M]odificar instrucción" << std::endl;
    std::cout << "[B]orrar instrucción" << std::endl;
    std::cout << "[A]gregar instrucción" << std::endl;
    std::cout << "[R]egresar" << std::endl;
    do{
        std::cin >> op;
        op = toupper(op);
        if(op != 'A' && op != 'B' && op != 'M' && op != 'V' && op != 'R'){
            std::cout << "Seleccione una acción valida (M, B, A, R, V)" << std::endl;
        }
    }while(op != 'A' && op != 'B' && op != 'M' && op != 'R' && op != 'V');
    
    switch(op){
        case 'V':
        {
            for(int i = 0; i <= receta.accesoInstrucciones().getLastPos(); i++){
                std::cout << i + 1 << " " << receta.accesoInstrucciones().retrieve(i) << "\n\n";
            }
            break;
        }
        case 'M':{
            int ins;
            std::string texto_nuevo;

            std::cout << "Estas son las instrucciones: " << std::endl;

            for(int i = 0; i <= receta.accesoInstrucciones().getLastPos(); i++){
                std::cout << i + 1 << " " << receta.accesoInstrucciones().retrieve(i) << "\n\n";
            }

            std::cout << "¿Qué instrucción desea modificar?" << std::endl;
            std::cin >> ins;
            ins -= 1;
            if(ins > receta.accesoInstrucciones().getLastPos() || ins == -1){break;}
            limpiarBuffer();
            std::cout << "Escriba la instrucción modificada: " << std::endl;
            std::getline(std::cin, texto_nuevo);
            receta.accesoInstrucciones().retrieve(ins) = texto_nuevo;
            std::cout << "Receta modificada correctamente" << std::endl;
            break;
        }
        case 'B':{
            int ins;

            std::cout << "Estas son las instrucciones: " << std::endl;
            
            for(int i = 0; i <= receta.accesoInstrucciones().getLastPos(); i++){
                std::cout << i + 1 << ". " << receta.accesoInstrucciones().retrieve(i) << "\n";
            }
            std::cout << "\n";
            std::cout << "Qué instrucción que desea borrar" << std::endl;
            std::cin >> ins;
            ins -= 1;

            if(!(receta.accesoInstrucciones().del(ins)) || ins == -1){
                std::cout << "La instrucción no existe" << std::endl;
            }else{
                std::cout << "Eliminada correctamente" << std::endl;
            }
            break;
        }
        case 'A':{
            std::string texto_nuevo;

            std::cout << "Estas son las instrucciones: " << std::endl;
            
            for(int i = 0; i <= receta.accesoInstrucciones().getLastPos(); i++){
                std::cout << i + 1 << " " << receta.accesoInstrucciones().retrieve(i) << "\n\n";
            }

            std::cout << "Escriba la instrucción que desea agregar" << std::endl;
            std::getline(std::cin, texto_nuevo);
            receta.accesoInstrucciones().agregar(texto_nuevo);
            std::cout << "Receta modificada correctamente" << std::endl;
            break;
        }
        case 'R':{
            std::cout << "Regresando..." << std::endl;
            break;
        }
    }

}

void Receta_UI::nuevaReceta(LDLCCED <Receta>& lista, UI_Ingredientes& sub)
{
    std::string nombre;
    std::string desc;
    std::string instrucciones;

    std::cout << "Ingrese el nombre de la receta: " << std::endl;
    std::getline(std::cin, nombre);
    std::cout << "Ingrese la descripcion: " << std::endl;
    std::getline(std::cin, desc);

    Receta nueva(nombre, desc);

    if(!(validarReceta(lista, nueva)))
    {
        std::cout << "Ya existe una receta igual!" << std::endl;
    }
    else{
        char op;

        std::cout << "Agregue los ingredientes: " << std::endl;

        do{
            sub.agregarIngrediente(nueva.accesoIngredientes());
            std::cout << "Agregado \n" << "¿Agregar más ingredientes?: " << "Y/N" << std::endl;
            std::cin >> op;
            limpiarBuffer();
            op = std::toupper(op);
        }while(op != 'N');

        int i = 0;
        std::cout << "Agregue las instrucciones: " << std::endl;
        do{
            std::cout << "Escriba la instruccion " << i + 1 << std::endl;
            std::getline(std::cin, instrucciones);
            nueva.accesoInstrucciones().agregar(instrucciones);
            i++;
            if(nueva.accesoInstrucciones().isFull())
            {
                std::cout << "Ha excedido el limite de instrucciones" << std::endl;
            }else{
                std::cout << "Agregado \n" << "¿Agregar más instrucciones?: " << "Y/N" << std::endl;
                std::cin >> op;
                limpiarBuffer();
                op = std::toupper(op);
            }
        }while(op != 'N');

        lista.insFinal(nueva);
    }
}

void Receta_UI::borrarReceta(LDLCCED <Receta>& lista)
{
    std::string solicitud;
    std::cout << "Ingrese el nombre de la receta que desea eliminar" << std::endl;
    std::getline(std::cin, solicitud);

    LDLCCED<Receta>::Position pos = buscarReceta(lista, solicitud);

    if(pos == nullptr){
        std::cout << "No se encontró la receta que desea eliminar" << std::endl;
        return;
    }

    lista.del(pos);
    std::cout << "Receta eliminada correctamente" << std::endl;
}

void Receta_UI::modificarReceta(LDLCCED <Receta>& lista)
{
    std::string solicitud;
    std::cout << "Ingrese el nombre de la receta que desea modificar" << std::endl;
    std::getline(std::cin, solicitud);

    LDLCCED<Receta>::Position pos = buscarReceta(lista, solicitud);
    if(pos == nullptr){
        std::cout << "No se encontró la receta que desea modificar" << std::endl;
        return;
    }

    char op;
    std::cout << "¿Qué desea modificar?" << std::endl;
    do{
        std::cout << "[N]ombre \n" << "[D]escripción \n" << "[I]nstrucciones \n" << std::endl;
        std::cin >> op;
        limpiarBuffer();
        op = toupper(op);
    }while(op != 'N' && op != 'D' && op != 'I');

    switch(op){
        case 'N':
        {
            std::string nombre;
            std::cout << "Ingrese el nuevo nombre: " << std::endl;
            std::getline(std::cin, nombre);
            lista.retrieve(pos).setNombre(nombre);
            std::cout << "Receta modificada correctamente" << std::endl;
            break;
        }
        case 'D':
        {
            std::string desc;
            std::cout << "Ingrese la nueva descripción: " << std::endl;
            std::getline(std::cin, desc);
            lista.retrieve(pos).setDescripcion(desc);
            std::cout << "Receta modificada correctamente" << std::endl;
            break;
        }
        case 'I':
        {
            modificarInstrucciones(lista.retrieve(pos));
            break;
        }
    }
}

void Receta_UI::menuIngredientes(UI_Ingredientes& sub, LDLCCED <Receta>& lista)
{
    std::string solicitud;
    std::cout << "¿Qué receta?" << std::endl;
    getline(std::cin, solicitud);
    

    LDLCCED<Receta>::Position pos = buscarReceta(lista, solicitud);

    if(pos == nullptr){std::cout << "No se encontró la receta" << std::endl;}
    else{
        std::cout << "Modificando los ingredientes de: " << lista.retrieve(pos).getNombre() << std::endl;
        sub.menu(lista.retrieve(pos).accesoIngredientes());
    }
}

typename LDLCCED<Receta>::Position Receta_UI::buscarReceta(LDLCCED <Receta>& lista, const std::string& solicitud)
{
    if(lista.isEmpty()){std::cout << "La lista se encuentra vacia" << std::endl; return nullptr;};

    auto cmp = [&solicitud](const Receta& a){
        return a.getNombre() == solicitud;
    };

    LDLCCED<Receta>::Position pos = lista.findLineal(cmp);

    return pos;
}



void Receta_UI::verReceta(LDLCCED <Receta>& lista, UI_Ingredientes& sub, LDLCCED<Receta>::Position pos)
{

    std::cout << lista.retrieve(pos).toString();
    std::cout << std::endl;
    sub.verIngredientes(lista.retrieve(pos).accesoIngredientes());
    std::cout << std::string(40, '-') << std::endl;
    for(int i = 0; i <= lista.retrieve(pos).accesoInstrucciones().getLastPos(); i++){
        std::cout << "Paso: " << i + 1 << ". " << lista.retrieve(pos).accesoInstrucciones().retrieve(i) << std::endl;
    }
    std::cout << std::string(40, '-') << std::endl;
}

/*void Receta_UI::ordenarReceta(LDLCCED <Receta>& lista)
{
    auto cmp = [](const Receta& a, const Receta& b){
        return a.getNombre() > b.getNombre();
    };
    lista.ShellSort(cmp);
}*/

void Receta_UI::verLista(LDLCCED <Receta>& lista)
{
    std::cout << "Sus recetas: " << std::endl;
    if(lista.isEmpty()){
        std::cout << "Aun no tiene recetas" << std::endl;
    }else{
        LDLCCED<Receta>::Position i = lista.getFirst();
        while(i != lista.getLast()){
            std::cout << std::string(40, '-') << std::endl;
            std::cout << std::left << std::setw(30) << lista.retrieve(i).getNombre() << std::endl;
            std::cout << std::string(40, '-') << std::endl;
            i = i->getNextNode();
        }
            std::cout << std::string(40, '-') << std::endl;
            std::cout << std::left << std::setw(30) << lista.retrieve(i).getNombre() << std::endl;
            std::cout << std::string(40, '-') << std::endl;
    }
}

void Receta_UI::mostrarOpciones()
{
    std::cout << "[V]er recetas" << std::endl
            << "[N]ueva receta" << std::endl
            << "[M]odificar receta" << std::endl
            << "Mos[t]rar receta" << std::endl
            << "[I]r al menu de ingredientes" << std::endl
            << "[R]egresar" << std::endl;
}

void Receta_UI::control(LDLCCED <Receta>& lista, UI_Ingredientes& sub)
{
    char op;
    do{
        std::cout << "Seleccione una de las opciones" << std::endl;
        mostrarOpciones();
        do{
            std::cin >> op;
            limpiarBuffer();
            op = toupper(op);
            if(op != 'N' && op != 'M' && op != 'T' && op != 'I' && op != 'R' && op != 'G' && op != 'C' && op != 'V' && op != 'O'){
                std::cout << "Seleccione una acción valida (V, N, M, B, I, O, G, C, R)" << std::endl;
            }
        }while(op != 'N' && op != 'M' && op != 'T' && op != 'I' && op != 'R' && op != 'G' && op != 'C' && op != 'V' && op != 'O');

        switch(op){
            case 'V':{
                verLista(lista);
                break;
            }
            case 'N':{
                nuevaReceta(lista, sub);
                break;
            }
            case 'M':{
                modificarReceta(lista);
                break;
            }
            case 'T':{
                std::string solicitud;
                std::cout << "Ingrese el nombre de la receta" << std::endl;
                std::getline(std::cin, solicitud);
                LDLCCED<Receta>::Position pos = buscarReceta(lista, solicitud);
                verReceta(lista, sub, pos);
                break;
            }
            case 'I':{
                menuIngredientes(sub, lista);
                break;
            }
            case 'R':{
                break;
            }
            case 'G':{
                //guardar(lista);
                break;
            }
            case 'C':{
                //cargar(lista);
                break;
            }
            case 'O':{
                //ordenarReceta(lista);
                break;
            } 
        }
    }while(op != 'R');
}

/*void Receta_UI::guardar(LDLCCED <Receta>& lista)
{
    std::ofstream archivo;

    archivo.open("PDS.txt", std::ios::out);

    if(archivo.fail()){
        throw std::runtime_error("No se pudo abrir el archivo");
    }

    lista.serializar(archivo);
    archivo.close();
}

void Receta_UI::cargar(LDLCCED <Receta>& lista)
{
    std::ifstream archivo;
    std::string str;

    archivo.open("PDS.txt", std::ios::in);

    if(archivo.fail()){
        throw std::runtime_error("No se pudo abrir el archivo");
    }

    std::getline(archivo, str);

    lista.deserializar(str);

    archivo.close();
}*/
