#include "Ingrediente.hpp"
#include <fstream>
#include <stdexcept>

bool Ingrediente::validarCantidad()
{
    return cantidad > 0;
}

Ingrediente::Ingrediente(): 
nombreIngrediente(), 
cantidad(0), 
unidad(){}

Ingrediente::Ingrediente(const Ingrediente& other)
{
    this->nombreIngrediente = other.nombreIngrediente;
    this->cantidad = other.cantidad;
    this->unidad = other.unidad;
}

Ingrediente::Ingrediente(std::string n, float c, std::string u) : 
    nombreIngrediente(n), 
    cantidad(c), 
    unidad(u){}

std::string Ingrediente::getNombre() const
{
    return nombreIngrediente;
}

float Ingrediente::getCantidad() const
{
    return cantidad;
}

std::string Ingrediente::getUnidad() const
{
    return unidad;
}

void Ingrediente::setCantidad(float c)
{
    this->cantidad = c;
}

void Ingrediente::setUnidad(std::string u)
{
    this->unidad = u;
}

void Ingrediente::setNombre(std::string n)
{
    this->nombreIngrediente = n;
}
/*Generalmente las comparaciones se realizan por medio de id's o elementos unicos por instancia
no siempre se utiliza el nombre, pero en esta ocasión lo utilizo para que no existan redundancias
en la lista de ingredientes, ej.:
2 tazas de harina != 3 tazas de harina, pero para un humano lo logico seria tener solo "5 tazas de harina"*/
bool Ingrediente::operator==(const Ingrediente& other) const
{
    return this->nombreIngrediente == other.nombreIngrediente;
}

std::ostream& operator<<(std::ostream& stream, const Ingrediente& este)
{
    stream << "Nombre: " << este.nombreIngrediente << std::endl;
    stream << "Cantidad: " << este.cantidad << " ";
    stream << este.unidad << std::endl;
    return stream;
}

std::string Ingrediente::toString(){
    return nombreIngrediente + " " + std::to_string(cantidad) + " "  + unidad + "\n";
}

void Ingrediente::serialize(std::ofstream& archivo, const char delim)
{
    archivo << this->nombreIngrediente << delim;
    archivo << this->cantidad << delim;
    archivo << this->unidad << delim;
}

void Ingrediente::deserialize(std::stringstream& str, const char delim)
{
    std::string cantidadStr;

    std::getline(str, this->nombreIngrediente, delim);
    std::getline(str, cantidadStr, delim);
    this->cantidad = std::stof(cantidadStr);
    std::getline(str, this->unidad, delim);
}