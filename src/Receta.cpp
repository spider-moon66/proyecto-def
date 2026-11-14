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

void Receta::serializar(std::ofstream& archivo, const char& delim)
{

    if(archivo.fail()){
       throw std::runtime_error("No se pudo abrir el archivo");
    }

    archivo << nombreReceta << delim;
    
    archivo << descripcion << delim;

    Lista<Ingrediente>::Position pos(ingredientesData.getFirst());

    ingredientesData.serialize(archivo, '#');

    for(int i = 0; i <= instrucciones.getLastPos(); i++){
        archivo << instrucciones.retrieve(i) << '#';
    }
    
    archivo << delim;

}

void Receta::deserializar(const std::string& str, const char& delim)
{
    std::stringstream myStr(str);

    /*Aqui lo que estoy haciendo es un tanto rudimentario, mi solución es fragil a modificaciones externas.
    En las iteraciones paso la cadena completa, sin tokenizar, que se obtiene en cada iteración como parametro al metodo para deserializar 
    de un objeto temporal de tipo ingrediente/instrucción, deserializar ya modifica o le da valores al objeto que le llamó porque estoy utilizando el operador ->
    por lo tanto solo hace falta que pase como parametro ese objeto al metodo agregar de la lista y ya estaria reconstruyendo los ingredientes de la lista*/

    std::string ingredientesStr;
    std::string instruccionesStr;
    std::string cantidadIng;
    std::string cantidadInsStr;
    int cantIng;
    int cantIns;

    Ingrediente ingredienteDeSerial;

    getline(myStr, this->nombreReceta, delim);
    getline(myStr, this->descripcion, delim);
    //Toma la ultima posición de la lista a reconstruir
    getline(myStr, cantidadIng, delim);
    cantIng = std::stoi(cantidadIng);
    int i = 0;
    while(i < cantIng){

        std::getline(myStr, ingredientesStr, ';');

        ingredienteDeSerial.deserializar(ingredientesStr, '|');
        this->ingredientesData.agregar(ingredienteDeSerial);
        i++;
    }
    
    std::getline(myStr, cantidadInsStr, delim);
    cantIns = std::stoi(cantidadInsStr);

    i = 0;
    while(i < cantIns){
        std::getline(myStr, instruccionesStr, '#');
        this->instrucciones.agregar(instruccionesStr);
        i++;
    }

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

short int Receta::Instruccion::getNum(){
    return n_ins;
}

std::string Receta::Instruccion::getPredicado(){
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