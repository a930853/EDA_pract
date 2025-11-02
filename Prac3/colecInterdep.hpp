/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP

// PREDECLARACION DEL TAD GENERICO colecInterdep (inicio INTERFAZ)

template<typename ident,typename val> struct colecInterdep;


/**
 * crear: -> colecInterdep
 * {Crea una colección vacía, sin elementos.}
 */
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci);

/**
 * tamaño: colecInterdep c -> natural
 * {Devuelve el número de elementos que hay en la colección c.}
 */
template<typename ident,typename val>
unsigned tamanyo(colecInterdep<ident,val> ci);

/**
 * esVacía?: colecInterdep c -> booleano
 * {Devuelve verdad si y solo si c no contiene ningún elemento.}
 */
template<typename ident,typename val>
bool esVacia(colecInterdep<ident,val> ci);

/**
 * existe?: ident id, colecInterdep c -> booleano
 * {Devuelve verdad si y solo si en c hay algún elemento con ident igual a id.}
 */
template<typename ident,typename val>
bool existe(ident id,colecInterdep<ident,val> ci);

/**
 * existeDependiente?: ident id, colecInterdep c -> booleano
 * {Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id, es
 * decir un elemento (id, v, idSup, NumDep).}
 */
template<typename ident,typename val>
bool existeDependiente(ident id,colecInterdep<ident,val> ci);

/**
 * existeIndependiente?: ident id, colecInterdep c -> booleano
 * {Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id, es
 * decir un elemento (id, v, -, NumDep).}
 */
template<typename ident,typename val>
bool existeIndependiente(ident id,colecInterdep<ident,val> ci);

/**
 * añadirIndependiente: colecInterdep c, ident id, val v -> colecInterdep
 * {Si no existe?(id,c), devuelve una colección igual a la resultante de añadir el elemento
 * independiente (id,v,-,0) a la colección c. En caso contrario, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci, ident id, val v);

/**
 * añadirDependiente: colecInterdep c, ident id, val v, ident super -> colecInterdep
 * {Si no existe?(id,c) y existe?(super,c) devuelve una colección igual a la resultante de:
 * incrementar en 1 el número de elementos dependientes del elemento con identificador super en c, y
 * de añadir el elemento (id,v,super,0) a la colección c.
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci, ident id, val v, ident idSup);

/**
 * hacerDependiente: colecInterdep c, ident id, ident super -> colecInterdep
 * {Si no igual(id,super) y existe?(super,c) y existeDependiente?(id,c), ...
 * Si no igual(id,super) y existe?(super,c) y existeIndependiente?(id,c), ...
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci, ident id, ident idSup);

/**
 * hacerIndependiente: colecInterdep c, ident id -> colecInterdep
 * {Si existeDependiente?(id,c), ...
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci, ident id);

/**
 * parcial actualizarVal: colecInterdep c, ident id, val nuevo -> colecInterdep
 * {Si existeIndependiente?(id,c), ... Si existeDependiente?(id,c), ...
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
void actualizarVal(colecInterdep<ident,val> &ci, ident id, val v, bool &error);

/**
 * parcial obtenerVal: ident id, colecInterdep c -> val
 * {Si en c hay algún elemento con ident igual a id, ... devuelve el dato v ...
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
void obtenerVal(ident id, colecInterdep<ident,val> ci, val &v, bool &error);

/**
 * parcial obtenerSupervisor: ident id, colecInterdep c -> ident
 * {Si existeDependiente?(id,c), ... devuelve el dato sup ...
 * Parcial: la operación no está definida si no existeDependiente?(id,c).}
 */
template<typename ident,typename val>
void obtenerSupervisor(ident id, colecInterdep<ident,val> ci, ident &idSup, bool &error);

/**
 * parcial obtenerNúmDependientes: ident id, colecInterdep c -> natural
 * {Si existe?(id,c), ... devuelve el dato NumDep ...
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
void obtenerNumDependientes(ident id, colecInterdep<ident,val> ci, unsigned &NumDep, bool &error);

/**
 * borrar: ident id, colecInterdep c -> colecInterdep
 * {Si existeDependiente?(id,c), ... y obtenerNúmDependientes(id,c)=0,
 * devuelve una colección igual a la resultante de: decrementar en 1 el número de elementos
 * dependientes del elemento con identificador sup, y eliminar el elemento ...
 * Si existeIndependiente?(id,c), ... y obtenerNúmDependientes(id,c)=0,
 * devuelve una colección igual a la resultante de eliminar el elemento ...
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void borrar(ident id, colecInterdep<ident,val> &ci);

/*OPERACIONES ITERADOR*/

/**
 * iniciarIterador: colecInterdep c -> colecInterdep
 * {Inicializa el iterador para recorrer los elementos de la colección c...}
 */
template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci);

/**
 * existeSiguiente?: colecInterdep c -> booleano
 * {Devuelve verdad si queda algún elemento por visitar con el iterador...}
 */
template<typename ident,typename val>
bool existeSiguiente(colecInterdep<ident,val> ci);

/**
 * parcial siguienteIdent: colecInterdep c -> ident
 * {Devuelve el ident del siguiente elemento a visitar ...
 * Parcial: la operación no está definida si no quedan elementos por visitar...}
 */
template<typename ident,typename val>
void siguienteIdent(colecInterdep<ident,val> ci, ident &id, bool &error);

/**
 * parcial siguienteVal: colecInterdep c -> val
 * {Devuelve el val del siguiente elemento a visitar ...
 * Parcial: la operación no está definida si no quedan elementos por visitar...}
 */
template<typename ident,typename val>
void siguienteVal(colecInterdep<ident,val> ci, val &v, bool &error);

/**
 * parcial siguienteDependiente?: colecInterdep c -> booleano
 * {Si el siguiente elemento a visitar ... es de la forma (ident, val, -, numDep) devuelve falso,
 * pero si es de la forma (ident, val, identSup, numDep) devuelve verdad.
 * Parcial: la operación no está definida si no quedan elementos por visitar...}
 */
template<typename ident,typename val>
void siguienteDependiente(colecInterdep<ident,val> ci, bool &esDep, bool &error);

/**
 * parcial siguienteSuperior: colecInterdep c -> ident
 * {Si el siguiente elemento a visitar ... es de la forma (ident, val, identSup, numDep), devuelve su identSup.
 * Parcial: la operación no está definida si no quedan elementos por visitar ...,
 * o bien si ... no es verdad siguienteDependiente?(c).}
 */
template<typename ident,typename val>
void siguienteSuperior(colecInterdep<ident,val> ci, ident &idSup, bool &error);

/**
 * parcial siguienteNúmDependientes: colecInterdep c -> natural
 * {Devuelve el NumDep del siguiente elemento a visitar ...
 * Parcial: la operación no está definida si no quedan elementos por visitar...}
 */
template<typename ident,typename val>
void siguienteNumDependientes(colecInterdep<ident,val> ci, unsigned &NumDep, bool &error);

/**
 * parcial avanza: colecInterdep c -> colecInterdep
 * {Avanza el iterador de la colección c para que se pueda visitar otro elemento.
 * Parcial: la operación no está definida si no quedan elementos por visitar...}
 */
template<typename ident,typename val>
void avanza(colecInterdep<ident,val>& ci, bool &error);

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
    friend void hacerDependiente<ident,val>(colecInterdep<ident,val> &ci, ident id, ident idSup);
    friend void hacerIndependiente<ident,val>(colecInterdep<ident,val> &ci, ident id);
    friend void actualizarVal<ident,val>(colecInterdep<ident,val> &ci, ident id, val v, bool &error);
    friend void obtenerVal<ident,val>(ident id,colecInterdep<ident,val> ci, val &v, bool &error);
    friend void obtenerSupervisor<ident,val>(ident id, colecInterdep<ident,val> ci, ident &idSup, bool &error);
    friend void obtenerNumDependientes<ident,val>(ident id, colecInterdep<ident,val> ci, unsigned &NumDep, bool &error);
    friend void borrar<ident,val>(ident id, colecInterdep<ident,val>& ci);

    // OPERACIONES ITERADOR 
    
    friend void iniciarIterador<ident,val>(colecInterdep<ident,val>& ci);
    friend bool existeSiguiente<ident,val>(colecInterdep<ident,val> ci);
    friend void siguienteIdent<ident,val>(colecInterdep<ident,val> ci, ident &id, bool &error);
    friend void siguienteVal<ident,val>(colecInterdep<ident,val> ci, val &v, bool &error);
    friend void siguienteDependiente<ident,val>(colecInterdep<ident,val> ci, bool &esDep, bool &error);
    friend void siguienteSuperior<ident,val>(colecInterdep<ident,val> ci, ident &idSup, bool &error);
    friend void siguienteNumDependientes<ident,val>(colecInterdep<ident,val> ci, unsigned &NumDep, bool &error);
    friend void avanza<ident,val>(colecInterdep<ident,val>& ci, bool &error);

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
    return ci.inicio == nullptr && ci.numElementos == 0;
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
    return (nAux != nullptr && nAux->id == id && nAux->NodoDep != nullptr );
}

template<typename ident,typename val>
bool existeIndependiente(ident id,colecInterdep<ident,val> ci) {
    typename colecInterdep<ident,val>::Nodo *nAux = ci.inicio; //puntero para recorrer la colección
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    return (nAux != nullptr && nAux->id == id && nAux->NodoDep == nullptr );
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
        nNew->NumDepend = 0;
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
        nNew->NumDepend = 0;
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

template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci, ident id, ident idSup) {
    if (id == idSup) {return;} 
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección,su anterior u uno para buscar el supervisor
        *nAux = ci.inicio, *nAuxSup = ci.inicio;
    while (nAuxSup != nullptr &&  nAuxSup->id < idSup) {
        nAuxSup = nAuxSup->siguiente;
    }
    if (nAuxSup == nullptr || nAuxSup->id != idSup) {return;} //no existe supervisor
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    if (nAux != nullptr && nAux->id == id) {
        nAuxSup->NumDepend++;
        if (nAux->NodoDep != nullptr) {
            nAux->NodoDep->NumDepend--;
        }
        nAux->NodoDep = nAuxSup;
    }
}

template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci, ident id) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección,su anterior u uno para buscar el supervisor
        *nAux = ci.inicio;
     while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    if (nAux != nullptr && nAux->id == id && nAux->NodoDep != nullptr) {
        nAux->NodoDep->NumDepend--;
        nAux->NodoDep = nullptr;
    }
}

template<typename ident,typename val>
void actualizarVal(colecInterdep<ident,val> &ci, ident id, val v, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección,su anterior u uno para buscar el supervisor
        *nAux = ci.inicio;
     while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    if (nAux == nullptr || nAux->id != id) {
        error = true;
    } else {
        error = false;
        nAux->val = v;
    }
}

template<typename ident,typename val>
void obtenerVal(ident id, colecInterdep<ident,val> ci,val &v, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección,su anterior u uno para buscar el supervisor
        *nAux = ci.inicio;
     while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    if (nAux == nullptr || nAux->id != id) {
        error = true;
    } else {
        error = false;
        v = nAux->val;
    }
}

template<typename ident,typename val>
void obtenerSupervisor(ident id, colecInterdep<ident,val> ci, ident &idSup, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección,su anterior u uno para buscar el supervisor
        *nAux = ci.inicio;
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    if (nAux == nullptr || nAux->id != id || (nAux->id == id && nAux->NodoDep == nullptr)) {
        error = true;
    } else {
        error = false;
        idSup = nAux->NodoDep->id;
    }
}

template<typename ident,typename val>
void obtenerNumDependientes(ident id, colecInterdep<ident,val> ci, unsigned &NumDep, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección,su anterior u uno para buscar el supervisor
        *nAux = ci.inicio;
     while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    if (nAux == nullptr || nAux->id != id) {
        error = true;
    } else {
        error = false;    
        NumDep = nAux->NumDepend;
    }
}

template<typename ident,typename val>
void borrar(ident id, colecInterdep<ident,val> &ci) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección y su anterior
        *nAux = ci.inicio, *nAnterior = ci.inicio;
    while (nAux != nullptr && nAux->id < id) {
        nAnterior = nAux;
        nAux = nAux->siguiente;
    }
    if (nAux != nullptr && nAux->id == id && nAux->NumDepend == 0) {
        if (nAux->NodoDep != nullptr) {
            nAux->NodoDep->NumDepend--;
        }
       if (nAux == nAnterior) {    //caso nNaux al principio       
            ci.inicio = nAux->siguiente;
            delete nAux;
        } else {    //caso nNew última posición o entre valores
            nAnterior->siguiente = nAux->siguiente;
            delete nAux;
        }
        ci.numElementos--;
    }
}

/*OPERACIONES ITERADOR*/

template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci) {
    ci.iterador = ci.inicio;
}

template<typename ident,typename val>
bool existeSiguiente(colecInterdep<ident,val> ci) {
    return ci.iterador != nullptr;
}
  
template<typename ident,typename val>
void siguienteIdent(colecInterdep<ident,val> ci, ident &id, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        id = ci.iterador->id;
    } else {
        error = true;
    }
}

template<typename ident,typename val>
void siguienteVal(colecInterdep<ident,val> ci, val &v, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        v = ci.iterador->v;
    } else {
        error = true;
    }
}

template<typename ident,typename val>
void siguienteDependiente(colecInterdep<ident,val> ci, bool &esDep, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        esDep = (ci.iterador->NodoDep != nullptr);
    } else {
        error = true;
    }
}

template<typename ident,typename val>
void siguienteSuperior(colecInterdep<ident,val> ci, ident &idSup, bool &error) {
    if (ci.iterador != nullptr && ci.iterador->NodoDep != nullptr) {
        error = false;
        idSup = ci.iterador->NodoDep->id;
    } else {
        error = true;
    }
}

template<typename ident,typename val>
void siguienteNumDependientes(colecInterdep<ident,val> ci, unsigned &NumDep, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        NumDep = ci.iterador->NumDepend;
    } else {
        error = true;
    }
}

template<typename ident,typename val>
void avanza(colecInterdep<ident,val>& ci, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        ci.iterador = ci.iterador->siguiente;
    } else {
        error = true;
    }
}

#endif //fin de colecInterdep.hpp
