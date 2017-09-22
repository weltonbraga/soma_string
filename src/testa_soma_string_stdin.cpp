/*! 
 *  \brief     Trabalho 1 - MP
 *  \details   Métodos de Programação - 201600
 *  \author    Welton de Almeida Braga - 16/0148880
 *  \date      20-09-2017
 */
/// includes 
#include "string_soma.hpp"

#if DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
	#define DEBUG_PRINT(x) 
#endif

int main(int argc, char *argv[]){

	if ( argc < 3 ){
		cout << "Uso correto: " << argv[0] << " entrada.txt saida.txt" << endl; 
	} else {
		const string arqEntrada = argv[1];
		const string arqSaida = argv[2];
		
		RUN (arqEntrada, arqSaida);
	}
	return 0;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG