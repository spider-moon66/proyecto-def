#ifndef __INGREDIENTES_UI_H__
#define __INGREDIENTES_UI_H__

#include "LDSL.hpp"
#include "Ingrediente.hpp"
#include <string>

class UI_Ingredientes{
    public:
    //Preparo los métodos para recibir una lista como parametro, en este caso una lista de tipo Ingrediente 
    void eliminarIngrediente(Lista<Ingrediente>&);
    void agregarIngrediente(Lista<Ingrediente>&);
    void editarNombre(Lista<Ingrediente>&, Lista<Ingrediente>::Position);
    void modificarUnidad(Lista<Ingrediente>&, Lista<Ingrediente>::Position);
    void modificarCantidad(Lista<Ingrediente>&, Lista<Ingrediente>::Position);
    void modificarIngrediente(Lista<Ingrediente>&);
    void verIngredientes(Lista<Ingrediente>&);
    void printOpciones();
    void control(int&, Lista<Ingrediente>&);
    //El menu de ingredientes recibe la lista desde la instancia de receta en la que fue llamado
    void menu(Lista<Ingrediente>&);
    void limpiarBuffer();
};

#endif // __INGREDIENTES_UI_H__