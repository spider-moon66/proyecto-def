
#include "LDSL.hpp"
#include "LDLCCED.hpp"
#include "Receta_UI.hpp"
#include "Receta.hpp"
#include "Ingredientes_UI.hpp"

int main()
{
    
    UI_Ingredientes menu_Ingredientes;
    LDLCCED<Receta> Recetas;
    Receta_UI menu_recetas;

    menu_recetas.control(Recetas, menu_Ingredientes);

    return EXIT_SUCCESS;
}