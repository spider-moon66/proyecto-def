#ifndef __INGREDIENTE_H__
#define __INGREDIENTE_H__

#include <string>			
#include <iostream>
#include <sstream>
#include <fstream>

class Ingrediente{
    private:
        std::string nombreIngrediente;
        //Ej. 200 ml de algo
        float cantidad;
        //ml, oz, g, kg, etc.
        std::string unidad;
    public:
        Ingrediente();
        Ingrediente(const Ingrediente&);
        Ingrediente(std::string, float, std::string);
        std::string getNombre() const;
        float getCantidad() const;
        std::string getUnidad() const;
        void setNombre(std::string);
        void setCantidad(std::string);
        void setCantidad(float);
        void setUnidad(std::string);
        bool operator==(const Ingrediente&) const;
        friend std::ostream& operator<<(std::ostream&, const Ingrediente&);
        std::string toString();
        bool validarCantidad();
        void serialize(std::ofstream&, const char delim = '|');
        void deserialize(std::stringstream& str, const char delim = '|');
        
};

#endif //__INGREDIENTE_H__