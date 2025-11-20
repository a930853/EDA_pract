/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP
#include "pila.hpp"

/* ----------------------------------------------------------------
 * PREDECLARACION DEL TAD GENERICO colecInterdep (inicio INTERFAZ)
 * ----------------------------------------------------------------*/
template<typename ident,typename val> struct colecInterdep;

/*
 * crear: -> colecInterdep
 */
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci);

/*
 * tamaño: colecInterdep c -> natural
 */
template<typename ident,typename val>
unsigned tamanyo(const colecInterdep<ident,val> &ci);

/*
 * esVacía?: colecInterdep c -> booleano
 */
template<typename ident,typename val>
bool esVacia(const colecInterdep<ident,val> &ci);

/*
 * existe?: ident id, colecInterdep c -> booleano
 * MODIFICADO: quitamos const para usar el buscar no-const
 */
template<typename ident,typename val>
bool existe(const ident& id, colecInterdep<ident,val> &ci, bool &esDep);

/*
 * añadirIndependiente: colecInterdep c, ident id, val v -> colecInterdep
 * MODIFICADO: ci sin const
 */
template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v);

/*
 * añadirDependiente: colecInterdep c, ident id, val v, ident super -> colecInterdep
 * MODIFICADO: ci sin const
 */
template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v,const ident &idSup);

/* MODIFICADO: ci sin const */
template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci,const ident &id,const ident &idSup);

/* MODIFICADO: ci sin const */
template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci,const ident &id);

/*
 * parcial actualizarVal: colecInterdep c, ident id, val nuevo -> colecInterdep
 * MODIFICADO: ci sin const
 */
template<typename ident,typename val>
bool actualizarVal(colecInterdep<ident,val> &ci,const ident &id,const val &v);

/*
 * parcial obtenerDatos: colecInterdep c, ident id -> (val, ident, natural, booleano)
 * MODIFICADO: ci sin const para usar buscar no-const
 */
template<typename ident,typename val>
bool obtenerDatos(const ident id, colecInterdep<ident,val> &ci, val &v, ident &idSup,unsigned &NumDep,bool &esDep);

/*
 * borrar: ident id, colecInterdep c -> colecInterdep
 * MODIFICADO: ci sin const
 */
template<typename ident,typename val>
void borrar(const ident &id, colecInterdep<ident,val>& ci);

/*---------------------
 * OPERACIONES ITERADOR
 *---------------------*/

/*
 * iniciarIterador: colecInterdep c -> colecInterdep
 */
template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci);

/**
 * existeSiguiente?: colecInterdep c -> booleano
 */
template<typename ident,typename val>
bool existeSiguiente(const colecInterdep<ident,val> &ci);

template<typename ident,typename val>
bool  siguienteYavanza(colecInterdep<ident,val> &ci, ident &id, unsigned &NumDep, val &v, bool &esDep, ident &idSup);

/*-----------------------------------------------------------------
 * FIN predeclaracion del TAD GENERICO colecInterdep (Fin INTERFAZ)
 *-----------------------------------------------------------------*/

// buscar: NO CONST (recibe Nodo* y devuelve Nodo*)
template<typename ident,typename val>
typename colecInterdep<ident,val>::Nodo* buscar(typename colecInterdep<ident,val>::Nodo *nodoAux,const ident &id);

template<typename ident,typename val>
void insertarNodo(colecInterdep<ident,val> &ci,typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v, typename colecInterdep<ident,val>::Nodo *nodoSup);

// cambiarValor: NO CONST (recibe puntero modificable)
template<typename ident,typename val>
bool cambiarValor(typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v);

template<typename ident,typename val>
void desengancharMax(typename colecInterdep<ident,val>::Nodo *&nodoAux, typename colecInterdep<ident,val>::Nodo *&maxNodo);

template<typename ident,typename val>
void eliminarNodo(colecInterdep<ident,val>& ci, typename colecInterdep<ident,val>::Nodo *&nodoAux, const ident &id);

// DECLARACION DEL TAD GENERICO colecInterdep

template<typename ident,typename val>
struct colecInterdep{

    friend void crear<ident,val>(colecInterdep<ident,val>& ci);
    friend unsigned tamanyo<ident,val>(const colecInterdep<ident,val> &ci);
    friend bool esVacia<ident,val>(const colecInterdep<ident,val> &ci);
    
    // Friends modificados (sin const)
    friend bool existe<ident,val>(const ident& id, colecInterdep<ident,val> &ci, bool &esDep);
    
    friend void anyadirIndependiente<ident,val>(colecInterdep<ident,val> &ci,const ident &id,const val &v);
    friend void anyadirDependiente<ident,val>(colecInterdep<ident,val> &ci,const ident &id,const val &v,const ident &idSup);
    friend void hacerDependiente<ident,val>(colecInterdep<ident,val> &ci,const ident &id,const ident &idSup);
    friend void hacerIndependiente<ident,val>(colecInterdep<ident,val> &ci,const ident &id);
    friend bool actualizarVal<ident,val>(colecInterdep<ident,val> &ci,const ident &id,const val &v);
    friend void borrar<ident,val>(const ident &id, colecInterdep<ident,val>& ci);
    
    friend bool obtenerDatos<ident,val>(const ident id, colecInterdep<ident,val> &ci, val &v, ident &idSup,unsigned &NumDep,bool &esDep);

    /*---------------------
    * OPERACIONES ITERADOR
    *---------------------*/
    
    friend void iniciarIterador<ident,val>(colecInterdep<ident,val> &ci);
    friend bool existeSiguiente<ident,val>(const colecInterdep<ident,val> &ci);
    friend bool siguienteYavanza<ident,val>(colecInterdep<ident,val> &ci, ident &id, unsigned &NumDep, val &v, bool &esDep, ident &idSup);

  private: 
    struct Nodo {
        ident id;           
        val v;              
        unsigned NumDepend;  
        Nodo* izq,*der;    
        Nodo* NodoDep;   
    };

    Nodo* raiz;
    unsigned numElementos;
    Pila<Nodo*> iterador;

    // Friends auxiliares (sin const)
    friend typename colecInterdep<ident,val>::Nodo* buscar<ident,val>(typename colecInterdep<ident,val>::Nodo *nodoAux,const ident &id);

    friend void insertarNodo<ident,val>(colecInterdep<ident,val> &ci,typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v, typename colecInterdep<ident,val>::Nodo *nodoSup);
    friend bool cambiarValor<ident,val>(typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v);
    friend void desengancharMax<ident,val>(typename colecInterdep<ident,val>::Nodo *&nodoAux, typename colecInterdep<ident,val>::Nodo *&maxNodo);
    friend void eliminarNodo<ident,val>(colecInterdep<ident,val>& ci, typename colecInterdep<ident,val>::Nodo *&nodoAux, const ident &id);
};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colc


template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci) {
    ci.raiz = nullptr;
    ci.numElementos = 0;
    crearVacia(ci.iterador);
}


template<typename ident,typename val>
unsigned tamanyo(const colecInterdep<ident,val> &ci) {
    return ci.numElementos;
}


template<typename ident,typename val>
bool esVacia(const colecInterdep<ident,val> &ci) {
    return ci.raiz == nullptr && ci.numElementos == 0;
}


/*FUNCION AUXILIAR MODIFICADA: Sin const*/
template<typename ident,typename val>
typename colecInterdep<ident,val>::Nodo* buscar(typename colecInterdep<ident,val>::Nodo *nodoAux,const ident &id) {
    if (nodoAux == nullptr) {
        return nullptr;
   } else {
        if(nodoAux->id < id) {
            return buscar<ident,val>(nodoAux->der,id);
        } else if(nodoAux->id == id) {
            return nodoAux; 
        } else {
            return buscar<ident,val>(nodoAux->izq,id);
        }
   }
}

/* MODIFICADO: ci sin const */
template<typename ident,typename val>
bool existe(const ident& id, colecInterdep<ident,val> &ci, bool &esDep) {
    typename colecInterdep<ident,val>::Nodo *nodoAux;
    nodoAux = buscar<ident,val>(ci.raiz,id);
    if (nodoAux != nullptr) {
        esDep = (nodoAux->NodoDep != nullptr);
    }
    // Lógica original
    return nodoAux != nullptr;
}


/*FUNCION AUXILIAR*/
template<typename ident,typename val>
void insertarNodo(colecInterdep<ident,val> &ci,typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v, typename colecInterdep<ident,val>::Nodo *nodoSup) {
   if (nodoAux == nullptr) {
        typename colecInterdep<ident,val>::Nodo 
            *nNew = new typename colecInterdep<ident,val>::Nodo;
        nNew->id = id;
        nNew->v = v;
        nNew->NumDepend = 0;
        nNew->NodoDep = nodoSup; 
        nNew->izq = nullptr; 
        nNew->der = nullptr; 
        if (nodoSup != nullptr) {
            nodoSup->NumDepend++;
        }
        ci.numElementos++;
        nodoAux = nNew; 
   } else {
        if(nodoAux->id < id) {
            insertarNodo<ident,val>(ci,nodoAux->der,id,v,nodoSup);
        } else if(!(nodoAux->id < id) && !(nodoAux->id == id)) {
            insertarNodo<ident,val>(ci,nodoAux->izq,id,v,nodoSup);
        } else {return;} 
   }
}

template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v) {
    insertarNodo<ident,val>(ci,ci.raiz,id,v,nullptr);
}

template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v,const ident &idSup) {
    typename colecInterdep<ident,val>::Nodo *nodoSup;
    nodoSup = buscar<ident,val>(ci.raiz,idSup);
    if (nodoSup != nullptr) {
        insertarNodo<ident,val>(ci,ci.raiz,id,v,nodoSup);
    }
}


template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci,const ident &id,const ident &idSup) {
    if (!(id == idSup)) {
        typename colecInterdep<ident,val>::Nodo *nodoSup;
        typename colecInterdep<ident,val>::Nodo *nodoId;
        nodoSup = buscar<ident,val>(ci.raiz,idSup);
        if (nodoSup != nullptr) {
            nodoId = buscar<ident,val>(ci.raiz,id);
            if (nodoId != nullptr) {
                if (nodoId->NodoDep != nullptr) {
                    nodoId->NodoDep->NumDepend--;
                }
                nodoSup->NumDepend++;
                nodoId->NodoDep = nodoSup;
            }
        }
    }
}

template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci,const ident &id) {
    typename colecInterdep<ident,val>::Nodo *nodoId;
    nodoId = buscar<ident,val>(ci.raiz, id); 
    if (nodoId != nullptr) {
        nodoId->NodoDep->NumDepend--;
        nodoId->NodoDep = nullptr;
    }
}


/*FUNCION AUXILIAR - MODIFICADA: sin const en nodoAux*/
template<typename ident,typename val>
bool cambiarValor(typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v) {
    if (nodoAux == nullptr) {
        return false;
    } else {
        if(nodoAux->id < id) {
            return cambiarValor<ident,val>(nodoAux->der,id,v);
        } else if(nodoAux->id == id) {
            nodoAux->v = v;
            return true;
        } else {
            return cambiarValor<ident,val>(nodoAux->izq,id,v);
        }
    }
}

template<typename ident,typename val>
bool actualizarVal(colecInterdep<ident,val> &ci,const ident &id,const val &v) {
    return cambiarValor<ident,val>(ci.raiz,id,v);
}


/* MODIFICADO: ci sin const */
template<typename ident,typename val>
bool obtenerDatos(const ident id, colecInterdep<ident,val> &ci, val &v, ident &idSup,unsigned &NumDep,bool &esDep) {
    typename colecInterdep<ident,val>::Nodo *nodoAux;
    nodoAux = buscar<ident,val>(ci.raiz,id);
    if (nodoAux != nullptr) {
        NumDep = nodoAux->NumDepend;
        v = nodoAux->v;
        if (nodoAux->NodoDep != nullptr) {
            idSup = nodoAux->NodoDep->id;
            esDep = true;
        } else { 
            esDep = false;
        }
    return true;
    } else return false;
}

/*FUNCION AUXILIAR*/
template<typename ident,typename val>
void desengancharMax(typename colecInterdep<ident,val>::Nodo *&nodoAux, typename colecInterdep<ident,val>::Nodo *&maxNodo) {
    if(nodoAux->der == nullptr) {
       maxNodo = nodoAux;
       nodoAux = nodoAux->izq;
    } else {
       desengancharMax<ident,val>(nodoAux->der,maxNodo);
    }
}

/* FUNCION AUXILIAR PARA BORRAR (versión simple correcta) */
template<typename ident,typename val>
void eliminarNodo(colecInterdep<ident,val>& ci, typename colecInterdep<ident,val>::Nodo *&nodoAux, const ident &id) {
    if (nodoAux == nullptr) return;

    if (nodoAux->id < id) {
        eliminarNodo<ident,val>(ci, nodoAux->der, id);
    } else if (id < nodoAux->id) { 
        eliminarNodo<ident,val>(ci, nodoAux->izq, id);
    } else {
        // Encontrado
        if (nodoAux->NumDepend == 0) {
            // Gestionar dependencias del superior
            if (nodoAux->NodoDep != nullptr) {
                nodoAux->NodoDep->NumDepend--;
            }

            typename colecInterdep<ident,val>::Nodo *borrar = nodoAux;

            if (nodoAux->der == nullptr) {
                nodoAux = nodoAux->izq;
            } else if (nodoAux->izq == nullptr) {
                nodoAux = nodoAux->der;
            } else {
                // Dos hijos
                typename colecInterdep<ident,val>::Nodo *nodoMax;
                desengancharMax<ident,val>(nodoAux->izq, nodoMax);
                nodoMax->der = nodoAux->der;
                nodoMax->izq = nodoAux->izq;
                nodoAux = nodoMax;
            }
            delete borrar;
            ci.numElementos--;
        }
    }
}

template<typename ident,typename val>
void borrar(const ident &id, colecInterdep<ident,val>& ci) {
    eliminarNodo<ident,val>(ci, ci.raiz, id);
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
bool existeSiguiente(const colecInterdep<ident,val> &ci) {
    return !esVacia(ci.iterador);
}

template<typename ident,typename val>
bool  siguienteYavanza(colecInterdep<ident,val> &ci, ident &id, unsigned &NumDep, val &v, bool &esDep, ident &idSup) {
    if (existeSiguiente<ident,val>(ci)) {
        typename colecInterdep<ident,val>::Nodo *nodoAux;
        bool error;
        cima(ci.iterador,nodoAux,error);
        if (!error) {
            NumDep = nodoAux->NumDepend;
            v = nodoAux->v;
            id = nodoAux->id;

            if (nodoAux->NodoDep != nullptr) {
                esDep = true;
                idSup = nodoAux->NodoDep->id;
            } else esDep = false;

            desapilar(ci.iterador);
            
            // Avanzar iterador (inorden)
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