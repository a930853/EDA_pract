/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
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

template<typename ident,typename val>
bool existeIndependiente(ident id,colecInterdep<ident,val> ci);

template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci, ident id, val v);

template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci, ident id, val v, ident idSup);

// FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)



// DECLARACION DEL TAD GENERICO colecInterdep

template<typename ident,typename val>
struct colecInterdep{

    friend void crear<ident,val>(colecInterdep<ident,val>& ci);
    friend unsigned tamanyo<ident,val>(colecInterdep<ident,val> ci);
    friend bool esVacia<ident,val>(colecInterdep<ident,val> ci);
    friend bool existe<ident,val>(ident id,colecInterdep<ident,val> ci);
    friend bool existeDependiente<ident,val>(ident id,colecInterdep<ident,val> ci);
    friend bool existeIndependiente<ident,val>(ident id,colecInterdep<ident,val> ci);
    friend void anyadirIndependiente<ident,val>(colecInterdep<ident,val> &ci, ident id, val v);
    friend void anyadirDependiente<ident,val>(colecInterdep<ident,val> &ci, ident id, val v, ident idSup);

    //Operaciones iterador
    
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
    typename colecInterdep<ident,val>::Nodo *nAux = ci.inicio;
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    return (nAux != nullptr && nAux->id == id);
}

template<typename ident,typename val>
bool existeDependiente(ident id,colecInterdep<ident,val> ci) {
    typename colecInterdep<ident,val>::Nodo *nAux = ci.inicio; //puntero para recorrer la colección
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    return (nAux != nullptr && nAux->id == id && nAux->NodoDep->id != nullptr );
}

template<typename ident,typename val>
bool existeIndependiente(ident id,colecInterdep<ident,val> ci) {
    typename colecInterdep<ident,val>::Nodo *nAux = ci.inicio; //puntero para recorrer la colección
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    return (nAux != nullptr && nAux->id == id && nAux->NodoDep->id == nullptr );
}

template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci, ident id, val v) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección y su anterior
        *nAux = ci.inicio, *nAnterior = ci.inicio;
    while (nAux != nullptr && nAux->id < id) {
        nAnterior = nAux;
        nAux = nAux->siguiente;
    }
    if (nAux == nullptr || nAux->id != id) {
        //Nodo añadido
        typename colecInterdep<ident,val>::Nodo 
            *nNew = new typename colecInterdep<ident,val>::Nodo;
        nNew->id = id;
        nNew->v = v;
        nNew->Numdepend = 0;
        nNew->NodoDep = nullptr;
        ci.numElementos++;
        if (nAux == nAnterior) {    //caso nNew al principio o colección vacia
            ci.inicio = nNew;
            nNew->siguiente = nAux;
        } else {    //caso nNew última posición o entre valores
            nAnterior->siguiente = nNew;
            nNew->siguiente = nAux;
        }
    }
}

template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci, ident id, val v, ident idSup) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección,su anterior u uno para buscar el supervisor
        *nAux = ci.inicio, *nAnterior = ci.inicio, *nAuxSup = ci.inicio;
    while (nAuxSup != nullptr &&  nAuxSup->id < idSup) {
        nAuxSup = nAuxSup->siguiente;
    }
    if (nAuxSup == nullptr || nAuxSup->id != idSup) {return;}
    while (nAux != nullptr && nAux->id < id) {
        nAnterior = nAux;
        nAux = nAux->siguiente;
    }
    if (nAux == nullptr || nAux->id != id) {
        //Nodo añadido
        typename colecInterdep<ident,val>::Nodo 
            *nNew = new typename colecInterdep<ident,val>::Nodo;
        nNew->id = id;
        nNew->v = v;
        nNew->Numdepend = 0;
        nNew->NodoDep = nAuxSup;
        nAuxSup->NumDepend++;
        ci.numElementos++;
        if (nAux == nAnterior) {    //caso nNew al principio o colección vacia
            ci.inicio = nNew;
            nNew->siguiente = nAux;
        } else {    //caso nNew última posición o entre valores
            nAnterior->siguiente = nNew;
            nNew->siguiente = nAux;
        }
    }
}

#endif //fin de colecInterdep.hpp
