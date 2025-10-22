/* Javier Martínez Virto, 930853
* Víctor Marteles Martínez, 928927
*/

#include "evento.hpp"


void crearEvento(string descripcion, int prioridad, evento& e) {
    e.descripcion = descripcion;
    e.prioridad = prioridad;
}

string descripcion(const evento& e) {
    return e.descripcion;
}

void cambiarDescripcion(evento& e,string nuevaD) {
    e.descripcion = nuevaD;
}

int suPrioridad(const evento& e) {
    return e.prioridad;
}

void cambiarPrioridad(evento& e,int nuevaP) {
    e.prioridad = nuevaP;
}
