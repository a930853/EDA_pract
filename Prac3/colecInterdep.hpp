/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#ifndef COLECINTERDEP_HPP
#define COLECINTERDEP_HPP

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
 * 
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
bool existe(ident id,colecInterdep<ident,val> ci);

/*
 * existeDependiente?: ident id, colecInterdep c -> booleano
 * {Devuelve verdad si y solo si en c hay algún elemento dependiente cuyo ident sea igual a id, es
 * decir un elemento (id, v, idSup, NumDep).}
 */
template<typename ident,typename val>
bool existeDependiente(ident id,colecInterdep<ident,val> ci);

/*
 * existeIndependiente?: ident id, colecInterdep c -> booleano
 * {Devuelve verdad si y solo si en c hay algún elemento independiente cuyo ident sea igual a id, es
 * decir un elemento (id, v, -, NumDep).}
 */
template<typename ident,typename val>
bool existeIndependiente(ident id,colecInterdep<ident,val> ci);

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
 * {Si no igual(id,super) y existe?(super,c) y existeDependiente?(id,c), ...
 * Si no igual(id,super) y existe?(super,c) y existeIndependiente?(id,c), ...
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci, ident id, ident idSup);

/*
 * hacerIndependiente: colecInterdep c, ident id -> colecInterdep
 * {Si existeDependiente?(id,c), ...
 * En cualquier otro caso, devuelve una colección igual a c.}
 */
template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci, ident id);

/*
 * parcial actualizarVal: colecInterdep c, ident id, val nuevo -> colecInterdep
 * {Si existeIndependiente?(id,c), ... Si existeDependiente?(id,c), ...
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
void actualizarVal(colecInterdep<ident,val> &ci, ident id, val v, bool &error);

/*
 * parcial obtenerVal: ident id, colecInterdep c -> val
 * {Si en c hay algún elemento con ident igual a id, ... devuelve el dato v ...
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
void obtenerVal(ident id, colecInterdep<ident,val> ci, val &v, bool &error);

/*
 * parcial obtenerSupervisor: ident id, colecInterdep c -> ident
 * {Si existeDependiente?(id,c), ... devuelve el dato sup ...
 * Parcial: la operación no está definida si no existeDependiente?(id,c).}
 */
template<typename ident,typename val>
void obtenerSupervisor(ident id, colecInterdep<ident,val> ci, ident &idSup, bool &error);

/*
 * parcial obtenerNúmDependientes: ident id, colecInterdep c -> natural
 * {Si existe?(id,c), ... devuelve el dato NumDep ...
 * Parcial: la operación no está definida si no existe?(id,c).}
 */
template<typename ident,typename val>
void obtenerNumDependientes(ident id, colecInterdep<ident,val> ci, unsigned &NumDep, bool &error);

/*
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

/*---------------------
 * OPERACIONES ITERADOR
 *---------------------*/

/*
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

    /*---------------------
    * OPERACIONES ITERADOR
    *---------------------*/
    
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

/*
* Pre: ---
* Post: Devuelve una colección 'ci' vacía (sin elementos), con el iterador inicializado.
* Coste: Θ(1)
*/
template<typename ident,typename val>
void crear(colecInterdep<ident,val>& ci) {
    // Inicializa los punteros a nulo y el contador a 0 
    ci.inicio = nullptr;
    ci.numElementos = 0;
    ci.iterador = nullptr;
}

/*
* Pre: ---
* Post: Devuelve el número de elementos que hay en la colección 'ci'.
* Coste: Θ(1)
*/
template<typename ident,typename val>
unsigned tamanyo(colecInterdep<ident,val> ci) {
    // Devuelve el contador de elementos mantenido en la estructura
    return ci.numElementos;
}

/*
* Pre: ---
* Post: Devuelve 'true' si y solo si 'ci' no contiene ningún elemento.
* Coste: Θ(1)
*/
template<typename ident,typename val>
bool esVacia(colecInterdep<ident,val> ci) {
    // Comprueba el puntero de inicio y el contador 
    return ci.inicio == nullptr && ci.numElementos == 0;
}

/*
* Pre: ---
* Post: Devuelve 'true' si y solo si en 'ci' hay algún elemento con 'ident' igual a 'id'.
* Coste: O(N) (N = numElementos). 
*/
template<typename ident,typename val>
bool existe(ident id,colecInterdep<ident,val> ci) {
    typename colecInterdep<ident,val>::Nodo *nAux = ci.inicio;
    // Búsqueda en lista ordenada: avanza mientras el 'id' actual sea menor
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    // Si el bucle paró, o es nulo (fin de lista) o 'nAux->id >= id'.
    // Comprueba si es '== id'.
    return (nAux != nullptr && nAux->id == id);
}

/*
* Pre: ---
* Post: Devuelve 'true' si existe un elemento con 'id' y es dependiente.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
bool existeDependiente(ident id,colecInterdep<ident,val> ci) {
    typename colecInterdep<ident,val>::Nodo *nAux = ci.inicio; //puntero para recorrer la colección
    // Búsqueda en lista ordenada 
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    // Devuelve 'true' si se encontró el 'id' Y su puntero de dependencia no es nulo
    return (nAux != nullptr && nAux->id == id && nAux->NodoDep != nullptr );
}

/*
* Pre: ---
* Post: Devuelve 'true' si existe un elemento con 'id' y es independiente.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
bool existeIndependiente(ident id,colecInterdep<ident,val> ci) {
    typename colecInterdep<ident,val>::Nodo *nAux = ci.inicio; //puntero para recorrer la colección
    // Búsqueda en lista ordenada 
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    // Devuelve 'true' si se encontró el 'id' Y su puntero de dependencia es nulo
    return (nAux != nullptr && nAux->id == id && nAux->NodoDep == nullptr );
}

/*
* Pre: ---
* Post: Si no existe?(id,c), añade el elemento independiente (id,v,-,0) a 'ci'
* manteniendo el orden. Si ya existe, no hace nada.
* Coste: O(N) (N = numElementos)
*/
template<typename ident,typename val>
void anyadirIndependiente(colecInterdep<ident,val> &ci, ident id, val v) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección y su anterior
        *nAux = ci.inicio, *nAnterior = ci.inicio;
    
    // 1. Buscar la posición de inserción (o el elemento si ya existe) 
    while (nAux != nullptr && nAux->id < id) {
        nAnterior = nAux;
        nAux = nAux->siguiente;
    }
    
    // 2. Si 'id' no se encontró (es nulo o el 'id' es mayor)
    if (nAux == nullptr || nAux->id != id) {
        // 3. Crear el nuevo nodo
        typename colecInterdep<ident,val>::Nodo 
            *nNew = new typename colecInterdep<ident,val>::Nodo;
        nNew->id = id;
        nNew->v = v;
        nNew->NumDepend = 0;
        nNew->NodoDep = nullptr; // Es independiente
        ci.numElementos++;
        
        // 4. Enlazar el nodo en la lista
        if (nAux == nAnterior) {    // 4a. Insertar al principio (o en lista vacía)
            ci.inicio = nNew;
            nNew->siguiente = nAux;
        } else {    // 4b. Insertar en medio o al final
            nAnterior->siguiente = nNew;
            nNew->siguiente = nAux;
        }
    }
    // Si 'id' ya existe (nAux->id == id), no se hace nada.
}

/*
* Pre: 'idSup' debe existir en 'ci'.
* Post: Si no existe?(id,c), añade el elemento (id,v,idSup,0) a 'ci'
* y actualiza el contador de 'idSup'. Si 'id' ya existe o 'idSup' no existe, no hace nada.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void anyadirDependiente(colecInterdep<ident,val> &ci, ident id, val v, ident idSup) {
    typename colecInterdep<ident,val>::Nodo //punteros para recorrer la colección
        *nAux = ci.inicio, *nAnterior = ci.inicio, *nAuxSup = ci.inicio, *nRec = ci.inicio;

    // 1. Búsqueda simultánea del supervisor (nAuxSup) y la posición de inserción (nAux)
    // nRec actúa como puntero de avance principal para asegurar que el bucle termina
    while (nRec != nullptr && (nAux->id < id || nAuxSup->id < idSup)) {
        if (nAuxSup->id < idSup) {
            nAuxSup = nAuxSup->siguiente;
        }
        if (nAux->id < id) {
            nAnterior = nAux;
            nAux = nAux->siguiente;
        }
        nRec = nRec->siguiente;
    }
    
    // 2. Comprobar que el supervisor existe (precondición)
    if (nAuxSup == nullptr || nAuxSup->id != idSup) {return;} // Supervisor no encontrado
    
    // 3. Comprobar que el 'id' a añadir no existe
    if (nAux == nullptr || nAux->id != id) {
        // 4. Crear y enlazar el nuevo nodo (similar a anyadirIndependiente)
        typename colecInterdep<ident,val>::Nodo 
            *nNew = new typename colecInterdep<ident,val>::Nodo;
        nNew->id = id;
        nNew->v = v;
        nNew->NumDepend = 0;
        nNew->NodoDep = nAuxSup; // Asignar supervisor
        nAuxSup->NumDepend++;    // Incrementar contador del supervisor
        ci.numElementos++;
        
        if (nAux == nAnterior) {    // Insertar al principio 
            ci.inicio = nNew;
            nNew->siguiente = nAux;
        } else {    // Insertar en medio o al final 
            nAnterior->siguiente = nNew;
            nNew->siguiente = nAux;
        }
    }
}

/*
* Pre: 'id' e 'idSup' deben existir en 'ci'.
* Post: Si no igual(id,idSup), 'id' pasa a ser dependiente de 'idSup'. 
* Si 'id' ya era dependiente, se actualiza su antiguo supervisor.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void hacerDependiente(colecInterdep<ident,val> &ci, ident id, ident idSup) {
    // 1. Evitar auto-dependencia
    if (id == idSup) {return;} 
    
    typename colecInterdep<ident,val>::Nodo //punteros para recorrer la colección
        *nAux = ci.inicio, *nAuxSup = ci.inicio, *nRec = ci.inicio;

    // 2. Búsqueda simultánea de 'id' (nAux) y 'idSup' (nAuxSup)
    while (nRec != nullptr && (nAux->id < id || nAuxSup->id < idSup)) {
        if (nAuxSup->id < idSup) {
            nAuxSup = nAuxSup->siguiente;
        }
        if (nAux->id < id) {
            nAux = nAux->siguiente;
        }
        nRec = nRec->siguiente;
    }
    
    // 3. Comprobar que ambos nodos existen
    if (nAuxSup == nullptr || nAuxSup->id != idSup) {return;} // Supervisor no existe
    if (nAux != nullptr && nAux->id == id) { // Nodo 'id' existe
        // 4. Re-enlazar dependencia
        nAuxSup->NumDepend++; // Incrementar nuevo supervisor
        // Si ya tenía un supervisor, decrementar el contador del antiguo
        if (nAux->NodoDep != nullptr) {
            nAux->NodoDep->NumDepend--; 
        }
        nAux->NodoDep = nAuxSup; // Asignar nuevo supervisor
    }
}

/*
* Pre: 'id' debe existir en 'ci'.
* Post: El elemento 'id' pasa a ser independiente (si era dependiente).
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void hacerIndependiente(colecInterdep<ident,val> &ci, ident id) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección
        *nAux = ci.inicio;
    
    // 1. Buscar el nodo
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    
    // 2. Si se encuentra y tiene supervisor...
    if (nAux != nullptr && nAux->id == id && nAux->NodoDep != nullptr) {
        // 3. Decrementa el contador del supervisor
        nAux->NodoDep->NumDepend--;
        // 4. Elimina el enlace de dependencia
        nAux->NodoDep = nullptr;
    }
}

/*
* Pre: 'id' debe existir en 'ci' (operación parcial).
* Post: Actualiza el valor 'v' del elemento 'id'. 'error' es 'false'.
* Si no existe 'id', 'error' es 'true'.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void actualizarVal(colecInterdep<ident,val> &ci, ident id, val v, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección
        *nAux = ci.inicio;
    
    // 1. Buscar el nodo 
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    
    // 2. Comprobar si se ha encontrado
    if (nAux == nullptr || nAux->id != id) {
        error = true;
    } else {
        // 3. Actualizar valor
        error = false;
        nAux->v = v;
    }
}

/*
* Pre: 'id' debe existir en 'ci' (operación parcial).
* Post: Devuelve en 'v' el valor del elemento 'id'. 'error' es 'false'.
* Si no existe 'id', 'error' es 'true'.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void obtenerVal(ident id, colecInterdep<ident,val> ci,val &v, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección
        *nAux = ci.inicio;
    
    // 1. Buscar el nodo 
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    
    // 2. Comprobar si se ha encontrado
    if (nAux == nullptr || nAux->id != id) {
        error = true;
    } else {
        // 3. Obtener valor
        error = false;
        v = nAux->v;
    }
}

/*
* Pre: 'id' debe existir y ser dependiente (operación parcial).
* Post: Devuelve en 'idSup' el 'id' del supervisor de 'id'. 'error' es 'false'.
* Si no existe 'id' o es independiente, 'error' es 'true'.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void obtenerSupervisor(ident id, colecInterdep<ident,val> ci, ident &idSup, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección
        *nAux = ci.inicio;

    // 1. Buscar el nodo
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    
    // 2. Comprobar precondiciones: que exista Y que sea dependiente
    if (nAux == nullptr || nAux->id != id || (nAux->id == id && nAux->NodoDep == nullptr)) {
        error = true;
    } else {
        // 3. Obtener id del supervisor
        error = false;
        idSup = nAux->NodoDep->id;
    }
}

/*
* Pre: 'id' debe existir en 'ci' (operación parcial).
* Post: Devuelve en 'NumDep' el nº de dependientes de 'id'. 'error' es 'false'.
* Si no existe 'id', 'error' es 'true'.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void obtenerNumDependientes(ident id, colecInterdep<ident,val> ci, unsigned &NumDep, bool &error) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección
        *nAux = ci.inicio;
    
    // 1. Buscar el nodo
    while (nAux != nullptr && nAux->id < id) {
        nAux = nAux->siguiente;
    }
    
    // 2. Comprobar si se ha encontrado
    if (nAux == nullptr || nAux->id != id) {
        error = true;
    } else {
        // 3. Obtener el contador
        error = false;    
        NumDep = nAux->NumDepend;
    }
}

/*
* Pre: 'id' debe existir y no tener dependientes (NumDepend == 0).
* Post: Elimina el elemento 'id' de 'ci'. Si 'id' no existe o tiene 
* dependientes, no hace nada.
* Coste: O(N) (N = numElementos).
*/
template<typename ident,typename val>
void borrar(ident id, colecInterdep<ident,val> &ci) {
    typename colecInterdep<ident,val>::Nodo //puntero para recorrer la colección y su anterior
        *nAux = ci.inicio, *nAnterior = ci.inicio;
    
    // 1. Buscar el nodo a borrar
    while (nAux != nullptr && nAux->id < id) {
        nAnterior = nAux;
        nAux = nAux->siguiente;
    }
    
    // 2. Si se encuentra Y cumple la precondición (no tiene dependientes)
    if (nAux != nullptr && nAux->id == id && nAux->NumDepend == 0) {
        
        // 3. Si era dependiente, notificar a su supervisor
        if (nAux->NodoDep != nullptr) {
            nAux->NodoDep->NumDepend--;
        }
        
        // 4. Desenlazar de la lista y liberar memoria 
        if (nAux == nAnterior) {    // 4a. Borrar el primer elemento 
            ci.inicio = nAux->siguiente;
            delete nAux;
        } else {    // 4b. Borrar un elemento intermedio o final
            nAnterior->siguiente = nAux->siguiente;
            delete nAux;
        }
        ci.numElementos--; // Decrementar contador total
    }
    // Si no se encuentra o tiene dependientes, no se borra
}

/*---------------------
 * OPERACIONES ITERADOR
 *---------------------*/

/*
* Pre: ---
* Post: Prepara el iterador para que el siguiente elemento a visitar 
* sea el primero de la colección (según el orden de 'id'). 
* Coste: Θ(1)
*/
template<typename ident,typename val>
void iniciarIterador(colecInterdep<ident,val>& ci) {
    ci.iterador = ci.inicio;
}

/*
* Pre: ---
* Post: Devuelve 'true' si queda algún elemento por visitar, 
* 'false' en caso contrario. 
* Coste: Θ(1)
*/
template<typename ident,typename val>
bool existeSiguiente(colecInterdep<ident,val> ci) {
    return ci.iterador != nullptr;
}
 
/*
* Pre: existeSiguiente(ci) == true (operación parcial).
* Post: 'id' toma el identificador del elemento actual. 'error' es 'false'.
* Si no existe siguiente, 'error' es 'true'.
* Coste: Θ(1)
*/
template<typename ident,typename val>
void siguienteIdent(colecInterdep<ident,val> ci, ident &id, bool &error) {
    // Comprueba si el iterador es nulo (fin del recorrido)
    if (ci.iterador != nullptr) {
        error = false;
        id = ci.iterador->id;
    } else {
        error = true;
    }
}

/*
* Pre: existeSiguiente(ci) == true (operación parcial).
* Post: 'v' toma el valor del elemento actual. 'error' es 'false'.
* Si no existe siguiente, 'error' es 'true'.
* Coste: Θ(1)
*/
template<typename ident,typename val>
void siguienteVal(colecInterdep<ident,val> ci, val &v, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        v = ci.iterador->v;
    } else {
        error = true;
    }
}

/*
* Pre: existeSiguiente(ci) == true (operación parcial).
* Post: 'esDep' es 'true' si el elemento actual es dependiente. 'error' es 'false'.
* Si no existe siguiente, 'error' es 'true'.
* Coste: Θ(1)
*/
template<typename ident,typename val>
void siguienteDependiente(colecInterdep<ident,val> ci, bool &esDep, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        esDep = (ci.iterador->NodoDep != nullptr);
    } else {
        error = true;
    }
}

/*
* Pre: existeSiguiente(ci) == true y el elemento actual es dependiente (parcial).
* Post: 'idSup' toma el 'id' del supervisor del elemento actual. 'error' es 'false'.
* Si no existe siguiente o es independiente, 'error' es 'true'.
* Coste: Θ(1)
*/
template<typename ident,typename val>
void siguienteSuperior(colecInterdep<ident,val> ci, ident &idSup, bool &error) {
    // Comprueba ambas precondiciones
    if (ci.iterador != nullptr && ci.iterador->NodoDep != nullptr) {
        error = false;
        idSup = ci.iterador->NodoDep->id;
    } else {
        error = true;
    }
}

/*
* Pre: existeSiguiente(ci) == true (operación parcial).
* Post: 'NumDep' toma el nº de dependientes del elemento actual. 'error' es 'false'.
* Si no existe siguiente, 'error' es 'true'.
* Coste: Θ(1)
*/
template<typename ident,typename val>
void siguienteNumDependientes(colecInterdep<ident,val> ci, unsigned &NumDep, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        NumDep = ci.iterador->NumDepend;
    } else {
        error = true;
    }
}

/*
* Pre: existeSiguiente(ci) == true (operación parcial).
* Post: Avanza el iterador al siguiente elemento. 'error' es 'false'.
* Si no existe siguiente, 'error' es 'true'.
* Coste: Θ(1)
*/
template<typename ident,typename val>
void avanza(colecInterdep<ident,val>& ci, bool &error) {
    if (ci.iterador != nullptr) {
        error = false;
        // Mueve el puntero iterador al siguiente nodo de la lista 
        ci.iterador = ci.iterador->siguiente;
    } else {
        error = true;
    }
}

#endif //fin de colecInterdep.hpp