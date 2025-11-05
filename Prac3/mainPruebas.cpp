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

    ifstream ent; 
    ofstream sal;
    ent.open("entradaPrueba.txt"); // cambiar .txt !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(!ent.is_open()) {
        cerr << "No se pudo abrir el archivo entrada." << endl;
        return 1;
    }

    sal.open("salidaPrueba.txt"); // cambiar .txt !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(!sal.is_open()) {
        cerr << "No se pudo abrir el archivo salida." << endl;
        return 1;
    }

    string instruccion, salto; 
    string nom;     // nombre
    evento e;       // evento
    string desc;    // descripción
    string prioS;   // prioridad (string)
    int prio;       // prioridad (int)
    unsigned NumDep;
    string tipoDep;  // tipo de dependencia (dep. o ind.)
    string eventoSup;   // nombre del evento del cual depende el evento que se añade ("vacío" si es independiente)
    bool error;     // error en funciones parciales

    while (ent >> instruccion) {     
	    getline(ent,salto);   
         
	    if (instruccion == "A") {         
            
            getline(ent,nom);
            getline(ent,desc);
            getline(ent,prioS);
            prio = stoi(prioS);     // convertimos el string "prioS" en un int "prio"
            getline(ent,tipoDep);
            getline(ent,eventoSup);

            crearEvento(desc,prio,e); // creamos el evento con la descripción y prioridad dadas


            
            if(!existe(nom,ci)) { // si no existe un evento con el mismo nombre
                if(tipoDep == "DEPendiente") {
                    anyadirDependiente(ci,nom,e,eventoSup);

                    if(existeDependiente(nom,ci)) {    // si se ha añadido bien
                        sal << "INTRODUCIDO: ";

                    } else {
                        sal << "NO INTRODUCIDO: ";
                    }

                    sal << "[ " << nom << " -de-> " << eventoSup << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;

                } else {                // poner un caso por si no pone ni DEP ni IND ??????????????????????????
                    anyadirIndependiente(ci,nom,e);

                    if(existeIndependiente(nom,ci)) {    // si se ha añadido bien
                        sal << "INTRODUCIDO: ";

                    } else {
                        sal << "NO INTRODUCIDO: ";
                    }

                    sal << "[ " << nom << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;
                }

            } else {    // si existe ya un evento con el mismo nombre
                if(tipoDep == "DEPendiente") {
                    sal << "NO INTRODUCIDO: " << "[ " << nom << " -de-> " << eventoSup << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;

                } else {
                    sal << "NO INTRODUCIDO: " << "[ " << nom << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;

                }
            }
            
            


	    } else if (instruccion == "C") {         
            getline(ent,nom);
            getline(ent,desc);
            getline(ent,prioS);
            prio = stoi(prioS);     // convertimos el string "prioS" en un int "prio"


            obtenerVal(nom,ci,e,error);     // ponemos el evento en la variable "e"
            if(!error) {    // si existe el evento y se ha podido "obtener"
                cambiarDescripcion(e,desc);
                cambiarPrioridad(e,prio);
                actualizarVal(ci,nom,e,error); 
                
                if(!error) { // si se ha podido actualizar el evento 
                    if(existeDependiente(nom,ci)) {  // si es dependiente
                        obtenerNumDependientes(nom,ci,NumDep,error);
                        if(!error) {
                            sal << "CAMBIADO: [ " << nom << " -de-> " << eventoSup << " ;;; " << NumDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
                        } else {
                            sal <<  "NO CAMBIADO: " << nom << endl;
                        }

                    } else {

                    }

                } else {    // si NO se ha podido actualizar el evento
                    sal <<  "NO CAMBIADO: " << nom << endl;

                }

                

            } else {    // si no existe el evento o ha habido otro fallo en la obtención de este
                sal <<  "NO CAMBIADO: " << nom << endl;

            }                    


            // quizás se puede optimizar todo si se sale de la función si hay error y después pone "NO CAMBIADO: " ???????????????????????????????'


        



            

        } else if (instruccion == "O") {
            getline(ent,nom);

            // funciones para obtener la info relacionada con el nombre encontrado


            // funciones para salida.txt   



        } else if (instruccion == "E") {
            getline(ent,nom);

            bool exist = existe(nom,ci);    // lo dejo así de momento (aunque creo que se debería declarar la variable fuera)

            // funciones para salida.txt   


        } else if (instruccion == "I") {
            getline(ent,nom);

            hacerIndependiente(ci,nom);

            // funciones para salida.txt   


        } else if (instruccion == "D") {
            getline(ent,nom);
            getline(ent,eventoSup);

            hacerDependiente(ci,nom,eventoSup);


            
            // funciones para salida.txt   



        } else if (instruccion == "B") {
            getline(ent,nom);

            borrar(nom,ci); // con esto ya se borra el evento también ???????????????????????????????????????

            // funciones para salida.txt   


        } else if (instruccion == "LD") {

            // funciones para salida.txt   



        } else if (instruccion == "LT") {

            // funciones para salida.txt   



        } 
    }


    

    ent.close();
}