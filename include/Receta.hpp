#ifndef __RECETA_H__
#define __RECETA_H__

#include <string>
#include <iostream>
#include <fstream>
#include "LDLCCED.hpp"
#include "LDSL.hpp"
#include "Ingrediente.hpp"

class Receta{
    private:
        Lista <Ingrediente> ingredientesData;
        std::string nombreReceta;
        std::string descripcion;

        class Instruccion{
            private:
                short int n_ins = 0;
                std::string predicado;
            public:
                Instruccion();
                Instruccion(const std::string&, const short int);
                std::string getPredicado();
                short int getNum();
                void setPredicado(const std::string&);
                void setNum(const short int);
                std::string toString();
        };

        LDLCCED<Instruccion> instrucciones;

    public:
        std::string toString();
        Receta();
        Receta(const Receta&);
        Receta(std::string&, std::string&);

        std::string getNombre() const;
        std::string getDescripcion() const;

        void setIngrediente(Ingrediente&);
        void setNombre(std::string&);
        void setDescripcion(std::string&);
        void setInstrucciones(const Instruccion&);
        //Asi el menu de ingredientes puede operar sobre la lista de ingredientes cuando sea llamado desde el menu de recetas
        Lista <Ingrediente>& accesoIngredientes();
        LDLCCED<Instruccion>& accesoInstrucciones();
        bool operator==(const Receta&) const;
        bool operator>(const Receta&) const;
        bool operator<(const Receta&) const;
        bool operator<=(const Receta&) const;
        bool operator>=(const Receta&) const;
        //Serializar/Deserializar
        void serializar(std::ofstream&, const char& delim = '*');
        void deserializar(const std::string& str, const char& delim = '*');
};

#endif // __RECETA_H__