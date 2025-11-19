 /* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP
#include "pila.hpp"

/* ----------------------------------------------------------------
 * PREDECLARACION DEL TAD GENERICO colecInterdep (inicio INTERFAZ)
 * ----------------------------------------------------------------
 * operación {Se requiere que el género ident tenga definidas las siguientes operaciones.                 
 * Las operaciones igual y anterior definen una relación de orden total (i.e., permiten 
 * organizar los datos de la colección en forma de secuencia ordenada)}
 *  
 * igual: ident s1, ident s2  booleano {devuelve verdad si y solo si s1 es igual que s2.} 
 * anterior: ident s1, ident s2  booleano {devuelve verdad si y solo si s1 es anterior a s2.} 
 * 
 * Género colecInterdep 
 * {Los valores del TAD representan colecciones de elementos formados como 
 * tuplas de la forma (ident, val, -, NumDepend) o bien (ident, val, identSup, NumDepend). 
 * A los elementos con forma (ident, val, -, NumDepend) los llamaremos en general 
 * ‘elementos independientes’, mientras que a los elementos con forma 
 * (ident, val, identSup, NumDepend),los llamaremos en general ‘elementos dependientes’.
 * En la colección no podrá haber dos elementos con el mismo ident. En las tuplas que representan 
 * elementos dependientes, la información identSup será la identificación del elemento del 
 * que es directamente dependiente el elemento con identificación ident. 
 * Ningún elemento de la colección podrá ser directamente dependiente de sí mismo, 
 * y todo elemento dependiente debe serlo de otro elemento que exista en la colección 
 * (que a su vez puede ser un elemento independiente o dependiente). En cada elemento, 
 * la información NumDepend de su tupla representará el número total de elementos     
 * en la colección que son directamente dependientes del elemento con identificador ident, 
 * y que será 0 si ningún elemento de la colección depende de dicho elemento.}
 */
template<typename ident,typename val> struct colecInterdep;


/*
 * crear: -> colecInterdep
 * {Crea una colección vacía, sin elementos.}
 */
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci);

/*
 * tamaño: colecInterdep c -> natural
 * {Devuelve el número de elementos que hay en la colección c.}
 */
template<typename ident,typename val>
unsigned tamanyo(colecInterdep<ident,val> ci);

/*
 * esVacía?: colecInterdep c -> booleano
 * {Devuelve verdad si y solo si c no contiene ningún elemento.}
 */
template<typename ident,typename val>
bool esVacia(colecInterdep<ident,val> ci);

/*
 * existe?: ident id, colecInterdep c -> booleano
 * {Devuelve verdad si y solo si en c hay algún elemento con ident igual a id.}
 */
template<typename ident,typename val>
bool existe(ident id,colecInterdep<ident,val> ci, bool esDep);

/*
 * añadirIndependiente: colecInterdep c, ident id, val v -> colecInterdep
 * {Si no existe?(id,c), devuelve una colección igual a la resultante de añadir el elemento
 * independiente (id,v,-,0) a la colección c. En caso contrario, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci, ident id, val v);

/*
 * añadirDependiente: colecInterdep c, ident id, val v, ident super -> colecInterdep
 * {Si no existe?(id,c) y existe?(super,c) devuelve una colección igual a la resultante de:
 * incrementar en 1 el número de elementos dependientes del elemento con identificador super en c, y
 * de añadir el elemento (id,v,super,0) a la colección c.
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci, ident id, val v, ident idSup);

/*
 * hacerDependiente: colecInterdep c, ident id, ident super -> colecInterdep
 * {Si no igual(id,super), existe?(id,c) y existe?(super,c): 
 * si id era independiente, lo convierte en dependiente de super e incrementa el NumDepend de super. 
 * Si id ya era dependiente de supAnt, decrementa el NumDepend de supAnt, lo convierte en dependiente de super e incrementa el NumDepend de super. 
 * En cualquier otro caso, devuelve c sin modificar.}
 */
template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci, ident id, ident idSup);

/*
 * hacerIndependiente: colecInterdep c, ident id -> colecInterdep
 * {Si existeDependiente?(id,c, supAnt), devuelve una colección igual a c tras decrementar en 1 el NumDepend de supAnt 
 * y convertir id en un elemento independiente (id, v, -, NumDepend). 
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci, ident id);

/*
 * parcial actualizarVal: colecInterdep c, ident id, val nuevo -> colecInterdep
 * {Si existe?(id,c), devuelve una colección igual a c tras actualizar el valor 'val' del elemento 'id' a 'nuevo'.
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
bool actualizarVal(colecInterdep<ident,val> &ci, ident id, val v);

/*
 * parcial obtenerDatos: colecInterdep c, ident id -> (val, ident, natural, booleano)
 * {Si existe?(id,c), devuelve en 'v', 'idSup', 'NumDep' y 'esDep' los datos asociados al elemento 'id'. 
 * Si 'id' es independiente, 'esDep' será falso.
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
void obtenerDatos(ident id, colecInterdep<ident,val> ci, val &v, ident &idSup,unsigned &NumDep,bool &esDep, bool &error);

/*
 * borrar: ident id, colecInterdep c -> colecInterdep
 * {Si existeDependiente?(id,c, supAnt) y obtenerNúmDependientes(id,c)=0,
 * devuelve una colección igual a la resultante de: decrementar en 1 el NumDepend de supAnt y eliminar el elemento id.
 * Si existeIndependiente?(id,c) y obtenerNúmDependientes(id,c)=0,
 * devuelve una colección igual a la resultante de eliminar el elemento id.
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void borrar(ident id, colecInterdep<ident,val> &ci);

/*---------------------
 * OPERACIONES ITERADOR
 *---------------------*/

/*
 * iniciarIterador: colecInterdep c -> colecInterdep
 * {Inicializa el iterador para recorrer los elementos de la colección c en el orden definido por los 'ident'. 
 * El siguiente elemento a visitar será el primero (el de menor 'ident').}
 */
template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci);

/**
 * existeSiguiente?: colecInterdep c -> booleano
 * {Devuelve verdad si queda algún elemento por visitar con el iterador, falso en caso contrario.}
 */
template<typename ident,typename val>
bool existeSiguiente(colecInterdep<ident,val> ci);

template<typename ident,typename val>
bool  siguienteYavanza(colecInterdep<ident,val> ci, ident &id, unsigned &NumDep, val &v, bool &esDep, ident &idSup);

/*-----------------------------------------------------------------
 * FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)
 *-----------------------------------------------------------------*/

template<typename ident,typename val>
typename colecInterdep<ident,val>::Nodo* buscar(typename colecInterdep<ident,val>::Nodo *nodoAux, ident id);

template<typename ident,typename val>
void insertarNodo(typename colecInterdep<ident,val>::Nodo *nodoAux,ident id,val v, typename colecInterdep<ident,val>::Nodo *nodoSup);

template<typename ident,typename val>
bool cambiarValor(typename colecInterdep<ident,val>::Nodo *nodoAux, ident id, val v);

template<typename ident,typename val>
void desengancharMax(typename colecInterdep<ident,val>::Nodo *nodoAux, typename colecInterdep<ident,val>::Nodo *maxNodo);

// DECLARACION DEL TAD GENERICO colecInterdep

template<typename ident,typename val>
struct colecInterdep{

    friend void crear<ident,val>(colecInterdep<ident,val>& ci);
    friend unsigned tamanyo<ident,val>(colecInterdep<ident,val> ci);
    friend bool esVacia<ident,val>(colecInterdep<ident,val> ci);
    friend bool existe<ident,val>(ident id,colecInterdep<ident,val> ci, bool esDep);
    friend void anyadirIndependiente<ident,val>(colecInterdep<ident,val> &ci, ident id, val v);
    friend void anyadirDependiente<ident,val>(colecInterdep<ident,val> &ci, ident id, val v, ident idSup);
    friend void cambiarDependencia<ident,val>(colecInterdep<ident,val> &ci, ident id, ident idSup);
    friend bool actualizarVal<ident,val>(colecInterdep<ident,val> &ci, ident id, val v);
    friend void obtenerDatos<ident,val>(ident id, colecInterdep<ident,val> ci, val &v, ident &idSup,unsigned &NumDep,bool &esDep, bool &error);
    friend void borrar<ident,val>(ident id, colecInterdep<ident,val>& ci);

    /*---------------------
    * OPERACIONES ITERADOR
    *---------------------*/
    
    friend void iniciarIterador<ident,val>(colecInterdep<ident,val>& ci);
    friend bool existeSiguiente<ident,val>(colecInterdep<ident,val> ci);
    friend bool siguienteYavanza<ident,val>(colecInterdep<ident,val> ci, ident &id, unsigned &NumDep, val &v, bool &esDep, ident &idSup);

  private: //declaracion de la representacion interna del tipo
    struct Nodo {
        ident id;           // Identificador (clave de ordenación)
        val v;              // Valor asociado
        unsigned NumDepend;  // Contador de dependientes directos
        Nodo* izq,*der;    // Punteros a los siguientes nodo en la lista (ordenada por 'id')
        Nodo* NodoDep;   // Puntero al nodo al cual es dependiente (es NULL si es independiente)
    };

    /**
     * Puntero al inicio de la lista enlazada.
     * Apunta al primer 'Nodo' de la colección, que es el
     * elemento con el 'id' menor según la relación de orden.
     * Si la colección está vacía, 'inicio' es NULL.
     */
    Nodo* raiz;

    /**
     * Contador del número total de elementos.
     * Almacena el número de nodos en la colección para que
     * la operación 'tamaño' sea de coste O(1).
     */
    unsigned numElementos;

    /**
     * Puntero a la pila del estado del iterador.
     * Apunta al *siguiente* nodo que debe ser visitado/leído.
     * - 'iniciarIterador' lo coloca en 'inicio'.
     * - 'avanza' lo mueve a 'iterador->siguiente'.
     * - Si es NULL, 'existeSiguiente' devuelve falso.
     */
    Pila<Nodo*> iterador;

    friend typename colecInterdep<ident,val>::Nodo* buscar<ident,val>(typename colecInterdep<ident,val>::Nodo *nodoAux, ident id);

    friend void insertarNodo<ident,val>(typename colecInterdep<ident,val>::Nodo *nodoAux,ident id,val v, typename colecInterdep<ident,val>::Nodo *nodoSup);

    friend bool cambiarValor<ident,val>(typename colecInterdep<ident,val>::Nodo *nodoAux, ident id, val v);

    friend void desengancharMax<ident,val>(typename colecInterdep<ident,val>::Nodo *nodoAux, typename colecInterdep<ident,val>::Nodo *maxNodo);
};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colc


template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci) {
    // Inicializa los punteros a nulo y el contador a 0 
    ci.raiz = nullptr;
    ci.numElementos = 0;
    crearVacia(ci.iterador);
}


template<typename ident,typename val>
unsigned tamanyo(colecInterdep<ident,val> ci) {
    // Devuelve el contador de elementos mantenido en la estructura
    return ci.numElementos;
}


template<typename ident,typename val>
bool esVacia(colecInterdep<ident,val> ci) {
    // Comprueba el puntero de inicio y el contador 
    return ci.raiz == nullptr && ci.numElementos == 0;
}


/*FUNCION AUXILIAR*/
template<typename ident,typename val>
typename colecInterdep<ident,val>::Nodo* buscar(typename colecInterdep<ident,val>::Nodo *nodoAux, ident id) {
    if (nodoAux == nullptr) {
        return nullptr;
   } else {
        if(nodoAux->id < idSup) {
            return buscar(nodoAux->izq,id);
        } else if(nodoAux->id == id) {
            return nodoAux;
        } else {
            buscar(nodoAux->der,id);
        }
   }
}


template<typename ident,typename val>
bool existe(ident id,colecInterdep<ident,val> ci, bool esDep) {
    typename colecInterdep<ident,val>::Nodo *nodoAux;
    nodoAux = buscar(ci.raiz,id,esDep);
    return nodoAux != nullptr;
}



/*FUNCION AUXILIAR*/
template<typename ident,typename val>
void insertarNodo(typename colecInterdep<ident,val>::Nodo *nodoAux,ident id,val v, 
                    typename colecInterdep<ident,val>::Nodo *nodoSup) {
   if (nodoAux == nullptr) {
        typename colecInterdep<ident,val>::Nodo 
            *nNew = new typename colecInterdep<ident,val>::Nodo;
        nNew->id = id;
        nNew->v = v;
        nNew->NumDepend = 0;
        nNew->NodoDep = nodoSup; 
        if (nodoSup != nullptr) {
            nodoSup->NumDepend++;
        }
        ci.numElementos++;
   } else {
        if(nodoAux->id < id) {
            insertarNodo(nodoAux->izq,id,v,nodoSup);
        } else if(nodoAux->id > id) {
            insertarNodo(nodoAux->der,id,v,nodoSup);
        } else {return;} //caso nodoAux->id == id
   }
}

template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci, ident id, val v) {
    insertarNodo(ci.raiz,id,v,nullptr);
}

template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci, ident id, val v, ident idSup) {
    typename colecInterdep<ident,val>::Nodo *nodoSup;
    nodoSup = buscar(ci.raiz,idSup);
    if (nodoSup != nullptr) {
        insertarNodo(ci.raiz,id,v,nodoSup);
    }
}


template<typename ident,typename val>
void cambiarDependencia(colecInterdep<ident,val> &ci, ident id, ident idSup) {
    if (id != idSup) {
        typename colecInterdep<ident,val>::Nodo *nodoSup;
        nodoSup = buscar(ci.raiz,idSup);
        if (nodoSup != nullptr) {
            if (nodoSup != nullptr) {
                nodoAux->NodoDep = nodoSup;
                nodoSup->NumDepend++;
            } else {
                nodoAux->nodoDep->NumDepend--;
                nodoAux->NodoDep = nullptr;
            }
        }
    }
}

/*FUNCION AUXILIAR*/
template<typename ident,typename val>
bool cambiarValor(typename colecInterdep<ident,val>::Nodo *nodoAux, ident id, val v) {
    if (nodoAux == nullptr) {
        return false;
    } else {
        if(nodoAux->id < id) {
            return cambiarValor(nodoAux->izq,id,v);
        } else if(nodoAux->id == id) {
            nodoAux->v = v;
            return true;
        } else {
            return cambiarValor(nodoAux->der,id,v);
        }
    }
}

template<typename ident,typename val>
bool actualizarVal(colecInterdep<ident,val> &ci, ident id, val v) {
    return cambiarValor(ci.raiz,id,v);
}


template<typename ident,typename val>
bool obtenerDatos(ident id, colecInterdep<ident,val> ci, val &v, ident &idSup,unsigned &NumDep,bool &esDep) {
    typename colecInterdep<ident,val>::Nodo *nodoAux;
    nodoAux = buscar(ci.raiz,id);
    if (nodoAux != nullptr) {
        NumDep = nAux->NumDepend;
        v = nAux->v;
        if (nAux->NodoDep != nullptr) {
            idSup = nAux->NodoDep->id;
            esDep = true;
        } else { 
            esDep = false;
        }
    return true;
    } else return false;
}

/*FUNCION AUXILIAR*/
template<typename ident,typename val>
void desengancharMax(typename colecInterdep<ident,val>::Nodo *nodoAux, typename colecInterdep<ident,val>::Nodo *maxNodo) {
    if(nodoAux->der == nullptr) {
       maxNodo = nodoAux;
       nodoAux = nodoAux->izq;
       maxNodo->izq = nullptr;
    } else {
        desengancharMax(nodoAux->der,maxNodo);
    }
}


template<typename ident,typename val>
void borrar(ident id, colecInterdep<ident,val> &ci) {
    typename colecInterdep<ident,val>::Nodo *nodoAux;
    nodoAux = buscar(ci.raiz,id);
    if (nodoAux != nullptr) {
        typename colecInterdep<ident,val>::Nodo *nodoAux2;
            if (nodoAux->izq == nullptr) {
                nodoAux2 = nodoAux;
                nodoAux->der = nodoAux;
                delete nodoAux2;

            } else if (nodoAux->der == nullptr) {
                nodoAux2 = nodoAux;
                nodoAux->izq = nodoAux;
                delete nodoAux2;

            } else {
                desengancharMax(nodoAux->izq,nodoAux->id);
            }
        
    }
}

/*---------------------
 * OPERACIONES ITERADOR
 *---------------------*/


template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci) {
    liberar(ci.iterador);
    typename colecInterdep<ident,val>::Nodo *nodoAux = ci.raiz;
    while (nodoAux != nullptr) {
        apilar(ci.iterador,nodoAux);
        nodoAux = nodoAux->izq;
    }
}


template<typename ident,typename val>
bool existeSiguiente(colecInterdep<ident,val> ci) {
    return esVacia(ci.iterador);
}

template<typename ident,typename val>
bool  siguienteYavanza(colecInterdep<ident,val> ci, ident &id, unsigned &NumDep, val &v, bool &esDep, ident &idSup) {
    if (existeSiguiente(ci)) {
        typename colecInterdep<ident,val>::Nodo *nodoAux;
        bool error;
        cima(ci.iterador,nodoAux,error);
        if (!error) {
            NumDep = ci.iterador->NumDepend;
            v = ci.nodoAux->v;
            id = ci.nodoAux->id;

            if (ci.nodoAux->NodoDep != nullptr) {
                esDep = true;
                idSup = ci.nodoAux->NodoDep->id;
            } else esDep = false;
            desapilar(ci.iterador);
            nodoAux = nodoAux->der;
            while (nodoAux != nullptr) {
                apilar(ci.iterador,nodoAux);
                nodoAux = nodoAux->izq;
            }
            return true;
        } else return false;
    } else return false;
}

#endif //fin de colecInterdep.hpp