/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#include "evento.hpp"
#include "colecInterdep.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    
    colecInterdep<string,evento> ci;

    crear(ci);  // creamos la colección vacía

    ifstream f; 
    f.open("entrada.txt"); 
    if(!f.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    string instruccion, salto; 
    string nom;     // nombre
    evento e;       // evento
    string desc;    // descripción
    string prioS;   // prioridad (string)
    int prio;       // prioridad (int)
    string tipoDep;  // tipo de dependencia (dep. o ind.)
    string eventoSup;   // nombre del evento del cual depende el evento que se añade ("vacío" si es independiente)

    while (f >> instruccion) {     
	    getline(f,salto);   
         
	    if (instruccion == "A") {         
            
            // quizás hay que poner aquí un "existe()" o algo parecido ????????????????????
            
            getline(f,nom);
            getline(f,desc);
            getline(f,prioS);
            prio = stoi(prioS);     // convertimos el string "prioS" en un int "prio"
            getline(f,tipoDep);
            getline(f,eventoSup);

            crearEvento(desc,prio,e); // creamos el evento con la descripción y prioridad dadas

            if(tipoDep == "DEPendiente") {
                anyadirDependiente(ci,nom,e,eventoSup);

            } else {                // poner un caso por si no pone es ni dep ni ind ??????????????????????????
                anyadirIndependiente(ci,nom,e);

                
                // salida.txt

            }


            


	    } else if (instruccion == "O") {         
		//... sigue el programa 
        }//... sigue el programa
    }
    f.close();
}