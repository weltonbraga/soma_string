#include "string_soma.hpp"

#if DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
#else
	#define DEBUG_PRINT(x) 
#endif
vector<t_calc> dadosEntrada;

int soma_string(char * string_entrada ) {
	DEBUG_PRINT("string_soma()");
	t_calc entrada;
	entrada.dado = string(string_entrada );
	DEBUG_PRINT(entrada.dado);
	calcula_resultado(entrada);
	return entrada.resultado;
}

void calcula_resultado(t_calc &entrada){
	DEBUG_PRINT("calcula_resultado()");
	
	if ( !termina_com_barra_n(entrada) )
		entrada.resultado = INVALIDO;
	else if( espaco_no_final(entrada) )
		entrada.resultado = INVALIDO;
	else 
		entrada.resultado = soma_numeros(entrada);	
}
/// verifica '\n' final e se tem apenas letras
bool termina_com_barra_n(t_calc &entrada){
	string aux = entrada.dado;
	/// regex ex: '1,2\n' vai pegar \n
    std::regex e ("([0-9,]*)(\\n)");
	if (std::regex_match (aux,e))
		return true;
	DEBUG_PRINT(" Barra N FALSO");
	return false;
}

bool espaco_no_final(t_calc &entrada){
	string aux = entrada.dado;
	/// regex ex: '1,2\n' vai pegar \n
    std::regex e ("[ ]+");
	if (std::regex_match (aux,e)){
		return true;
		DEBUG_PRINT("Espaco FALSO");
	}
	return false;
}

int soma_numeros (t_calc &entrada){
	string s = entrada.dado;
	smatch m;
	regex e ("-?\\d+");
	int soma = 0;
	std::vector <int> valores;
	while (regex_search (s,m,e)) {
		for (auto x:m){
			valores.push_back(stoi(x));
		}		
		s = m.suffix().str();
	}
		
	for (std::vector<int>::iterator it=valores.begin();  it != valores.end(); it++){
		DEBUG_PRINT("			"+ std::to_string((*it)));
		if ((*it) < 0){
			soma = INVALIDO;
			break;
		}else if ((*it) <= 1000)
			soma += (*it);
	}
	if(valores.size() < 1 || valores.size() > 3)
		return INVALIDO;
	else
		return soma;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG