/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#include "tareas.hpp"
#include "colecInterdep.hpp"
#include <iostream>
#include <string>

using namespace std;

// INSTRUCCIÓN A: Añadir tarea
// Lógica adaptada: Pregunta si tiene prerrequisitos.
void instruccionA(colecInterdep<string,tareas> &ci) {
    string nom, desc, uni, resp, nomPrerreq;
    double esti;
    tareas t;

    cout << "Introduce nombre de la nueva tarea: "; 
    cin >> ws; getline(cin, nom);
    
    cout << "Introduce descripcion: "; 
    getline(cin, desc);
    
    cout << "Introduce unidad de tiempo: "; 
    getline(cin, uni);
    
    cout << "Introduce tiempo estimado: "; 
    cin >> esti;

    // Intentamos crear la tarea localmente (valida si tiempo >= 0)
    if (crearTarea(t, nom, desc, uni, esti)) {
        unsigned tamPrev = tamanyo(ci);
        
        cout << "¿Tiene esta tarea algun prerrequisito? (S/N): ";
        cin >> ws; getline(cin, resp);

        if (resp == "S" || resp == "s") {
            cout << "Introduce el nombre de la tarea prerrequisito: ";
            getline(cin, nomPrerreq);
            
            // Añadimos 'nom' como dependiente de 'nomPrerreq'
            anyadirDependiente(ci, nom, t, nomPrerreq);
            
            if (tamPrev < tamanyo(ci)) {
                cout << "INTRODUCIDO: [ " << nom << " ] (Prerrequisito: " << nomPrerreq << ")" << endl;
            } else {
                cout << "NO INTRODUCIDO: Error (quizas no existe el prerrequisito o ID repetido)." << endl;
            }
        } else {
            // No tiene prerrequisitos -> Es independiente
            anyadirIndependiente(ci, nom, t);
            
            if (tamPrev < tamanyo(ci)) {
                cout << "INTRODUCIDO: [ " << nom << " ] (Sin prerrequisitos)" << endl;
            } else {
                cout << "NO INTRODUCIDO: Ya existe una tarea con ese nombre." << endl;
            }
        }
    } else {
        cout << "NO INTRODUCIDO: Tiempo estimado invalido (no puede ser negativo)." << endl;
    }
}

// INSTRUCCIÓN C: Modificar tarea
void instruccionC(colecInterdep<string,tareas> &ci) {
    string nom, desc, uni;
    double esti, empl;
    tareas t;

    cout << "Introduce nombre de la tarea a modificar: ";
    cin >> ws; getline(cin, nom);
    
    cout << "Nueva descripcion: "; 
    getline(cin, desc);
    cout << "Nueva unidad: "; 
    getline(cin, uni);
    cout << "Nuevo tiempo estimado: "; 
    cin >> esti;
    cout << "Nuevo tiempo empleado: "; 
    cin >> empl;

    // Usamos el constructor para validar y empaquetar los datos
    if (crearTarea(t, nom, desc, uni, esti)) {
        if (cambiarTiempoEmpleado(t, empl)) {
            // Actualizamos en la colección
            if (actualizarVal(ci, nom, t)) {
                cout << "CAMBIADO CORRECTAMENTE: " << nom << endl;
            } else {
                cout << "NO CAMBIADO: La tarea no existe." << endl;
            }
        } else {
            cout << "NO CAMBIADO: Tiempo empleado negativo." << endl;
        }
    } else {
        cout << "NO CAMBIADO: Tiempo estimado negativo." << endl;
    }
}

// INSTRUCCIÓN O: Consultar tarea
void instruccionO(colecInterdep<string,tareas> &ci) {
    string nom;
    cout << "Introduce nombre a consultar: ";
    cin >> ws; getline(cin, nom);

    tareas t;
    string nomPrerreq; // Identificador del supervisor (prerrequisito)
    unsigned NumDep;   // Cuántas tareas dependen de esta
    bool tienePrerreq; // esDep

    if (obtenerDatos(nom, ci, t, nomPrerreq, NumDep, tienePrerreq)) {
        string n, d, u; double te, tm;
        obtenerDatos(t, n, d, u, te, tm);

        cout << "------------------------------------------------" << endl;
        cout << "Tarea: " << n << endl;
        cout << "Descripcion: " << d << endl;
        cout << "Tiempos: " << te << " est / " << tm << " real (" << u << ")" << endl;
        
        if (tienePrerreq) {
            cout << "PRERREQUISITO: Esta tarea depende de '" << nomPrerreq << "'" << endl;
        } else {
            cout << "PRERREQUISITO: Ninguno (puede iniciarse ya)." << endl;
        }

        if (NumDep > 0) {
            cout << "BLOQUEO: Esta tarea es prerrequisito para otras " << NumDep << " tarea(s)." << endl;
        }
        cout << "------------------------------------------------" << endl;
    } else {
        cout << "NO LOCALIZADO: La tarea no existe." << endl;
    }
}

// INSTRUCCIÓN E: Consultar estado (Tiene prerrequisito o no)
void instruccionE(colecInterdep<string,tareas> &ci) {
    string nom;
    cout << "Introduce nombre: ";
    cin >> ws; getline(cin, nom);

    bool tienePrerreq;
    // existe devuelve en 'tienePrerreq' si es dependiente (tiene supervisor)
    if (existe(nom, ci, tienePrerreq)) {
        if (tienePrerreq) cout << "ESTADO: Dependiente (Tiene prerrequisito)." << endl;
        else              cout << "ESTADO: Independiente (No tiene prerrequisito)." << endl;
    } else {
        cout << "DESCONOCIDO: La tarea no existe." << endl;
    }
}

// INSTRUCCIÓN I: Quitar prerrequisito (Hacer independiente)
void instruccionI(colecInterdep<string,tareas> &ci) {
    string nom;
    cout << "Introduce nombre de la tarea a liberar de prerrequisito: ";
    cin >> ws; getline(cin, nom);

    bool tienePrerreq;
    if (existe(nom, ci, tienePrerreq)) {
        if (!tienePrerreq) {
            cout << "AVISO: La tarea ya no tenia prerrequisitos." << endl;
        } else {
            hacerIndependiente(ci, nom);
            cout << "EXITO: Tarea '" << nom << "' ahora no tiene prerrequisitos." << endl;
        }
    } else {
        cout << "ERROR: La tarea no existe." << endl;
    }
}

// INSTRUCCIÓN D: Establecer prerrequisito
// t1 pasa a ser prerrequisito de t2 ==> t2 depende de t1
void instruccionD(colecInterdep<string,tareas> &ci) {
    string t1, t2;
    cout << "Introduce la tarea PRERREQUISITO (T1): ";
    cin >> ws; getline(cin, t1);
    cout << "Introduce la tarea que DEPENDERA de T1 (T2): ";
    getline(cin, t2);

    bool dummy;
    // Verificamos existencia
    if (existe(t1, ci, dummy) && existe(t2, ci, dummy)) {
        // En colecInterdep: hacerDependiente(ci, hijo, padre)
        // Hijo = t2 (la que depende), Padre = t1 (el prerrequisito)
        hacerDependiente(ci, t2, t1);
        cout << "PROCESADO: '" << t1 << "' es ahora prerrequisito de '" << t2 << "'" << endl;
    } else {
        cout << "IMPOSIBLE: Alguna de las tareas no existe." << endl;
    }
}

// INSTRUCCIÓN B: Borrar
void instruccionB(colecInterdep<string,tareas> &ci) {
    string nom;
    cout << "Introduce nombre a borrar: ";
    cin >> ws; getline(cin, nom);

    unsigned tamPrev = tamanyo(ci);
    borrar(nom, ci);
    
    if (tamPrev > tamanyo(ci)) {
        cout << "BORRADO: " << nom << endl;
    } else {
        cout << "NO BORRADO: " << nom << " (No existe o es prerrequisito de otras)." << endl;
    }
}

// INSTRUCCIÓN LD: Listar tareas que tienen a X como prerrequisito
void instruccionLD(colecInterdep<string,tareas> &ci) {
    string nom;
    cout << "Introduce nombre de la tarea prerrequisito: ";
    cin >> ws; getline(cin, nom);

    tareas t;
    string nomSup;
    unsigned NumDep;
    bool tienePrerreq;

    if (obtenerDatos(nom, ci, t, nomSup, NumDep, tienePrerreq)) {
        cout << "**** TAREAS QUE TIENEN COMO PRERREQUISITO A: " << nom << " ****" << endl;
        
        // Iterador para recorrer y buscar hijos
        iniciarIterador(ci);
        string idIter, idPrerreqIter;
        tareas tIter;
        unsigned numDepIter;
        bool tienePrerreqIter;
        int cont = 1;

        while (existeSiguiente(ci)) {
            if (siguienteYavanza(ci, idIter, numDepIter, tIter, tienePrerreqIter, idPrerreqIter)) {
                // Si la tarea iterada (idIter) tiene prerrequisito Y ese prerrequisito es 'nom'
                if (tienePrerreqIter && idPrerreqIter == nom) {
                    string n, d, u; double te, tm;
                    obtenerDatos(tIter, n, d, u, te, tm);
                    cout << "[" << cont << "] " << idIter << " --- " << d << endl;
                    cont++;
                }
            }
        }
        cout << "**** FIN LISTADO ****" << endl;
    } else {
        cout << "**** ERROR: Tarea desconocida ****" << endl;
    }
}

// INSTRUCCIÓN LT: Listado Total
void instruccionLT(colecInterdep<string,tareas> &ci) {
    cout << "----- LISTADO COMPLETO (" << tamanyo(ci) << " tareas) -----" << endl;
    
    iniciarIterador(ci);
    string nom, nomPrerreq;
    tareas t;
    unsigned NumDep; // Num tareas para las que 'nom' es prerrequisito
    bool tienePrerreq;

    while (existeSiguiente(ci)) {
        if (siguienteYavanza(ci, nom, NumDep, t, tienePrerreq, nomPrerreq)) {
            string n, d, u; double te, tm;
            obtenerDatos(t, n, d, u, te, tm);

            cout << "Tarea: [" << nom << "]";
            if (tienePrerreq) {
                cout << " (Prerrequisito: " << nomPrerreq << ")";
            } else {
                cout << " (Sin prerrequisitos)";
            }
            
            // Si NumDep > 0, significa que esta tarea bloquea a otras
            if (NumDep > 0) {
                cout << " -> Es prerrequisito de " << NumDep << " tareas.";
            }
            cout << endl;
        }
    }
    cout << "-----------------------------------------------" << endl;
}

int main() {
    colecInterdep<string, tareas> planificador;
    crear(planificador);

    int opcion;
    do {
        cout << "\n=== GESTOR DE PROYECTOS ===" << endl;
        cout << "1. Anadir tarea" << endl;
        cout << "2. Establecer prerrequisito (T1 es necesario para T2)" << endl;
        cout << "3. Quitar prerrequisito a una tarea" << endl;
        cout << "4. Actualizar datos de tarea" << endl;
        cout << "5. Consultar detalle de tarea" << endl;
        cout << "6. Borrar tarea" << endl;
        cout << "7. Listar todas" << endl;
        cout << "8. Salir" << endl;
        cout << "Opcion: ";
        
        cin >> opcion;

        // Limpieza básica de errores de entrada numérica
        if (cin.fail()) {
            cin.clear(); 
            string dummy; getline(cin, dummy);
            opcion = 0;
        }

        switch(opcion) {
            case 1: instruccionA(planificador); break;
            case 2: instruccionD(planificador); break;
            case 3: instruccionI(planificador); break;
            case 4: instruccionC(planificador); break;
            case 5: instruccionO(planificador); break;
            case 6: instruccionB(planificador); break;
            case 7: instruccionLT(planificador); break;
            case 8: cout << "Cerrando..." << endl; break;
            default: cout << "Opcion no valida." << endl;
        }

    } while (opcion != 8);

    return 0;
}