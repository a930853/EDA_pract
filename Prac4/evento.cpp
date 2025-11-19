 /* Javier Martínez Virto, 930853
* Víctor Marteles Martínez, 928927
*/
#include "evento.hpp"

/* Modifica 'e' para que sea un evento compuesto con descripción 'descripcion' 
* y con prioridad 'prioridad'.
* Coste: Θ(1)
*/
void crearEvento(string descripcion, unsigned prioridad, evento& e) {
    e.descripcion = descripcion;
    e.prioridad = prioridad;
}

void obtenerDatos(evento& e, string& descripcion, unsigned& prioridad) {
    descripcion = e.descripcion;
    prioridad = e.prioridad;
}

/* Dado un evento 'e' formado como (D,P), modifica 'e' para que sea igual 
* al evento compuesto como (nuevaD, P).
* Coste: Θ(1)
*/
void cambiarDescripcion(evento& e,string nuevaD) {
    e.descripcion = nuevaD;
}

/* Dado un evento 'e' formado como (D,P) y un natural 'nuevaP', 
* modifica 'e' para que sea igual al evento compuesto como (D, nuevaP).
* Coste: Θ(1)
*/
void cambiarPrioridad(evento& e, unsigned nuevaP) {
    e.prioridad = nuevaP;
}