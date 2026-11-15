#include "Receta.hpp"
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <iostream>

std::string Receta::toString()
{
    return "Receta: " + nombreReceta + "\n" + "Descripción: " + descripcion + "\n" + ingredientesData.toString() + instrucciones.toString();
}

Receta::Receta(): 
nombreReceta(""),
descripcion(""),
instrucciones(),
ingredientesData(){}

Receta::Receta(const Receta& other) : 
nombreReceta(other.nombreReceta), 
descripcion(other.descripcion), 
instrucciones(other.instrucciones), 
ingredientesData(other.ingredientesData)
{}

Receta::Receta(std::string& n, std::string& d):
nombreReceta(n),
descripcion(d)
{}

std::string Receta::getNombre() const
{
    return nombreReceta;
}

std::string Receta::getDescripcion() const
{
    return descripcion;
}

void Receta::setIngrediente(Ingrediente& nuevo)
{
    ingredientesData.ins(ingredientesData.getLast(), nuevo);
}

void Receta::setNombre(std::string& nuevo)
{
    this->nombreReceta = nuevo;
}

void Receta::setDescripcion(std::string& nuevo)
{
    this->descripcion = nuevo;
}

void Receta::setInstrucciones(const Instruccion& nuevo)
{
    this->instrucciones.insSorted(nuevo);
}

bool Receta::operator==(const Receta& other) const
{
    return this->nombreReceta == other.nombreReceta && this->nombreReceta == other.nombreReceta;
}

bool Receta::operator>(const Receta& other) const
{
    return this->getNombre() > other.getNombre();
}

bool Receta::operator<(const Receta& other) const
{
    return this->getNombre() < other.getNombre();
}

void Receta::serialize(std::ofstream& archivo, const char& delim)
{

    if(archivo.fail()){
       throw std::runtime_error("No se pudo abrir el archivo");
    }

    archivo << nombreReceta << delim;
    
    archivo << descripcion << delim;

    ingredientesData.serialize(archivo, '|');

    instrucciones.serialize(archivo, '#');
    
    archivo << delim;

}

void Receta::deserialize(const std::string& str, const char& delim)
{
    std::stringstream myStr(str);
    std::string nombre;
    std::string desc;

    std::getline(myStr, nombre, delim);

    std::getline(myStr, desc, delim);

    ingredientesData.deserialize(str, '|');
    instrucciones.deserialize(str, '#');

}

Lista<Ingrediente>& Receta::accesoIngredientes()
{
    return ingredientesData;
}

LDLCCED<typename Receta::Instruccion>& Receta::accesoInstrucciones()
{
    return instrucciones;
}

//Implementación de instrucciones
Receta::Instruccion::Instruccion() : predicado(""){}

Receta::Instruccion::Instruccion(const std::string& t, const short int num):
predicado(t),
n_ins(num)
{}

short int Receta::Instruccion::getNum() const{
    return n_ins;
}

std::string Receta::Instruccion::getPredicado() const{
    return predicado;
}

void Receta::Instruccion::setNum(const short int n){
    n_ins = n;
}

void Receta::Instruccion::setPredicado(const std::string& t){
    predicado = t;
}

std::string Receta::Instruccion::toString(){
    return std::to_string(n_ins) + ". " + predicado + "/n";
}

/*Se manda llamar solo cuando se inserta un elemento, 
contemplando que la lista de instrucciones sólo admite inserción ordenada para simplificar las operaciones desde la interfaz*/
short int Receta::autoNum(){
    return contadorINS++;
}

/*Se invoca cuando se elimina un elemento, 
en tal caso tiene que decrementar el contador y además tiene que cambiar el numero de instruccion de las instrucciones consecutivas*/
void Receta::autoDecr(LDLCCED<Instruccion>::Position pos){
    //El peor caso es que se elimine la primer instruccion
    pos = pos->getNextNode();

    while(pos != instrucciones.getLast()->getNextNode()){
        pos->getData().setNum(pos->getData().getNum() - 1);
        pos = pos->getNextNode();
    }
    contadorINS--;
}

void Receta::Instruccion::serialize(std::ofstream& archivo, const char& delim){
    if(archivo.fail()){
        throw std::runtime_error("Error al intentar abrir el archivo");
    }

    archivo << std::to_string(n_ins) << delim;
    archivo << predicado << delim;
}

void Receta::Instruccion::deserialize(const std::string& str, const char& delim){
    std::stringstream myStr(str);
    std::string insSTR;

    std::getline(myStr, insSTR, delim);
    this->n_ins = std::stoi(insSTR);

    std:getline(myStr, this->predicado, delim);
}