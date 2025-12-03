/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP
#include "pila.hpp"

/* INICIO DE LA PARTE PÚBLICA o INTERFAZ  */

/* Los valores del TAD genérico colecInterdep representan colecciones de elementos formados como 
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
 * y que será 0 si ningún elemento de la colección depende de dicho elemento.
 *
 * Se requiere que el género ident tenga definidas las operaciones de comparación < y ==.
 */
template<typename ident,typename val> struct colecInterdep;


/* Crea una colección vacía, sin elementos.
*/
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci);


/* Devuelve el número de elementos que hay en la colección c.
*/
template<typename ident,typename val>
unsigned tamanyo(const colecInterdep<ident,val> &ci);


/* Devuelve verdad si y solo si c no contiene ningún elemento.
*/
template<typename ident,typename val>
bool esVacia(const colecInterdep<ident,val> &ci);


/* Devuelve verdad si y solo si en c hay algún elemento con ident igual a id.
   Si existe, devuelve en esDep si dicho elemento es dependiente (true) o independiente (false).
*/
template<typename ident,typename val>
bool existe(const ident& id, colecInterdep<ident,val> &ci, bool &esDep);


/* Si no existe?(id,c), devuelve una colección igual a la resultante de añadir el elemento
 * independiente (id,v,-,0) a la colección c. En caso contrario, devuelve una colección igual a c.
*/
template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v);


/* Si no existe?(id,c) y existe?(super,c) devuelve una colección igual a la resultante de:
 * incrementar en 1 el número de elementos dependientes del elemento con identificador super en c, y
 * de añadir el elemento (id,v,super,0) a la colección c.
 * En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v,const ident &idSup);


/* Si existe?(id,c) y existe?(idSup,c) y id != idSup, convierte al elemento 'id' en dependiente de 'idSup'.
 * Gestiona los contadores de dependencias: decrementa el del antiguo supervisor (si tenía)
 * e incrementa el del nuevo ('idSup'). Si no se cumplen las condiciones, la colección no se modifica.
*/
template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci,const ident &id,const ident &idSup);


/* Si existe?(id,c), convierte al elemento 'id' en independiente.
 * Decrementa el contador de dependencias de su supervisor actual (si lo tenía).
 * Si no existe el elemento, la colección no se modifica.
*/
template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci,const ident &id);


/* Si existe?(id,c), devuelve una colección igual a c tras actualizar el valor 'val' del elemento 'id' a 'nuevo' y devuelve true.
 * Si no existe?(id,c), devuelve false y la colección no se modifica.
*/
template<typename ident,typename val>
bool actualizarVal(colecInterdep<ident,val> &ci,const ident &id,const val &v);


/* Si existe?(id,c), devuelve true y en 'v', 'idSup', 'NumDep' y 'esDep' los datos asociados al elemento 'id'. 
 * Si 'id' es independiente, 'esDep' será falso.
 * Si no existe?(id,c), devuelve false.
*/
template<typename ident,typename val>
bool obtenerDatos(const ident id, colecInterdep<ident,val> &ci, val &v, ident &idSup,unsigned &NumDep,bool &esDep);


/* Si existeDependiente?(id,c, supAnt) y obtenerNúmDependientes(id,c)=0,
 * devuelve una colección igual a la resultante de: decrementar en 1 el NumDepend de supAnt y eliminar el elemento id.
 * Si existeIndependiente?(id,c) y obtenerNúmDependientes(id,c)=0,
 * devuelve una colección igual a la resultante de eliminar el elemento id.
 * En cualquier otro caso, devuelve una colección igual a c.
*/
template<typename ident,typename val>
void borrar(const ident &id, colecInterdep<ident,val>& ci);


/* Las operaciones siguientes conforman un iterador interno para la colección.
   Permite recorrer los elementos ordenados por su identificador (inorden).
*/

/* Inicializa el iterador para recorrer los elementos de la colección c en el orden definido por los 'ident'. 
 * El siguiente elemento a visitar será el primero (el de menor 'ident').
*/
template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci);


/* Devuelve verdad si queda algún elemento por visitar con el iterador, falso en caso contrario.
*/
template<typename ident,typename val>
bool existeSiguiente(const colecInterdep<ident,val> &ci);


/* Si existe algún elemento pendiente de visitar, devuelve true y en los parámetros de salida
 * los datos del siguiente elemento en orden, avanzando el iterador.
 * Si no quedan elementos por visitar, devuelve false.
*/
template<typename ident,typename val>
bool  siguienteYavanza(colecInterdep<ident,val> &ci, ident &id, unsigned &NumDep, val &v, bool &esDep, ident &idSup);

/* FIN DE LA PARTE PÚBLICA o INTERFAZ  */


// -- FUNCIONES AUXILIARES PRIVADAS --

// Búsqueda recursiva en el ABB. Devuelve puntero al nodo o nullptr.
template<typename ident,typename val>
typename colecInterdep<ident,val>::Nodo*& buscar(typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id);

// Inserción recursiva ordenada en el ABB.
template<typename ident,typename val>
void insertarNodo(colecInterdep<ident,val> &ci,typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v, typename colecInterdep<ident,val>::Nodo *nodoSup);

// Auxiliar para el borrado: busca el máximo del subárbol izquierdo para reemplazar al nodo borrado.
template<typename ident,typename val>
void desengancharMax(typename colecInterdep<ident,val>::Nodo *&nodoAux, typename colecInterdep<ident,val>::Nodo *&maxNodo);


// DECLARACION DEL TAD GENERICO colecInterdep

template<typename ident,typename val>
struct colecInterdep{

    friend void crear<ident,val>(colecInterdep<ident,val>& ci);
    friend unsigned tamanyo<ident,val>(const colecInterdep<ident,val> &ci);
    friend bool esVacia<ident,val>(const colecInterdep<ident,val> &ci);
    
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
    /* Representación interna basada en un Árbol Binario de Búsqueda (ABB) dinámico.
       Cada Nodo almacena un elemento de la colección y punteros para mantener la estructura de árbol y
       las relaciones de dependencia.
       - raiz: puntero a la raíz del ABB.
       - numElementos: entero para llevar la cuenta del tamaño en O(1).
       - iterador: Pila auxiliar para realizar el recorrido en inorden de forma iterativa.

       Coste Temporal en el Peor Caso (Árbol degenerado en una lista, altura = N):
       - O(1): crear, esVacia y tamanyo.
       
       - O(N): Operaciones que realizan un único recorrido de búsqueda o inserción:
         existe, anyadirIndependiente, actualizarVal, obtenerDatos, hacerIndependiente y borrar.
         
       - O(2N): Operaciones que requieren dos accesos secuenciales al árbol (dos recorridos):
         * anyadirDependiente: Primero busca al supervisor (N) y luego inserta el nuevo nodo (N).
         * hacerDependiente: Primero busca al supervisor (N) y luego busca al nodo a modificar (N).
       
       Coste Espacial:
       - O(N): Se almacena un nodo por cada elemento de la colección.
    */
    struct Nodo {
        ident id;           // Clave de ordenación en el ABB
        val v;              // Valor almacenado
        unsigned NumDepend; // Cantidad de elementos que dependen directamente de este nodo
        Nodo* izq,*der;     // Punteros para la estructura de árbol (hijos izquierdo y derecho)
        Nodo* NodoDep;      // Puntero al nodo supervisor (del que depende este nodo), NULL si independiente
    };

    Nodo* raiz;             
    unsigned numElementos;  
    Pila<Nodo*> iterador;   

    // Friends auxiliares (sin const para permitir modificación interna a través de los punteros devueltos)
    friend typename colecInterdep<ident,val>::Nodo*& buscar<ident,val>(typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id);
    friend void insertarNodo<ident,val>(colecInterdep<ident,val> &ci,typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id,const val &v, typename colecInterdep<ident,val>::Nodo *nodoSup);
    friend void desengancharMax<ident,val>(typename colecInterdep<ident,val>::Nodo *&nodoAux, typename colecInterdep<ident,val>::Nodo *&maxNodo);
};


// IMPLEMENTACION DE LAS OPERACIONES DEL TAD GENERICO colc

/* Crea una colección vacía, inicializando la raíz del ABB a nulo y el contador a 0.
*/
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci) {
    ci.raiz = nullptr;
    ci.numElementos = 0;
    crearVacia(ci.iterador);
}

/* Devuelve el número total de elementos almacenados en la colección.
*/
template<typename ident,typename val>
unsigned tamanyo(const colecInterdep<ident,val> &ci) {
    return ci.numElementos;
}

/* Devuelve verdad si y solo si la colección no contiene ningún elemento.
*/
template<typename ident,typename val>
bool esVacia(const colecInterdep<ident,val> &ci) {
    return ci.raiz == nullptr && ci.numElementos == 0;
}


/*FUNCION AUXILIAR BUSCAR
 * Realiza una búsqueda recursiva estándar en un ABB.
 * Devuelve un puntero al nodo encontrado o nullptr si no existe.
 */
template<typename ident,typename val>
typename colecInterdep<ident,val>::Nodo*& buscar(typename colecInterdep<ident,val>::Nodo *&nodoAux,const ident &id) {
    if (nodoAux == nullptr) {   
        return nodoAux;
   } else {
        if(nodoAux->id < id) {
            // Si el id del nodo actual es menor que el buscado, buscamos en la derecha (elementos mayores)
            return buscar<ident,val>(nodoAux->der,id);
        } else if(nodoAux->id == id) { 
            return nodoAux; 
        } else {
            // Si el id del nodo actual es mayor que el buscado, buscamos en la izquierda (elementos menores)
            return buscar<ident,val>(nodoAux->izq,id);
        }
   }
}

/* Devuelve verdad si existe un elemento con identificador 'id' en la colección.
   Si existe, devuelve en 'esDep' si dicho elemento es dependiente (true) o independiente (false).
*/
template<typename ident,typename val>
bool existe(const ident& id, colecInterdep<ident,val> &ci, bool &esDep) {
    typename colecInterdep<ident,val>::Nodo *nodoAux;   
    nodoAux = buscar<ident,val>(ci.raiz,id);    
    if (nodoAux != nullptr) {   //Caso de nodo encontrado
        esDep = (nodoAux->NodoDep != nullptr);     
    }
    return nodoAux != nullptr;
}


/*FUNCION AUXILIAR INSERTAR
 * Inserta un nuevo nodo manteniendo el orden del ABB de forma recursiva.
 */
template<typename ident,typename val>
void insertarNodo(colecInterdep<ident,val> &ci,typename colecInterdep<ident,val>::Nodo *&nodoAux,
                  const ident &id,const val &v, typename colecInterdep<ident,val>::Nodo *nodoSup) {

   if (nodoAux == nullptr) {    // Punto de inserción encontrado
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
        nodoAux = nNew; // Enlazamos el nuevo nodo
   } else { 
        if(nodoAux->id < id) { // Si el nodo actual es menor, el nuevo va a la derecha
            insertarNodo<ident,val>(ci,nodoAux->der,id,v,nodoSup);
        } else if(!(nodoAux->id < id) && !(nodoAux->id == id)) { // Si es mayor, a la izquierda
            insertarNodo<ident,val>(ci,nodoAux->izq,id,v,nodoSup);
        } else {return;} 
   }
}

/* Añade un nuevo elemento independiente a la colección si el 'id' no existe previamente.
*/
template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v) {
    insertarNodo<ident,val>(ci,ci.raiz,id,v,nullptr);
}

/* Añade un nuevo elemento dependiente del elemento con identificador 'idSup'.
   Requiere que 'id' no exista y que 'idSup' sí exista en la colección.
*/
template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci,const ident &id,const val &v,const ident &idSup) {
    typename colecInterdep<ident,val>::Nodo *nodoSup;
    nodoSup = buscar<ident,val>(ci.raiz,idSup); 
    if (nodoSup != nullptr) {   // si existe supervisor
        insertarNodo<ident,val>(ci,ci.raiz,id,v,nodoSup);
    }
}

/* Modifica el elemento 'id' para que pase a ser dependiente de 'idSup'.
*/
template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci,const ident &id,const ident &idSup) {
    if (!(id == idSup)) { 
        typename colecInterdep<ident,val>::Nodo *nodoSup;   //Punteros de busqueda
        
        nodoSup = buscar<ident,val>(ci.raiz,idSup);

        if (nodoSup != nullptr) {   //Si existe supervisor
            typename colecInterdep<ident,val>::Nodo *nodoId;
            nodoId = buscar<ident,val>(ci.raiz,id);

            if (nodoId != nullptr) {    //Si existe supervisor y el Id a cambiar
                if (nodoId->NodoDep != nullptr) {   //Decrementamos NumDependientes del Sup anterior en caso de que tuviera
                    nodoId->NodoDep->NumDepend--;
                }
                nodoSup->NumDepend++;
                nodoId->NodoDep = nodoSup;
            }
        }
    }
}

/* Modifica el elemento 'id' para que deje de depender de otro elemento.
*/
template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci,const ident &id) {
    typename colecInterdep<ident,val>::Nodo *nodoId;
    nodoId = buscar<ident,val>(ci.raiz, id); 
    if (nodoId != nullptr) {    //Nodo encontrado
        if (nodoId->NodoDep != nullptr) {
            nodoId->NodoDep->NumDepend--;
            nodoId->NodoDep = nullptr;
        }
    }
}



/* Actualiza el valor asociado al elemento 'id' con el nuevo valor 'v'.
   Devuelve true si se realizó la actualización, false si 'id' no existe.
*/
template<typename ident,typename val>
bool actualizarVal(colecInterdep<ident,val> &ci,const ident &id,const val &v) {
    typename colecInterdep<ident,val>::Nodo *nodoAux;
    nodoAux = buscar<ident,val>(ci.raiz, id); 
    if (nodoAux != nullptr) {    //Nodo encontrado
        nodoAux->v = v; 
        return true;
    } else return false;
}

/* Recupera toda la información asociada al elemento 'id'.
*/
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

/*FUNCION AUXILIAR DESENGANCHARMAX
 * Busca y desenlaza el nodo con valor máximo del subárbol para sustituir a un nodo borrado.
 */
template<typename ident,typename val>
void desengancharMax(typename colecInterdep<ident,val>::Nodo *&nodoAux, typename colecInterdep<ident,val>::Nodo *&maxNodo) {
    if(nodoAux->der == nullptr) { // Hemos llegado al máximo (más a la derecha)
       maxNodo = nodoAux;         
       nodoAux = nodoAux->izq;    
    } else {
       desengancharMax<ident,val>(nodoAux->der,maxNodo);
    }
}


/* Elimina el elemento 'id' de la colección si existe y si no tiene dependientes (NumDepend == 0).
*/
template<typename ident,typename val>
void borrar(const ident &id, colecInterdep<ident,val>& ci) {
    typename colecInterdep<ident,val>::Nodo*& nodoAux = buscar<ident,val>(ci.raiz,id);

    if (nodoAux != nullptr && nodoAux->NumDepend == 0) { 
            
            // Gestionar dependencias del supervisor 
            if (nodoAux->NodoDep != nullptr) {
                nodoAux->NodoDep->NumDepend--;
            }

            typename colecInterdep<ident,val>::Nodo *borrar = nodoAux;

            // Reestructuración del ABB
            if (nodoAux->der == nullptr) { // Caso 1 o 0 hijos (sin hijo derecho)
                nodoAux = nodoAux->izq;    
            } else if (nodoAux->izq == nullptr) { // Caso 1 hijo (sin hijo izquierdo)
                nodoAux = nodoAux->der;    
            } else {
                // Caso 2 hijos
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

/*---------------------
 * OPERACIONES ITERADOR
 *---------------------*/

/* Inicializa el iterador para un recorrido en inorden (ordenado por identificador).
   Apila la rama izquierda desde la raíz para preparar el primer elemento (el menor).
*/
template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci) {
    liberar(ci.iterador); 
    typename colecInterdep<ident,val>::Nodo *nodoAux = ci.raiz;
    
    // Apilamos la rama izquierda completa para llegar al menor elemento
    while (nodoAux != nullptr) {
        apilar(ci.iterador,nodoAux);
        nodoAux = nodoAux->izq; 
    }
}


/* Devuelve verdad si la pila del iterador no está vacía.
*/
template<typename ident,typename val>
bool existeSiguiente(const colecInterdep<ident,val> &ci) {
    return !esVacia(ci.iterador);
}

/* Devuelve los datos del siguiente elemento en orden y avanza el iterador al próximo.
   Utiliza la pila auxiliar para gestionar el recorrido en inorden.
*/
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
            
            // Avanzar iterador (inorden): tras visitar un nodo, vamos a su subárbol derecho
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