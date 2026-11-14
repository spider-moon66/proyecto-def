#ifndef __RECETA_UI_H__
#define __RECETA_UI_H__

#include "LDLCCED.hpp"
#include "Lista.hpp"
#include "LDSL.hpp"
#include "Receta.hpp"
#include "Ingrediente.hpp"
#include "Ingredientes_UI.hpp"

class Receta_UI{
    public:
    bool validarReceta(LDLCCED <Receta>&, Receta&);
    void modificarInstrucciones(Receta&);
    void limpiarBuffer();
    void nuevaReceta(LDLCCED <Receta>&, UI_Ingredientes&);
    void borrarReceta(LDLCCED <Receta>&);
    void modificarReceta(LDLCCED <Receta>&);
    void menuIngredientes(UI_Ingredientes&, LDLCCED <Receta>&);
    void mostrarOpciones();
    LDLCCED<Receta>::Position buscarReceta(LDLCCED <Receta>&, const std::string&);
    void verReceta(LDLCCED <Receta>&, UI_Ingredientes&, LDLCCED<Receta>::Position);
    //void ordenarReceta(LDLCCED <Receta>&);
    void verLista(LDLCCED <Receta>&);
    void control(LDLCCED <Receta>&, UI_Ingredientes&);
    //void guardar(LDLCCED <Receta>&);
    //void cargar(LDLCCED <Receta>&);
};

#endif // __RECETA_UI_H__