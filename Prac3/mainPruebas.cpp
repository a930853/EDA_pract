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
    unsigned NumDep, prio; // número de dependientes
    string tipoDep;  // tipo de dependencia (dep. o ind.)
    string eventoSup;   // nombre del evento del cual depende el evento que se añade ("vacío" si es independiente)
    bool esDep,error;     // error en funciones parciales

    while (ent >> instruccion) { 

	    getline(ent,salto);   
         
	    if (instruccion == "A") {         
            
            getline(ent,nom);
            getline(ent,desc);
            getline(ent,prioS);
            prio = stoi(prioS);     // convertimos el string "prioS" en un int "prio"
            getline(ent,tipoDep);
            getline(ent,eventoSup);

            if(!existe(nom,ci)) { // si NO existe el evento
                crearEvento(desc,prio,e); // creamos el evento con la descripción y prioridad dadas


                if(tipoDep == "DEPendiente") {
                    anyadirDependiente(ci,nom,e,eventoSup);

                    if(existeDependiente(nom,ci)) {    // si se ha añadido bien
                        sal << "INTRODUCIDO: ";

                    } else {
                        sal << "NO INTRODUCIDO: ";
                    }

                    sal << "[ " << nom << " -de-> " << eventoSup << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;

                } else {                
                    anyadirIndependiente(ci,nom,e);

                    if(existeIndependiente(nom,ci)) {    // si se ha añadido bien
                        sal << "INTRODUCIDO: ";

                    } else {
                        sal << "NO INTRODUCIDO: ";
                    }

                    sal << "[ " << nom << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;
                }
            } else {    // si ya existe el evento
                sal << "NO INTRODUCIDO: ";
                if(tipoDep == "DEPendiente") {
                    sal << "[ " << nom << " -de-> " << eventoSup << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;
                } else {
                    sal << "[ " << nom << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;
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
                    obtenerNumDependientes(nom,ci,NumDep,error);
                    if(!error) { // ha obtenido NumDep
                        if(existeDependiente(nom,ci)) {  // si es dependiente
                            obtenerSupervisor(nom,ci,eventoSup,error);
                            if(!error) { // si se ha obtenido el supervisor
                                sal << "CAMBIADO: [ " << nom << " -de-> " << eventoSup << " ;;; " << NumDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
                            } else { // si NO se ha obtenido el supervisor
                                sal <<  "NO CAMBIADO: " << nom << endl;
                            }   
                        } else { // si es independiente
                                sal << "CAMBIADO: [ " << nom << " --- " << NumDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
                        }
                    } else { // si NO ha obtenido NumDep
                        sal <<  "NO CAMBIADO: " << nom << endl;
                    }
                } else {    // si NO se ha podido actualizar el evento
                    sal <<  "NO CAMBIADO: " << nom << endl;

                }
            } else {    // si no existe el evento o ha habido otro fallo en la obtención de este
                sal <<  "NO CAMBIADO: " << nom << endl;
            }                    



        } else if (instruccion == "O") {
            getline(ent,nom);
            
            if(existe(nom,ci)) { // si existe
                obtenerNumDependientes(nom,ci,NumDep,error);
                if(!error) { // ha obtenido NumDep
                    obtenerVal(nom,ci,e,error); 
                    if(!error) {    // ha podido obtener el evento
                        if(existeDependiente(nom,ci)) { // si es dependiente
                            obtenerSupervisor(nom,ci,eventoSup,error);
                            if(!error) { // si se ha obtenido el supervisor
                                sal << "LOCALIZADO: " << "[ " << nom << " -de-> " << eventoSup << " ;;; " << NumDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
                            } else { // si NO se ha obtenido el supervisor
                                sal << "NO LOCALIZADO: " << nom << endl;
                            }
                        } else { // si es independiente
                            sal << "LOCALIZADO: " << "[ " << nom << " --- " << NumDep << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )"<< endl;
                        }

                    } else {    // NO ha podido obtener el evento
                        sal << "NO LOCALIZADO: " << nom << endl;
                    }
                } else { // si NO ha obtenido NumDep
                    sal << "NO LOCALIZADO: " << nom << endl;
                }
            } else { // si no existe
                sal << "NO LOCALIZADO: " << nom << endl;
            }



        } else if (instruccion == "E") {
            getline(ent,nom);

            if(existe(nom,ci)) {
                if(existeDependiente(nom,ci)) {
                    sal << "DEPendiente: ";
                } else {
                    sal << "INDEPendiente: ";
                }
            } else {
                sal << "DESCONOCIDO: ";
            }
            sal << nom << endl;




        } else if (instruccion == "I") {
            getline(ent,nom);

            if(existe(nom,ci)) { // si existe el evento
                if(existeIndependiente(nom,ci)) { // era ya independiente
                    sal << "YA ERA INDepend.: ";
                } else {    // NO era independiente
                    hacerIndependiente(ci,nom);
                    sal << "INDEPENDIZADO: ";
                }
            } else {    // si NO existe el evento
                sal << "NO INDEPENDIZADO: ";
            }
            sal << nom << endl;


        } else if (instruccion == "D") {
            getline(ent,nom);
            getline(ent,eventoSup);

            if(existe(nom,ci) && existe(eventoSup,ci)) {    // existen ambos eventos
                hacerDependiente(ci,nom,eventoSup);
                sal << "INTENTANDO hacer depend.: ";
            } else {    // no existe alguno de los eventos (o ninguno)
                sal << "IMPOSIBLE hacer depend.: ";
            }
            sal << nom << " -de-> " << eventoSup << endl;




        } else if (instruccion == "B") {
            getline(ent,nom);
            if (existe(nom,ci)) {
                borrar(nom,ci);
                if(!existe(nom,ci)){
                    sal << "BORRADO: " << nom << endl;
                } else {sal << "NO BORRADO: " << nom << endl;}
            } else {sal << "NO BORRADO: " << nom << endl;} 



        } else if (instruccion == "LD") {
            getline(ent,nom);
            sal << "****DEPENDIENTES: " << nom << endl;
            if (existe(nom,ci)) {
                string nomAux = nom;
                obtenerVal(nom,ci,e,error);
                if (!error) {
                    desc = descripcion(e);
                    prio = suPrioridad(e);
                }
                if (!error) {obtenerNumDependientes(nom,ci,NumDep,error);}
                if( existeIndependiente(nom,ci) && !error) {
                        sal << "[ " << nom << " --- " << NumDep << " ]" << " --- " 
                        << desc << " --- ( " << prio << " )" << endl;
                        
                } else if (!error){
                        obtenerSupervisor(nom,ci,eventoSup,error);
                        if(!error) {
                            sal << "[ " << nom << " -de-> " << eventoSup << " ;;; " << NumDep 
                            << " ]" << " --- " << desc << " --- ( " << prio << " )" << endl;
                        }
                }
                iniciarIterador(ci);
                error = false;
                while (existeSiguiente(ci)) {
                    if(!error) {siguienteDependiente(ci,esDep,error);}
                    if (esDep && !error) {
                        if(!error) {siguienteIdent(ci,nom,error);}
                        if(!error) {siguienteNumDependientes(ci,NumDep,error);}
                        if(!error) {siguienteVal(ci,e,error);}
                        if (!error) {
                            desc = descripcion(e);
                            prio = suPrioridad(e);
                            siguienteSuperior(ci,eventoSup,error);
                        } if (!error) {
                            sal << "[ " << nom << " -de-> " << eventoSup << " ;;; " << NumDep 
                            << " ]" << " --- " << desc << " --- ( " << prio << " )" << endl;
                        }
                    }
                    avanza(ci,error);
                } 
                sal << "****FINAL dependientes -de-> " << nomAux << endl;
                }
            else {sal << "****DESCONOCIDO: " << endl;}


            
        } else if (instruccion == "LT") {

            sal << "-----LISTADO: " << tamanyo(ci) << endl;
            iniciarIterador(ci);
            error = false;
            while (existeSiguiente(ci) && !error) {
                if(!error) {siguienteDependiente(ci,esDep,error);}
                if(!error) {siguienteIdent(ci,nom,error);}
                if(!error) {siguienteNumDependientes(ci,NumDep,error);}
                if(!error) {siguienteVal(ci,e,error);
                    desc = descripcion(e);
                    prio = suPrioridad(e);
                }
                if (esDep && !error) {
                    siguienteSuperior(ci,eventoSup,error);
                    sal << "[ " << nom << " -de-> " << eventoSup << " ;;; " << NumDep 
                    << " ]" << " --- " << desc << " --- ( " << prio << " )" << endl;
                } else if (!error){
                    sal << "[ " << nom << " --- " << NumDep << " ]" << " --- " 
                    << desc << " --- ( " << prio << " )" << endl;
                }
                avanza(ci,error);
            }
            sal << "-----" << endl;
        } 
    }


    

    ent.close();
}