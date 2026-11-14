#ifndef __Lista_estatica_H__
#define __Lista_estatica_H__

#include <stdexcept>
#include <functional>
#include <sstream>
#include <fstream>
#include <string>

template <class T, int ARRAYSIZE>
class Lista_estatica{
    private:
        T data[ARRAYSIZE];
        int last = -1;
        bool isValidPos(int&);
    public:
        Lista_estatica();
        Lista_estatica(const Lista_estatica<T, ARRAYSIZE>&);
        void copyAll(const Lista_estatica<T, ARRAYSIZE>&);
        bool isEmpty();
        bool isFull();
        void agregar(T&);
        bool ins(int&, T&);
        bool del(int&);
        T getFirst() const;
        T getLast();
        int getLastPos() const;
        T getPrev(int&);
        T getNext(int&);
        bool isSorted();
        //Recibe una funcion de retorno booleano cuyos parametros son constantes de tipo T
        int findLineal(std::function<bool(const T&)>);
        int findBinaria(std::function<int(const T&)>);

        //Metodos de ordenamiento
        //Implicito
        void Burbuja();
        void InsSort();
        void SelectSort();
        void ShellSort();
        void MergeSort();
        void MergeSortRecursive(T[], int extL, int extR);
        void MergeSorted(T[], int extL, int m, int extR);
        void swap(T*, T*);
        void QuickSort();
        void QuickSortRecursive(T[], int, int);
        int QuickSortPartition(T[], int, int);
        //Explicito
        void Burbuja(std::function<bool(const T&, const T&)>cmp);
        void InsSort(std::function<bool(const T&, const T&)>cmp);
        void SelectSort(std::function<bool(const T&, const T&)>cmp);
        void ShellSort(std::function<bool(const T&, const T&)>cmp);
        T& retrieve(int&);
        void anular();
        //Serializar/Deserializar
        void serializar(std::ofstream&, const char& delim = '@');
        void deserializar(const std::string&, const char& delim = '@');
};

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::copyAll(const Lista_estatica<T, ARRAYSIZE>& otra){
    for(int i = 0; i <= otra.last; i++){
        this->data[i] = otra.data[i];
    }
    this->last = otra.last;
}

template<class T, int ARRAYSIZE>
Lista_estatica<T, ARRAYSIZE>::Lista_estatica(const Lista_estatica<T, ARRAYSIZE>& otra) : last(-1){
    this->copyAll(otra);
}

template<class T, int ARRAYSIZE>
Lista_estatica<T, ARRAYSIZE>::Lista_estatica()
{
    last = -1;
}

template<class T, int ARRAYSIZE>
bool Lista_estatica<T, ARRAYSIZE>::isValidPos(int& pos)
{
    if(pos >= 0 && pos <= last){
        return true;
    }
    return false;
}

template<class T, int ARRAYSIZE>
bool Lista_estatica<T, ARRAYSIZE>::isEmpty()
{
    if(last == -1){return true;}
    return false;
}

template<class T, int ARRAYSIZE>
bool Lista_estatica<T, ARRAYSIZE>::isFull()
{
    if(last == ARRAYSIZE -1){return true;}
    return false;
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::agregar(T& nueva)
{
    if(!isFull()){
        last++;
        data[last] = nueva;
    }
}

template<class T, int ARRAYSIZE>
bool Lista_estatica<T, ARRAYSIZE>::ins(int& pos, T& nueva)
{
    if(pos >= 0 && pos <= last + 1){
        if(!isFull()){
            for(int i = last; i >= pos; i--){
                data[i + 1] = data[i];
            }
            data[pos] = nueva;
            last++;
            return true;
        }
        return false;
    }
    return false;
}

template<class T, int ARRAYSIZE>
bool Lista_estatica<T, ARRAYSIZE>::del(int& pos)
{
    if(isValidPos(pos) == true){
        for(int i = pos; i < last; i++){
            data[i] = data[i + 1];
            }
            last--;
            return true;
        }
    return false;
}

template<class T, int ARRAYSIZE>
T Lista_estatica<T, ARRAYSIZE>::getFirst() const
{
    if(!isEmpty()){return data[0];}
}

template<class T, int ARRAYSIZE>
T Lista_estatica<T, ARRAYSIZE>::getLast()
{
    if(!isEmpty()){return data[last];}
}

template<class T, int ARRAYSIZE>
int Lista_estatica<T, ARRAYSIZE>::getLastPos() const
{
    return last;
}

template<class T, int ARRAYSIZE>
T Lista_estatica<T, ARRAYSIZE>::getPrev(int& pos)
{
    if(!(isEmpty()) && pos > 0){
        if(isValidPos(pos)){
            return data[pos - 1];
        }
    }
}

template<class T, int ARRAYSIZE>
T Lista_estatica<T, ARRAYSIZE>::getNext(int& pos)
{
    if((!isEmpty()) && (pos < last)){
        if(isValidPos(pos)){
            return data[pos + 1];
        }
    }
}

template<class T, int ARRAYSIZE>
int Lista_estatica<T, ARRAYSIZE>::findLineal(std::function<bool(const T&)> cmp)
{
    if(!isEmpty()){
        int pos = 0;
        do{
            if(cmp(data[pos])){
                return pos;
            }
            pos++;
        }while(pos <= last);
        return -1;
    }
}
template<class T, int ARRAYSIZE>
int Lista_estatica<T, ARRAYSIZE>::findBinaria(std::function<int(const T&)> cmp){
    int i = 0, j = last;
    do{
    int medio = (i + j)/2;
    //Al guardar el resultado solo se llama a lambda una vez por iteración
    int resultado = cmp(data[medio]);
    if(resultado == 0){return medio;}
    if(resultado == -1){j = medio - 1;}
    if(resultado == 1){i = medio + 1;}
    }while(i <= j);
    return -1;
}



template<class T, int ARRAYSIZE>
T& Lista_estatica<T, ARRAYSIZE>::retrieve(int& pos)
{
    if(isValidPos(pos)){
        return data[pos];
    }
    throw std::out_of_range("Posicion invalida");
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::anular()
{
    last = -1;
}

//Metodos de busqueda

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::Burbuja(){
    int i = last;
    int j;
    bool band = true;

    while(i > 0){
        band = false;
        j = 0;
        while(j < i){
            if(data[j] > data[j + 1]){
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                band = true;
            }
            j++;
        }
        if(band == false){
            break;
        }
        i--;
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::Burbuja(std::function<bool(const T&, const T&)>cmp){
    int i = last;
    int j;
    bool band = true;

    while(i > 0){
        band = false;
        j = 0;
        while(j < i){
            if(cmp(data[j], data[j + 1])){
                T temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                band = true;
            }
            j++;
        }
        if(band == false){
            break;
        }
        i--;
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::InsSort(){
    int i = 1;
    int j;
    while(i <= last){
        T temp = data[i];
        j = i;
        while(j > 0 && temp < data[j - 1]){
            data[j] = data[j - 1];
            j--;
        }
        if(i != j){
            data[j] = temp;
        }
        i++;
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::InsSort(std::function<bool(const T&, const T&)>cmp){
    int i = 1;
    int j;
    while(i <= last){
        T temp = data[i];
        j = i;
        while(j > 0 && cmp(temp, data[j- 1])){
            data[j] = data[j - 1];
            j--;
        }
        if(i != j){
            data[j] = temp;
        }
        i++;
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::SelectSort(){
    int menor;
    int i = 0;
    
    while(i < last){
        menor = i;
        int j = i + 1;
        while(j <= last){
            if(data[j] < data[menor]){
                menor = j;
            }
            j++;
        }
        if(menor != i){
            T temp = data[i];
            data[i] = data[menor];
            data[menor] = temp; 
        }
        i++;
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::SelectSort(std::function<bool(const T&, const T&)>cmp){
    int menor;
    int i = 0;
    
    while(i < last){
        menor = i;
        int j = i + 1;
        while(j <= last){
            if(cmp(data[j], data[menor])){
                menor = j;
            }
            j++;
        }
        if(menor != i){
            T temp = data[i];
            data[i] = data[menor];
            data[menor] = temp; 
        }
        i++;
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::ShellSort(){
    int dif = (last + 1)/2;
    while(dif > 0){
        int i = dif;
        while(i <= last){
            int j = i;
            while(j >= dif && data[j - dif] > data[j]){
                T temp = data[j - dif];
                data[j - dif] = data[j];
                data[j] = temp;
                j = j - dif;
            }
            i++;
        }
        dif = dif/2;
    }

}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::ShellSort(std::function<bool(const T&, const T&)>cmp){
    int dif = (last + 1)/2;
    while(dif > 0){
        int i = dif;
        while(i <= last){
            int j = i;
            while(j >= dif && cmp(data[j - dif], data[j])){
                T temp = data[j - dif];
                data[j - dif] = data[j];
                data[j] = temp;
                j = j - dif;
            }
            i++;
        }
        dif = dif/2;
    }

}

//Recursivos

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::MergeSort(){
    if(!isEmpty()){
        //lo mismo que (Arreglo, Extremo izquierdo, Extremo derecho)
        MergeSortRecursive(data, 0, last);
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::MergeSortRecursive(T data[], int extL, int extR){
    //criterio de paro
    if(extL < extR){
        //En la primer llamada de recursion no tiene mucho caso sumar la posición del extremo izquierdo
        //Sin embargo, en llamadas posteriores la posición que representa 
        //el primer indice de una de las porciones del arreglo, no siempre va a ser 0
        int m = extL + (extR - extL) / 2;

        //Porcion del arreglo izquierdo
        MergeSortRecursive(data, extL, m);
        //Porcion del arreglo derecho
        MergeSortRecursive(data, m + 1, extR);

        //Una vez se resuelven las llamadas recursivas, solo queda juntar o mezclar las dos porciones en un solo arreglo
        MergeSorted(data, extL, m, extR);
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::MergeSorted(T data[], int extL, int m ,int extR){
    int l_lenght = m - extL + 1;
    int r_lenght = extR - m;

    T temp_left[l_lenght];
    T temp_right[r_lenght];

    int i, j, x;

    //Copio las porciones del arreglo original en los arreglos temporales que representan dichas porciones
    for(int i = 0; i < l_lenght; i++){
        //La porcion que se está copiando no siempre comienza en el indice cero
        temp_left[i] = data[extL + i];
    }
    for(int i = 0; i < r_lenght; i++){
        temp_right[i] = data[m + 1 + i];
    }
    /*X comienza en la primer posición de la porción izquierda y en cada iteración se incrementa, 
    x tambien representa la posición del elemento en el arreglo original*/
    for(i = 0, j = 0, x = extL; x <= extR; x++){
        if(i >= l_lenght){
            data[x] = temp_right[j];
            j++;
        }else if(j >= r_lenght){
            data[x] = temp_left[i];
            i++;
        }else if(temp_left[i] <= temp_right[j]){
            data[x] = temp_left[i];
            i++;
        }else{
            data[x] = temp_right[j];
            j++;
        }
    }
    /*De forma coloquial, lo que hace la iteración es buscar cuál de los dos arreglos tiene el elemento 
    más pequeño y despues copia ese elemento en la posición x que corresponde dentro del arreglo original*/
}

//Serializar/Deserializar

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::serializar(std::ofstream& archivo, const char& delim){
    //Guardo el numero de elementos que tiene la Lista_estatica
    archivo << this->last + 1 << delim;
    for(int i = 0; i <= this->last; i++){
        this->data[i].serializar(archivo);
        archivo << delim;
    }
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::deserializar(const std::string& str, const char& delim){
    int Tcant;
    std::stringstream myStr(str);
     std::string cant;
    //Recupero los elementos que tiene la Lista_estatica a reconstruir
    std::getline(myStr, cant, delim);
    Tcant = std::stoi(cant);
    //El archivo es fragil a modificaciones exteriores, si hay una mala lectura y la cantidad de elementos 
    //termina siendo menor a 0 o mayor a ARRAYSIZE terminaria accediento a indices invalidos, habria un error de overflow
    if(Tcant > ARRAYSIZE || Tcant < 0){
        throw std::runtime_error("La cantidad de elemenos es invalida");
    }

    for(int i = 0; i < Tcant; i++){
        std::string Lista_estaticaSTR;
        std::getline(myStr, Lista_estaticaSTR, delim);
        this->data[i].deserializar(Lista_estaticaSTR);
    }
    /*Por eso de que los indices comienzan desde 0, 
    pero cuando la Lista_estatica se inicializa last = -1, por tanto para representar la cantidad de elemenos o 
    indices que se tienen que recorrer tengo que sumar 1 a last*/
    this->last = Tcant - 1;
}

//Swap pero con punteros
template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::swap(T *a, T *b){
    T temp = *a;
    *a = *b;
    *b = temp;
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::QuickSort(){
    QuickSortRecursive(data, 0, last);
}

template<class T, int ARRAYSIZE>
void Lista_estatica<T, ARRAYSIZE>::QuickSortRecursive(T data[], int low, int high){
    //Criterio de paro (low > high)
    if(low < high){
        //Particion retorna la posición del pivote (el ultimo elemento de la porcion de arreglo que se está tomando)
        T piv_indx = QuickSortPartition(data, low, high);
        //Porcion izquierda del arreglo
        QuickSortRecursive(data, low, piv_indx - 1);
        //Porcion derecha del arreglo
        QuickSortRecursive(data, piv_indx + 1, high);
    }
}

template<class T, int ARRAYSIZE>
int Lista_estatica<T, ARRAYSIZE>::QuickSortPartition(T[], int low, int high){
    //En está implementación, asumimos que el pivote siempre va a ser la ultima posición de la porción de arreglo
    T piv_value = data[high];

    int i = low;
    //Tanto i como j comienzan en el extremo izquierdo del arreglo, j se incrementa en cada iteración
    //i se incrementa solo si hay un cambio de posiciones
    for(int j = low; j < high; j++){
        //el cambio de posiciones se da cuando el elemento en la posicion j es menor o igual que el pivote
        if(data[j] <= piv_value){
            swap(&data[i], &data[j]);
            i++;
        }
    }
    //Al finalizar la iteración se intercambia la posición de i con el pivote
    swap(&data[i], &data[high]);

    return i;
}

template<class T, int ARRAYSIZE>
bool Lista_estatica<T, ARRAYSIZE>::isSorted(){
    for(int i = 0; i < last; i++){
        if(data[i] > data[i + 1]){return false;}
    }
    return true;
}

#endif // __Lista_estatica_H__