/* Javier Martínez Virto, 930853
* Víctor Marteles Martínez, 928927
*/
#ifndef TAREAS_HPP
#define TAREAS_HPP

#include<iostream>
#include<string>
using namespace std;

// PREDECLARACION DEL TAD tareas (inicio INTERFAZ)

/* Los valores del TAD tarea representarán tuplas formadas como:
* (nombre, descripción, unidadTiempo, tiempoEstimado, tiempoEmpleado)
* siendo los tiempos números reales y el resto cadenas.
*/
struct tareas;

/* Dadas tres cadenas y un real 'tEstimado', intenta inicializar la tarea 't'.
* Si 'tEstimado' < 0 devuelve false (operación parcial).
* Si es correcto, devuelve true e inicializa el tiempo empleado a 0.0.
*/
bool crearTarea(tareas& t, string nombre, string descripcion, string uTiempo, double tEstimado);

/* Dada una tarea 't', devuelve en los parámetros por referencia los componentes de la tupla:
* nombre, descripción, unidad de tiempo, tiempo estimado y tiempo empleado.
*/
void obtenerDatos(const tareas& t, string& nombre, string& descripcion, string& uTiempo, double& tEstimado, double& tEmpleado);

/* Dada una tarea 't', modifica 't' sustituyendo su nombre por la cadena 'nombre'.
*/
void cambiarNombre(tareas& t, string nombre);

/* Dada una tarea 't', modifica 't' sustituyendo su descripción por la cadena 'descripcion'.
*/
void cambiarDescripcion(tareas& t, string descripcion);

/* Dada una tarea 't', modifica 't' sustituyendo su unidad de tiempo por la cadena 'uTiempo'.
*/
void cambiarUnidad(tareas& t, string uTiempo);

/* Dada una tarea 't' y un real 'tEstimado', si el nuevo tiempo no es negativo,
* modifica 't' actualizando su tiempo estimado y devuelve true.
* Si es negativo, no modifica nada y devuelve false.
*/
bool cambiarTiempoEstimado(tareas& t, double tEstimado);

/* Dada una tarea 't' y un real 'tEmpleado', si el nuevo tiempo no es negativo,
* modifica 't' actualizando su tiempo empleado y devuelve true.
* Si es negativo, no modifica nada y devuelve false.
*/
bool cambiarTiempoEmpleado(tareas& t, double tEmpleado);

// FIN de la PREDECLARACION DEL TAD tareas (fin INTERFAZ)

// DECLARACION DEL TAD tareas

struct tareas {
  friend bool crearTarea(tareas& t, string nombre, string descripcion, string uTiempo, double tEstimado);
  friend void obtenerDatos(const tareas& t, string& nombre, string& descripcion, string& uTiempo, double& tEstimado, double& tEmpleado);
  friend void cambiarNombre(tareas& t, string nombre);
  friend void cambiarDescripcion(tareas& t, string descripcion);
  friend void cambiarUnidad(tareas& t, string uTiempo);
  friend bool cambiarTiempoEstimado(tareas& t, double tEstimado);
  friend bool cambiarTiempoEmpleado(tareas& t, double tEmpleado);

  private:   //declaracion de la representacion interna del tipo
        // Los valores del TAD tarea se representan mediante un registro (struct) con cinco campos.
     string nombre;       // Campo para almacenar el nombre de la tarea.
     string descripcion;  // Campo para almacenar la descripción.
     string uTiempo;      // Campo para la unidad de tiempo (ej: "horas").
     double tEstimado;    // Campo para el tiempo estimado (real).
     double tEmpleado;    // Campo para el tiempo empleado (real).
};

#endif