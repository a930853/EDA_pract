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

/* Dado un evento 'e' formado como (D,P), devuelve la cadena D, 
* i.e. la descripción en el evento e.
* Coste: Θ(1)
*/
string descripcion(const evento& e) {
    return e.descripcion;
}

/* Dado un evento 'e' formado como (D,P), modifica 'e' para que sea igual 
* al evento compuesto como (nuevaD, P).
* Coste: Θ(1)
*/
void cambiarDescripcion(evento& e,string nuevaD) {
    e.descripcion = nuevaD;
}

/* Dado un evento 'e' formado como (D,P), devuelve P, 
* i.e. la prioridad en el evento e.
* Coste: Θ(1)
*/
unsigned suPrioridad(const evento& e) {
    return e.prioridad;
}

/* Dado un evento 'e' formado como (D,P) y un natural 'nuevaP', 
* modifica 'e' para que sea igual al evento compuesto como (D, nuevaP).
* Coste: Θ(1)
*/
void cambiarPrioridad(evento& e, unsigned nuevaP) {
    e.prioridad = nuevaP;
}