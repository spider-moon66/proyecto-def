#ifndef __RECETA_H__
#define __RECETA_H__

#include <string>
#include <iostream>
#include <fstream>
#include "LDLCCED.hpp"
#include "LDSL.hpp"
#include "Ingrediente.hpp"


class Receta{
    public:
        //Dos funciones que me permiten mantener simples las operaciones sobre instrucciones
        //Enumerar de forma automatica cada instrucción segun el orden de inserción
        short int autoNum();
        class Instruccion{
            private:
                short int n_ins = 0;
                std::string predicado;
            public:
                Instruccion();
                Instruccion(const std::string&, const short int);
                std::string getPredicado() const;
                short int getNum() const;
                void setPredicado(const std::string&);
                void setNum(const short int);
                std::string toString();
                void serialize(std::ofstream&, const char& delim = ';');
                void deserialize(const std::string& str, const char& delim = ';');
            };
    private:
        Lista <Ingrediente> ingredientesData;
        std::string nombreReceta;
        std::string descripcion;
        
        short int contadorINS = 0;
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
        //Decrementar de forma automatica cada instrucción
        void autoDecr(LDLCCED<Instruccion>::Position);

        bool operator==(const Receta&) const;
        bool operator>(const Receta&) const;
        bool operator<(const Receta&) const;
        bool operator<=(const Receta&) const;
        bool operator>=(const Receta&) const;
        //Serializar/Deserializar
        void serialize(std::ofstream&, const char& delim = '*');
        void deserialize(const std::string& str, const char& delim = '*');
};

#endif // __RECETA_H__