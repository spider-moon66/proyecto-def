#ifndef __LDLCCED_H__
#define __LDLCCED_H__

#include <functional>
#include <exception>
#include <string>

template<class T>
class LDLCCED{
    private:
        class Node{
            private:
                T* dataPtr;
                Node* next;
                Node* prev;
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
                Node();
                Node(T*);
                Node(const T&);
                ~Node();

                Node* getNextNode();
                Node* getPrevNode();
                T* getDataPtr() const;
                T& getData();

                
                void setNext(Node*);
                void setPrev(Node*);
                void setDataPtr(T*);
                void setData(const T&);

        };

        Node* header;

        void copyAll(const LDLCCED<T>&);
        bool isValidPos(Node*);

    public:

        class Exception : public Node::Exception{
            private:
                std::string msg;
            public:
                using Node::Exception::Exception;

                virtual ~Exception() noexcept = default;
        };

        LDLCCED();
        LDLCCED(const LDLCCED<T>&);
        ~LDLCCED();

        bool isEmpty() const;
        void ins(Node*, const T&);
        void insInicio(const T&);
        void insFinal(const T&);
        void insSorted(const T&);
        void insSorted(const T&, Node*);
        void del(Node*);

        Node* getFirst() const;
        Node* getLast() const;
        Node* getPrev(Node*) const;
        Node* getNext(Node*) const;

        T& retrieve(Node*);

        Node* findLineal(const T&) const;

        Node* findLineal(std::function<bool(const T&)>cmp) const;
        
        typedef Node* Position;

        std::string toString();

        void anular();
};

//Node
template<class T>
LDLCCED<T>::Node::Node() : dataPtr(nullptr), next(nullptr), prev(nullptr){}

template<class T>
LDLCCED<T>::Node::Node(T* e) : dataPtr(new T(e)), next(nullptr), prev(nullptr){
    if(dataPtr == nullptr)
    {
        throw Exception ("Memoria no disponible, crear nodo");
    }
}

template<class T>
LDLCCED<T>::Node::Node(const T& e) : dataPtr(new T(e)), next(nullptr), prev(nullptr){
    if(dataPtr == nullptr)
    {
        throw Exception ("Memoria no disponible, crear nodo");
    }
}

template<class T>
LDLCCED<T>::Node::~Node(){
    delete dataPtr;
}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::Node::getNextNode(){
    return next;
}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::Node::getPrevNode(){
    return prev;
}

template<class T>
T* LDLCCED<T>::Node::getDataPtr() const{
    return dataPtr;
}

template<class T>
T& LDLCCED<T>::Node::getData(){
    if(dataPtr == nullptr)
    {
        throw Exception("Posicion inexistente, obtener dato");
    }
    return *dataPtr;
}

template<class T>
void LDLCCED<T>::Node::setNext(Node* p){
    next = p;
}

template<class T>
void LDLCCED<T>::Node::setPrev(Node* p){
    prev = p;
}


template<class T>
void LDLCCED<T>::Node::setData(const T& e){
    //si el puntero a un dato T está vacio (nulo), se inicializa con una direccion a un elemento
    if(dataPtr == nullptr){
        if(dataPtr = new T(e) == nullptr)
        {
            throw Exception("Memoria no disponible, asignar dato");
        }
    }
    else
    {
        *dataPtr = e;
    }
}

//Lista

template<class T>
bool LDLCCED<T>::isEmpty() const{
    return header->getNextNode() == header && header->getPrevNode() == header;
}

template<class T>
void LDLCCED<T>::copyAll(const LDLCCED<T>& other){
    Node* aux(other.header->getNextNode());

    //de forma alternativa se podria utilizar other.getLast(), son operaciones equivalentes resultado de la estructura circular de la lista
    Node* last(header->getPrevNode());
    Node* nuevo;

    //los elementos se insertan tomando la posición previa como referencia, es decir, al ultimo
    while(aux != other.header){

        nuevo = new Node(aux->getData());

        if(nuevo == nullptr)
        {
            throw Exception("Memoria no disponible, copiar lista");
        }

        //el ultimo apunta al encabezado cuando la lista está vacia, por lo tanto el nuevo elemento queda "fijo" como el primer elemento
        if(last == header)
        {
            header->setNext(nuevo);
        }

        header->setPrev(nuevo);

        nuevo->setPrev(last);
        
        last->setNext(nuevo);

        nuevo->setNext(header);

        last = nuevo;

        aux = aux->getNextNode();

    }
    
}

template<class T>
bool LDLCCED<T>::isValidPos(Node* pos){

    Node* aux(header->getNextNode());

    while(aux != header){
        if(aux == pos){
            return true;
        }
        aux = aux->getNextNode();
    }

    return false;
}

template<class T>
LDLCCED<T>::LDLCCED() : header(new Node){
    if(header == nullptr){
        throw Exception("Memoria no disponible, crear lista");
    }
    header->setNext(header);
    header->setPrev(header);
}

template<class T>
LDLCCED<T>::LDLCCED(const LDLCCED<T>& other) : header(new Node){
    if(header == nullptr){
        throw Exception("Memoria no disponible, copiar lista");
    }

    header->setNext(header);
    header->setPrev(header);

    copyAll(other);
}

template<class T>
LDLCCED<T>::~LDLCCED(){
    anular();
    delete header;
}

//inserta despues de la posición de referencia
template<class T>
void LDLCCED<T>::ins(Node* pos, const T& e){
    if(!isValidPos(pos)){
        throw Exception("Posición invalida");
    }

    Node* nuevo;


    nuevo = new Node(e);

    if(nuevo == nullptr)
    {
        throw Exception("Memoria no disponible, insertar");
    }

    nuevo->setPrev(pos);

    pos->getNextNode()->setPrev(nuevo);
    
    nuevo->setNext(pos->getNextNode());

    pos->setNext(nuevo);

}

template<class T>
void LDLCCED<class T>::insSorted(const T& e){
    //si está vacia, no es necesario hacer la llamada recursiva
    if(isEmpty())
    {
        insInicio(e);
        return;
    }

    Node* aux(header->getNextNode());

    insSorted(e, aux);

}


//En el contexto del proyecto final, lo voy a utilizar de forma exclusiva para las instrucciones, puesto que no contemplo muchas y el costo por recorrer la lista es bajo
template<class T> 
void LDLCCED<class T>::insSorted(const T& e, Node* aux){

    //criterio de paro: si el elemento es menor que el primer elemento, entonces es menor que todos
    if(e < aux->getData()){
        insInicio(e);
        return;
    }

    //criterio de paro: si el siguiente nodo es header, significa que el elemento es mayor que todos los anteriores
    if(aux->getNextNode() == header){
        insFinal(e);
        return;
    }

    /*Si el elemento es mayor o igual que el elemento dentro del siguiente nodo, entonces el lugar de inserción es 
    despues del auxiliar (siguiendo la lógica de inserción que implementé)*/
    if(e <= aux->getNextNode()->getData()){
        ins(e, aux);
        return;
    }else{
        insSorted(e, aux->getNextNode());
    }
}


template<class T> 
void LDLCCED<T>::insFinal(const T& e){
    Node* nuevo;


    nuevo = new Node(e);

    if(nuevo == nullptr)
    {
        throw Exception("Memoria no disponible, insertar");
    }

    Node* last = header->getPrevNode();

    nuevo->setPrev(last);
    last->setNext(nuevo);
    header->setPrev(nuevo);
    nuevo->setNext(header);
}

template<class T> 
void LDLCCED<T>::insInicio(const T& e){
    Node* nuevo;


    nuevo = new Node(e);

    if(nuevo == nullptr)
    {
        throw Exception("Memoria no disponible, insertar");
    }

    Node* siguiente = header->getNextNode();

    nuevo->setNext(siguiente);
    nuevo->setPrev(header);
    siguiente->setPrev(nuevo);
    header->setNext(nuevo);

}

template<class T>
void LDLCCED<T>::del(Node* pos){

    if(!isValidPos(pos))
    {
        throw Exception("Posicion invalida, borrar");
    }
    pos->getNextNode()->setPrev(pos->getPrevNode());
    pos->getPrevNode()->setNext(pos->getNextNode());

    delete pos;
}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::getFirst() const{
    return header->getNextNode();
}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::getLast() const{
    return header->getPrevNode();
}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::getPrev(Node* pos) const{
    /*si la posición coincide con el primer elemento, entonces retornaria header, pero header es un encabezado 
    "centinela" por lo que en esta implementación no es una operación valida acceder al encabezado desde otra unidad de código*/
    if(!isValidPos(pos) || pos == header->getNextNode())
    {
        return nullptr;
    }
    return pos->getPrevNode();
}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::getNext(Node* pos) const {
    if(!isValidPos(pos) || pos == header->getPrevNode())
    {
        return nullptr;
    }
    return pos->getNextNode();
}
    

template<class T>
T& LDLCCED<T>::retrieve(Node* pos){
    if(!isValidPos(pos))
    {
        throw Exception("Posicion invalida, recuperar");
    }
    return pos->getData();
}

template<class T>
void LDLCCED<T>::anular(){

    Node* aux(header->getNextNode());

    while(aux != header){

        Node* siguiente(aux->getNextNode());

        delete aux;

        aux = siguiente;
    }

    header->setNext(header);
    header->setPrev(header);

}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::findLineal(const T& e) const{
    Node* aux = header->getNextNode();

    while(aux != header && aux->getData() != e){
        aux = aux->getNextNode();
    }

    return (aux == header) ? nullptr : aux;
}

template<class T>
typename LDLCCED<T>::Node* LDLCCED<T>::findLineal(std::function<bool(const T&)> cmp) const{
    Node* aux = header->getNextNode();

    while(aux != header && !cmp(aux->getData())){
        aux = aux->getNextNode();
    }

    return (aux == header) ? nullptr : aux;
}

template<class T>
std::string LDLCCED<T>::toString(){

    if(isEmpty()){
        return "";
    }
    
    Node* aux(header->getNextNode());
    std::string resultado("");

    while(aux != header){
        resultado += aux->getData().toString();
        aux = aux->getNextNode();
    }

    return resultado;
}


#endif // __LDLCCED_H__