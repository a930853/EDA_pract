 /* Javier Martínez Virto, 930853
* Víctor Marteles Martínez, 928927
*/
#ifndef EVENTO_HPP
#define EVENTO_HPP

#include<iostream>
using namespace std;

// PREDECLARACION DEL TAD evento (inicio INTERFAZ)

/* Los valores del TAD evento representarán tuplas formadas como:
* (descripción, prioridad) siendo la descripción una cadena y la prioridad un número natural.
*/
struct evento;

/* Devuelve en 'e' un evento compuesto con descripción 'descripcion' y con prioridad 'prioridad'.
*/
void crearEvento(string descripcion, unsigned prioridad, evento& e);

/* Dado un evento 'e' formado como (D,P), devuelve la cadena D, 
* i.e. la descripción en el evento e.
*/
string descripcion(const evento& e);

/* Dado un evento 'e' formado como (D,P), modifica 'e' para que sea igual 
* al evento compuesto como (nuevaD, P).
*/
void cambiarDescripcion(evento& e,string nuevaD);

/* Dado un evento 'e' formado como (D,P), devuelve P, 
* i.e. la prioridad en el evento e.
*/
unsigned suPrioridad(const evento& e);

/* Dado un evento 'e' formado como (D,P) y un natural 'nuevaP', 
* modifica 'e' para que sea igual al evento compuesto como (D, nuevaP).
*/
void cambiarPrioridad(evento& e,unsigned nuevaP);

// FIN de la PREDECLARACION DEL TAD evento (fin INTERFAZ)

// DECLARACION DEL TAD evento 

struct evento {
  friend void crearEvento(string descripcion, unsigned prioridad, evento& e);
  friend string descripcion(const evento& e);
  friend void cambiarDescripcion(evento& e,string nuevaD);
  friend unsigned suPrioridad(const evento& e);
  friend void cambiarPrioridad(evento& e,unsigned nuevaP);
  private:   //declaracion de la representacion interna del tipo
        // Los valores del TAD evento (tuplas (descripción, prioridad))
        // se representan mediante un registro (struct) con dos campos.
     string descripcion; // Campo para almacenar la descripción del evento.
     unsigned prioridad;      // Campo para almacenar la prioridad (natural) del evento.
};

#endif