/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#include "evento.hpp"
#include "colecInterdep.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void instruccionA(colecInterdep<string,evento> &ci, ofstream &sal, string nom, string desc, int prio, string tipoDep, string nomSup) {
    evento e;
    crearEvento(desc,prio,e); // creamos el evento con la descripción y prioridad dadas
    unsigned tamPrev = tamanyo(ci);
    if(tipoDep == "DEPendiente") {
        anyadirDependiente(ci,nom,e,nomSup);
        if(tamPrev < tamanyo(ci)) {    // si se ha añadido bien
            sal << "INTRODUCIDO: ";
        } else {
            sal << "NO INTRODUCIDO: ";
        }
        sal << "[ " << nom << " -de-> " << nomSup << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;

    } else {                
        anyadirIndependiente(ci,nom,e);

        if(tamPrev < tamanyo(ci)) {    // si se ha añadido bien
            sal << "INTRODUCIDO: ";
        } else {
            sal << "NO INTRODUCIDO: ";
        }
            sal << "[ " << nom << " ]" << " --- " << desc << " --- " << "( " << prio << " )" << endl;
        }
}

void instruccionC(colecInterdep<string,evento> &ci, ofstream &sal, string nom, string desc, unsigned prio) {
    evento e;
    bool esDep,error;
    unsigned NumDep;
    string nomSup;

    cambiarDescripcion(e,desc);
    cambiarPrioridad(e,prio);
    actualizarVal(ci,nom,e,error);   
    if(!error) { // si se ha podido actualizar el evento 
        obtenerDatos(nom,ci,e,nomSup,NumDep,esDep,error);
        if(!error && esDep) {  // si es dependiente
            sal << "CAMBIADO: [ " << nom << " -de-> " << nomSup << " ;;; " << NumDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
        } else { 
            sal << "CAMBIADO: [ " << nom << " --- " << NumDep << " ] --- " << desc << " --- ( " << prio << " )" << endl;
        }   
    } else { // si es independiente
        sal <<  "NO CAMBIADO: " << nom << endl;
    }       
}

void instruccionO(colecInterdep<string,evento> &ci, ofstream &sal, string nom) {
    evento e;
    unsigned NumDep;
    bool esDep,error;
    string nomSup;
    obtenerDatos(nom,ci,e,nomSup,NumDep,esDep,error);
    if(!error) {
        if(!error && esDep) { // si se ha obtenido el supervisor
            sal << "LOCALIZADO: " << "[ " << nom << " -de-> " << nomSup << " ;;; " << NumDep 
            << " ] --- " << descripcion(e) << " --- ( " << suPrioridad(e) << " )" << endl;
        } else { 
            sal << "LOCALIZADO: " << "[ " << nom << " --- " << NumDep << " ] --- " << descripcion(e) 
            << " --- ( " << suPrioridad(e) << " )"<< endl;
        }
    } else { // si es independiente
        sal << "NO LOCALIZADO: " << nom << endl;
    }
}

void instruccionI(colecInterdep<string,evento> &ci, ofstream &sal, string nom) {
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
}

void instruccionE(colecInterdep<string,evento> &ci, ofstream &sal, string nom) {
    if(existe(nom,ci)) {    // si existe el evento
        if(existeDependiente(nom,ci)) {
            sal << "DEPendiente: ";
        } else {
            sal << "INDEPendiente: ";
        }
    } else {    // si no existe el evento
        sal << "DESCONOCIDO: ";
    }
    sal << nom << endl;
}

void instruccionD(colecInterdep<string,evento> &ci, ofstream &sal, string nom, string nomSup) {
    if(existe(nom,ci) && existe(nomSup,ci)) {    // existen ambos eventos
        hacerDependiente(ci,nom,nomSup);
        sal << "INTENTANDO hacer depend.: ";
    } else {    // no existe alguno de los eventos (o ninguno)
        sal << "IMPOSIBLE hacer depend.: ";
    }
    sal << nom << " -de-> " << nomSup << endl;
}

void instruccionB(colecInterdep<string,evento> &ci, ofstream &sal, string nom) {
    unsigned tamPrev = tamanyo(ci);
    borrar(nom,ci);
    if(tamPrev > tamanyo(ci)){  // se ha borrado el evento de la colección
        sal << "BORRADO: " << nom << endl;
    } else {sal << "NO BORRADO: " << nom << endl;}  // no se ha borrado el evento de la colección (probablemente porque no exista)
}

void instruccionLD(colecInterdep<string,evento> &ci, ofstream &sal, string nom) {
    evento e;
    unsigned NumDep,prio;
    bool esDep,error;
    string nomSup,nomAux,desc;
    sal << "****DEPENDIENTES: " << nom << endl;
    nomAux = nom;
    obtenerDatos(nom,ci,e,nomSup,NumDep,esDep,error);
    if (!error) {
        desc = descripcion(e);
        prio = suPrioridad(e);
        if (esDep) {
            sal << "[ " << nom << " -de-> " << nomSup << " ;;; " << NumDep 
            << " ]" << " --- " << desc << " --- ( " << prio << " ) ****" << endl;   
        } else {
            sal << "[ " << nom << " --- " << NumDep << " ]" << " --- " 
            << desc << " --- ( " << prio << " ) ****" << endl;         
        }
        iniciarIterador(ci);
        unsigned i = 1;
        while (existeSiguiente(ci)) {
            if (!error) {siguienteSuperior(ci,nomSup,error);
            if (nomSup == nomAux) {
                if (!error) {siguienteIdent(ci,nom,error);}
                if (!error) {siguienteNumDependientes(ci,NumDep,error);}
                if (!error) {siguienteVal(ci,e,error);}
                if (!error) {
                    desc = descripcion(e);
                    prio = suPrioridad(e);
                    sal << "[" << i << " -> " << nom << " -de-> " << nomSup << " ;;; " << NumDep 
                        << " ]" << " --- " << desc << " --- ( " << prio << " ) ;;;;" << endl;
                    i++;
                }
                }   
            }
            avanza(ci,error);
        } 
                sal << "****FINAL dependientes -de-> " << nomAux << endl;
    } else {
        sal << "****DESCONOCIDO " << endl;
    }
}

void instruccionLT(colecInterdep<string,evento> &ci, ofstream &sal) {
    evento e;
    unsigned NumDep,prio;
    bool esDep,error;
    string nomSup,nom,desc;
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
                    siguienteSuperior(ci,nomSup,error);
                    sal << "[ " << nom << " -de-> " << nomSup << " ;;; " << NumDep 
                    << " ]" << " --- " << desc << " --- ( " << prio << " )" << endl;
                } else if (!error){
                    sal << "[ " << nom << " --- " << NumDep << " ]" << " --- " 
                    << desc << " --- ( " << prio << " )" << endl;
                }
                avanza(ci,error);
            }
            sal << "-----" << endl;
}

int main() {
 
    colecInterdep<string,evento> ci;

    crear(ci);  // creamos la colección vacía

    ifstream ent; 
    ofstream sal;
    ent.open("entradaEjemplo.txt"); // abrimos el fichero de entrada
    if(!ent.is_open()) {
        cerr << "No se pudo abrir el archivo entrada." << endl;
        return 1;
    }

    sal.open("salidaPrueba.txt"); // abrimos el fichero de salida
    if(!sal.is_open()) {
        cerr << "No se pudo abrir el archivo salida." << endl;
        return 1;
    }

    string instruccion, salto; 
    string nom;     // nombre
    string desc;    // descripción
    string prioS;   // prioridad (string)
    int prio;       // prioridad (int)
    string tipoDep;  // tipo de dependencia (dep. o ind.)
    string nomSup;   // nombre del evento del cual depende el evento que se añade ("vacío" si es independiente)

    while (ent >> instruccion) { 

	    getline(ent,salto);   
         
	    if (instruccion == "A") {         
            
            getline(ent,nom);
            getline(ent,desc);
            getline(ent,prioS);
            prio = stoi(prioS);     // convertimos el string "prioS" en un int "prio"
            getline(ent,tipoDep);
            getline(ent,nomSup);
            instruccionA(ci,sal,nom,desc,prio,tipoDep,nomSup);
            

	    } else if (instruccion == "C") {         
            getline(ent,nom);
            getline(ent,desc);
            getline(ent,prioS);
            prio = stoi(prioS);     // convertimos el string "prioS" en un int "prio"
            instruccionC(ci,sal,nom,desc,prio);
                       
        } else if (instruccion == "O") {
            getline(ent,nom);
            instruccionO(ci,sal,nom);
            
        } else if (instruccion == "E") {
            getline(ent,nom);
            instruccionE(ci,sal,nom);

        } else if (instruccion == "I") {
            getline(ent,nom);
            instruccionI(ci,sal,nom);

        } else if (instruccion == "D") {
            getline(ent,nom);
            getline(ent,nomSup);
            instruccionD(ci,sal,nom,nomSup);

        } else if (instruccion == "B") {
            getline(ent,nom);
            instruccionB(ci,sal,nom);

        } else if (instruccion == "LD") {
            getline(ent,nom);
            instruccionLD(ci,sal,nom);
            
        } else if (instruccion == "LT") {
            instruccionLT(ci,sal);
           
        } 
    }

    ent.close();
    sal.close();
}