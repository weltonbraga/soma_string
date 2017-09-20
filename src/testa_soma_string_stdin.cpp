/*! 
 *  \brief     Trabalho 1 - MP
 *  \details   Métodos de Programação - 201600
 *  \author    Welton de Almeida Braga - 16/0148880
 *  \date      20-09-2017
 */
#include "string_soma.hpp"

//#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
	#define DEBUG_PRINT(x) 
#endif

int main(){

	char str[] = "1,2\n";
	char * entrada = str;
	int r = soma_string(entrada);
	string saida(str);
	DEBUG_PRINT( saida + "resultado:" + std::to_string(r));
	return 0;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG