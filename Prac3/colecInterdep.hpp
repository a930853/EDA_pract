/* Javier Martínez Virto 930853
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP

// PREDECLARACION DEL TAD GENERICO colecInterdep (inicio INTERFAZ)

template<typename ident,typename val> struct colecInterdep;


/* COMPLETAR LA DOCUMENTACION PUBLICA DE CADA OPERACION DEL TAD
*/
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci);

template<typename ident,typename val>
unsigned tamanyo(colecInterdep<ident,val> ci);

template<typename ident,typename val>
bool esVacia(colecInterdep<ident,val> ci);

template<typename ident,typename val>
bool existe(ident id,colecInterdep<ident,val> ci);

template<typename ident,typename val>
bool existeDependiente(ident id,colecInterdep<ident,val> ci);

// FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)



// DECLARACION DEL TAD GENERICO colecInterdep

template<typename ident,typename val>
struct colecInterdep{

    friend void crear<ident,val>(colecInterdep<ident,val>& ci);
    friend unsigned tamanyo<ident,val>(colecInterdep<ident,val> ci);
    friend bool esVacia<ident,val>(colecInterdep<ident,val> ci);
    friend bool existe<ident,val>(ident id,colecInterdep<ident,val> ci);
    friend bool existeDependiente<ident,val>(ident id,colecInterdep<ident,val> ci);

  private: //declaracion de la representacion interna del tipo
    struct Nodo {
        ident id;           // Identificador (clave de ordenación)
        val v;              // Valor asociado
        unsigned NumDepend;  // Contador de dependientes directos
        Nodo* siguiente;    // Puntero al siguiente nodo en la lista (ordenada por 'id')
        Nodo* NodoDep;   // Puntero al nodo al cual es dependiente (es NULL si es independiente)
    };

    /**
     * Puntero al inicio de la lista enlazada.
     * Apunta al primer 'Nodo' de la colección, que es el
     * elemento con el 'id' menor según la relación de orden.
     * Si la colección está vacía, 'inicio' es NULL.
     */
    Nodo* inicio;

    /**
     * Contador del número total de elementos.
     * Almacena el número de nodos en la colección para que
     * la operación 'tamaño' sea de coste O(1).
     */
    unsigned numElementos;

    /**
     * Puntero de estado del iterador.
     * Apunta al *siguiente* nodo que debe ser visitado/leído.
     * - 'iniciarIterador' lo coloca en 'inicio'.
     * - 'avanza' lo mueve a 'iterador->siguiente'.
     * - Si es NULL, 'existeSiguiente' devuelve falso.
     */
    Nodo* iterador;
};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colc

 //...documentar ...
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci) {
    ci.inicio = nullptr;
    ci.numElementos = 0;
    ci.iterador = nullptr;
}

template<typename ident,typename val>
unsigned tamanyo(colecInterdep<ident,val> ci) {
    return ci.numElementos;
}

template<typename ident,typename val>
bool esVacia(colecInterdep<ident,val> ci) {
    return ci.inicio == nullptr && ci.numElementos = 0;
}

template<typename ident,typename val>
bool existe(ident id,colecInterdep<ident,val> ci) {
    Nodo *nAux = ci.inicio;
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    return (nAux != nullptr && nAux->id == id);
}

template<typename ident,typename val>
bool existeDependiente(ident id,colecInterdep<ident,val> ci) {
    Nodo *nAux = ci.inicio;
    while (nAux != nullptr && nAux->NodoDep->id != id) {
        nAux = nAux->siguiente;
    }
    return (nAux != nullptr && nAux->NodoDep->id == id);
}

#endif //fin de colecInterdep.hpp
