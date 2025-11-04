#include "evento.hpp"
#include "colecInterdep.hpp"
using namespace std;

int main() {
    colecInterdep<int,char> ci;
    int id,idSup;
    char v;
    bool error,esDep;
    unsigned NumDep;
      crear(ci);
      tamanyo(ci);
      esVacia(ci);
      existe( id,ci);
      existeDependiente( id,ci);
      existeIndependiente( id,ci);
      anyadirIndependiente(ci,  id,  v);
      anyadirDependiente(ci,  id,  v,  idSup);
      hacerDependiente(ci,  id,  idSup);
      hacerIndependiente(ci,  id);
      actualizarVal(ci,  id,  v,  error);
      obtenerVal( id,ci,  v,  error);
      obtenerSupervisor( id, ci,  idSup,  error);
      obtenerNumDependientes( id, ci,  NumDep,  error);
      borrar( id,  ci);
      iniciarIterador( ci);
      existeSiguiente(ci);
      siguienteIdent(ci,  id,  error);
      siguienteVal(ci,  v,  error);
      siguienteDependiente(ci,  esDep,  error);
      siguienteSuperior(ci,  idSup,  error);
      siguienteNumDependientes(ci,  NumDep,  error);
      avanza( ci,  error);
    return 0;
}