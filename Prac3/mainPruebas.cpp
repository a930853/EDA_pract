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
    f.open("entradaPrueba.txt"); // cambiar .txt !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    bool error;     // error en funciones parciales

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

            } else {                // poner un caso por si no pone ni DEP ni IND ??????????????????????????
                anyadirIndependiente(ci,nom,e);

            }
            
            
                // quitar esto después de hacer las pruebas !!!!!!!!!!!!!!!!!!!!!!!
                cout << nom << " / " << desc << " -> " << descripcion(e) << " / " << prio << " -> " << suPrioridad(e) 
                 << " / " << tipoDep << " / " << eventoSup << endl;



                // funciones para salida.txt

            




	    } else if (instruccion == "C") {         
            getline(f,nom);
            getline(f,desc);
            getline(f,prioS);
            prio = stoi(prioS);     // convertimos el string "prioS" en un int "prio"


            obtenerVal(nom,ci,e,error);
            if(!error) {            // parar el programa si hay error o seguir sin más a por la sig. instrucción ?!?!?!?!??!?!??!?!
                cambiarDescripcion(e,desc);
                cambiarPrioridad(e,prio);
                actualizarVal(ci,nom,e,error);
                // repasar lo de arriba y continuar si falta algo



                // funciones para salida.txt    



            }



            

        } else if (instruccion == "D") {




        } else if (instruccion == "O") {




        } else if (instruccion == "E") {




        } else if (instruccion == "I") {




        } else if (instruccion == "B") {




        } else if (instruccion == "LD") {




        } else if (instruccion == "LT") {




        } 
    }


    

    f.close();
}