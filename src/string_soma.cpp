#include "string_soma.hpp"

#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
#else
	#define DEBUG_PRINT(x) 
#endif
vector<t_calc> dadosEntrada;

int soma_string(char * string_entrada ) {
	t_calc entrada;
	entrada.dado = string(string_entrada );
	DEBUG_PRINT("string_soma()");
	return calcula_resultado(entrada);
}


int calcula_resultado(t_calc &entrada){
	DEBUG_PRINT("calcula_resultado()");
	
	if ( termina_com_barra_n(entrada) )
		entrada.resultado = 0;
	else
		entrada.resultado = -1;
	
	return entrada.resultado;
	
}

bool termina_com_barra_n(t_calc &entrada){
	string aux = entrada.dado;
	/// regex ex: '1,2\n' vai pegar \n
    std::regex e ("(.*)(\\n)");
	if (std::regex_match (aux,e))
		return true;
	return false;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG