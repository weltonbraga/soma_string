#include "string_soma.hpp"

//#define DEBUG
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
	
	if ( termina_com_barra_n(entrada) ){
		soma_numeros(entrada);
	}else {
		entrada.resultado = INVALIDO;
	}
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

void soma_numeros (t_calc &entrada){
	string s = entrada.dado;
	smatch m;
	regex e ("\\d+");
	int qtd=0;
	int soma = 0;
	while (regex_search (s,m,e)) {
		for (auto x:m){
			/// converte string pra int e soma
			soma += stoi(x);
			qtd++;
		}		
		s = m.suffix().str();
	}
	DEBUG_PRINT("m: "+std::to_string(qtd) );
	if(qtd < 1 || qtd > 3)
		entrada.resultado = INVALIDO;
	else
		entrada.resultado = soma;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG