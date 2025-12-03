/* Javier Martínez Virto, 930853
* Víctor Marteles Martínez, 928927
*/
#include "tareas.hpp"

/* Dadas tres cadenas y un real 'tEstimado', intenta inicializar la tarea 't'.
* Si 'tEstimado' < 0 devuelve false (operación parcial).
* Si es correcto, devuelve true e inicializa el tiempo empleado a 0.0.
* Coste: Θ(1)
*/
bool crearTarea(tareas& t, string nombre, string descripcion, string uTiempo, double tEstimado) {
    if (tEstimado < 0) {
        return false;
    }
    t.nombre = nombre;
    t.descripcion = descripcion;
    t.uTiempo = uTiempo;
    t.tEstimado = tEstimado;
    t.tEmpleado = 0.0;
    return true;
}

/* Dada una tarea 't', devuelve en los parámetros por referencia los componentes de la tupla:
* nombre, descripción, unidad de tiempo, tiempo estimado y tiempo empleado.
* Coste: Θ(1)
*/
void obtenerDatos(const tareas& t, string& nombre, string& descripcion, string& uTiempo, double& tEstimado, double& tEmpleado) {
    nombre = t.nombre;
    descripcion = t.descripcion;
    uTiempo = t.uTiempo;
    tEstimado = t.tEstimado;
    tEmpleado = t.tEmpleado;
}

/* Dada una tarea 't', modifica 't' sustituyendo su nombre por la cadena 'nombre'.
* Coste: Θ(1)
*/
void cambiarNombre(tareas& t, string nombre) {
    t.nombre = nombre;
}

/* Dada una tarea 't', modifica 't' sustituyendo su descripción por la cadena 'descripcion'.
* Coste: Θ(1)
*/
void cambiarDescripcion(tareas& t, string descripcion) {
    t.descripcion = descripcion;
}

/* Dada una tarea 't', modifica 't' sustituyendo su unidad de tiempo por la cadena 'uTiempo'.
* Coste: Θ(1)
*/
void cambiarUnidad(tareas& t, string uTiempo) {
    t.uTiempo = uTiempo;
}

/* Dada una tarea 't' y un real 'tEstimado', si el nuevo tiempo no es negativo,
* modifica 't' actualizando su tiempo estimado y devuelve true.
* Si es negativo, no modifica nada y devuelve false.
* Coste: Θ(1)
*/
bool cambiarTiempoEstimado(tareas& t, double tEstimado) {
    if (tEstimado < 0) {
        return false;
    }
    else {
        t.tEstimado = tEstimado; 
        return true;
    }
}

/* Dada una tarea 't' y un real 'tEmpleado', si el nuevo tiempo no es negativo,
* modifica 't' actualizando su tiempo empleado y devuelve true.
* Si es negativo, no modifica nada y devuelve false.
* Coste: Θ(1)
*/
bool cambiarTiempoEmpleado(tareas& t, double tEmpleado) {
    if (tEmpleado < 0) {
        return false;
    }
    else {
        t.tEmpleado = tEmpleado; 
        return true;
    }
}