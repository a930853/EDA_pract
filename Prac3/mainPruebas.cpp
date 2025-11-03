/* Javier Martínez Virto 930853
* Víctor Marteles Martínez 928927
*/

#include "evento.hpp"
#include "colecInterdep.hpp"
using namespace std;

int main() {
    colecInterdep<int,char> ci;
    crear(ci);
    anyadirIndependiente(ci,4,'c');
    anyadirIndependiente(ci,5,'f');
    anyadirIndependiente(ci,2,'a');
    anyadirIndependiente(ci,5,'f');
    return 0;
}