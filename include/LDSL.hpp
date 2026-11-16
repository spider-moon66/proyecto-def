#ifndef __LDSL_H__
#define __LDSL_H__

#include <string>
#include <sstream>
#include <fstream>
#include <functional>
#include <exception>

template <class T>
class Lista{
    private:
        class Node{ 
            private:
                T data;
                Node *next;
            public:
                Node();
                Node(const T&);

                T& getData();
                const T& getData() const;
                Node *getNext() const;

                void setData(const T&);
                void setNext(Node*);
        };
        
        Node *anchor;
        void copyAll(const Lista<T>&);
        bool isValidPos(Node*) const;

    public:
        class Exception : public std::exception{
            private:
                std::string msg;
            public:
                explicit Exception(const char* message) : msg(message){}
                explicit Exception(const std::string& message) : msg(message) {}

                virtual ~Exception() throw () {}

                virtual const char* what() const throw (){
                    return msg.c_str();
                }
        };

        Lista();
        Lista(const Lista<T>&);
        ~Lista();

        bool isEmpty() const;
        void ins(Node*, const T&);
        void del(Node*);

        Node* getFirst() const;
        Node* getLast() const;
        Node* getPrev(Node*) const;
        Node* getNext(Node*) const;

        T& retrieve(Node*);

        Node* findLineal(const T&) const;

        Node* findLineal(std::function<bool(const T&)>cmp) const;
        
        std::string toString();

        typedef Node* Position;

        void anular();

        void serialize(std::ofstream&, const char& = '|');
        void deserialize(std::stringstream& str, const char& = '|');
};

//Implementación de Node
template <class T>
Lista<T>::Node::Node() : next(nullptr) {

}

template <class T>
Lista<T>::Node::Node(const T& other) : data(other), next(nullptr) {

}

template <class T>
T& Lista<T>::Node::getData(){
    return data;
}

template <class T>
const T& Lista<T>::Node::getData() const{
    return data;
}

//Retorna un apuntador a un nodo que pertenece a la clase de lista de datos tipo T
template <class T>
typename Lista<T>::Node* Lista<T>::Node::getNext() const{
    return next;
}

template <class T>
void Lista<T>::Node::setData(const T& n){
    data = n;
}

template <class T>
void Lista<T>::Node::setNext(typename Lista<T>::Node *x){
    next = x;
}

//Implementación de la lista

template<class T>
void Lista<T>::copyAll(const Lista<T>& l)
{
    Node* aux(l.anchor);
    Node* last(nullptr);
    Node* nuevo;

    while(aux != nullptr){
        nuevo = new Node(aux->getData());

        if(last == nullptr){
            anchor = nuevo;
        }else{
            last->setNext(nuevo);
        }

        last = nuevo;

        aux = aux->getNext();
    }
}

template<class T>
Lista<T>::Lista() : anchor(nullptr)
{
    
}

template<class T>
Lista<T>::Lista(const Lista<T>& l) : anchor(nullptr)
{
    copyAll(l);
}

template<class T>
Lista<T>::~Lista()
{
    anular();
}

template<class T>
bool Lista<T>::isValidPos(Node* pos) const
{
    Node* aux(anchor);

    while(aux != nullptr){
        if(aux == pos){
            return true;
        }
        aux = aux->getNext();
    }

    return false;
}

template<class T>
bool Lista<T>::isEmpty() const
{
    return anchor == nullptr;
}

template<class T>
void Lista<T>::ins(Node* pos, const T& nuevo)
{
    if(pos != nullptr && !isValidPos(pos)){
        throw Exception("Posición invalida, ins");
    }

    Node* aux(new Node(nuevo));
    if(aux == nullptr){
        throw Exception("Error al asignar memoria, ins");
    }

    if(pos == nullptr){
        aux->setNext(anchor);
        anchor = aux;
    }else{
        aux->setNext(pos->getNext());
        pos->setNext(aux);
    }
}

template<class T>
void Lista<T>::del(Node* pos)
{
    if(pos != nullptr && !isValidPos(pos)){
        throw Exception("Posición invalida, del");
    }

    if(pos == anchor){
        anchor = anchor->getNext();
    }else{
        getPrev(pos)->setNext(pos->getNext());
    }

    delete pos;
}

template<class T>
typename Lista<T>::Node* Lista<T>::getFirst() const
{
    return anchor;
}

template<class T>
typename Lista<T>::Node* Lista<T>::getLast() const
{
    if(isEmpty()){
        return nullptr;
    }

    Node* aux(anchor);

    while(aux->getNext() != nullptr){
        aux = aux->getNext();
    }

    return aux;
}

template<class T>
typename Lista<T>::Node* Lista<T>::getPrev(Node* pos) const
{
    if(pos == anchor){
        return nullptr;
    }

    Node* aux(anchor);

    while(aux != nullptr && aux->getNext() != pos){
        aux = aux->getNext();
    }

    return aux;
}

template<class T>
typename Lista<T>::Node* Lista<T>::getNext(Node* pos) const
{
    if(pos != nullptr && !isValidPos(pos)){
        throw Exception("Posición invalida, del");
    }

    return pos->getNext();
}

template<class T>
T& Lista<T>::retrieve(Node* pos)
{
    if(!isValidPos(pos)){
        throw Exception("Posicion invalida, retrieve");
    }

    return pos->getData();
}

template<class T>
typename Lista<T>::Node* Lista<T>::findLineal(const T& item) const
{
    Node* aux(anchor);

    while(aux != nullptr && aux->getData() != item){
        aux = aux->getNext();
    }

    return aux;
}


template<class T>
void Lista<T>::anular()
{
    Node* aux;

    while(anchor != nullptr){
        aux = anchor;

        anchor = anchor->getNext();

        delete aux;
    }
}

template<class T>
typename Lista<T>::Node*
Lista<T>::findLineal(std::function<bool(const T&)> cmp) const
{
    Node* aux = anchor;

    while(aux != nullptr && !cmp(aux->getData())){
        aux = aux->getNext();
    }

    return aux;
}

//contempla que el dato dentro del nodo tiene un metodo toString()
template<class T>
std::string Lista<T>::toString(){

    if(anchor == nullptr){
        return "";
    }

    Node* aux(anchor);

    std::string resultado("");

    while(aux != nullptr){
        resultado += aux->getData().toString();
        aux = aux->getNext();
    }

    return resultado;

}

template<class T>
void Lista<T>::serialize(std::ofstream& archivo, const char& delim){

    if(archivo.fail()){
        throw Exception ("No se pudo abrir el archivo");
    }

    Node* aux(anchor);

    /*Me ayuda a que el algoritmo tenga un criterio más fuerte que el delimitador, 
    declarando explicitamente cuántos elementos tiene que reconstruir*/
    int i = 0;

    while(aux != nullptr){
        i++;
        aux = aux->getNext();
    }

    archivo << std::to_string(i) << delim;

    aux = anchor;

    while(aux != nullptr){
        aux->getData().serialize(archivo, delim);
        aux = aux->getNext();
    }

}

template<class T>
void Lista<T>::deserialize(std::stringstream& str, const char& delim){
    
    std::string cantSTR;
    int cantINT;

    std::getline(str, cantSTR, delim);

    cantINT = std::stoi(cantSTR);

    Node* ultimo(getLast());
    for(int i = 0; i < cantINT; i++){
        T nuevo;
        nuevo.deserialize(str, delim);
        ins(ultimo, nuevo);
        ultimo = (ultimo == nullptr) ? anchor : ultimo->getNext();
    }

}

#endif // __LDSL_H__