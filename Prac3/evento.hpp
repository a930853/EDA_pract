/* Javier Martínez Virto, 930853.
*/

#ifndef EVENTO_HPP
#define EVENTO_HPP

#include<iostream>
using namespace std;

// PREDECLARACION DEL TAD contacto (inicio INTERFAZ)

struct evento;

void crearEvento(string descripcion, int prioridad, evento& e);

string descripcion(const evento& e);

void cambiarDescripcion(evento& e,string nuevaD);

int suPrioridad(const evento& e);

void cambiarPrioridad(evento& e,int nuevaP);

// FIN de la PREDECLARACION DEL TAD evento (fin INTERFAZ)

// DECLARACION DEL TAD evento 

struct evento {
  friend void crearEvento(string descripcion, int prioridad, evento& e);
  friend string descripcion(const evento& e);
  friend void cambiarDescripcion(evento& e,string nuevaD);
  friend int suPrioridad(const evento& e);
  friend void cambiarPrioridad(evento& e,int nuevaP);
  private:  //declaracion de la representacion interna del tipo
            //... a completar COMPLETAR CON documentacion sobre la representacion interna ...
    string descripcion;
    int prioridad;
};

#endif
