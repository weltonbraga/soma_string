#include "string_soma.hpp"

#if DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
#else
	#define DEBUG_PRINT(x) 
#endif


int soma_string(char * string_entrada ) {
	DEBUG_PRINT("string_soma()");
	t_calc entrada;
	
	entrada.dado = string(string_entrada );
	entrada.v_del.push_back(",");
	DEBUG_PRINT(entrada.dado);
	
	calcula_resultado(entrada);
	return entrada.resultado;
}

void calcula_resultado(t_calc &entrada){
	DEBUG_PRINT("calcula_resultado()");
	
	if( ausencia_barra_n_final( entrada.dado ) )
		entrada.resultado = INVALIDO;
	if( tem_espacos_em_branco( entrada.dado ) )
		entrada.resultado = INVALIDO;
	if( tem_numeros_negativos( entrada.dado ) )
		entrada.resultado = INVALIDO;
	if( tem_muitos_delimitadores_entre_numeros( entrada.dado ))
		entrada.resultado = INVALIDO;
	if( define_delimitador(entrada.dado) )
		if ( ! armazena_delimitador(entrada)) 
			entrada.resultado = INVALIDO;
		
	entrada.resultado = soma_numeros(entrada);	
}

/// verifica '\n' final e se tem apenas letras
bool ausencia_barra_n_final (string s){
    int contador = 0;
    std::smatch m;
    std::regex e ("\\n$");   // matches 
    
   // std::cout << "Target sequence: " << s << std::endl;
    DEBUG_PRINT( "Regular expression: /\\n$/" );
    DEBUG_PRINT( "The following matches and submatches were found:" );
    
    while (std::regex_search (s,m,e)) {
        for (auto x:m) {
            contador++;
           DEBUG_PRINT( x );
        }
       // std::cout << std::endl;
        s = m.suffix().str();
    }
     if (contador == 0 )
        return true;
    return false;
}

/// espaços em branco retorna INVALIDO
bool tem_espacos_em_branco(string s){
    int contador = 0;
    std::smatch m;
    std::regex e ("[ ]+");   // matches espacos em branco
    
   // std::cout << "Target sequence: " << s << std::endl;
    DEBUG_PRINT( "Regular expression: /\\n$/" );
    DEBUG_PRINT( "The following matches and submatches were found:" );
    
    while (std::regex_search (s,m,e)) {
        for (auto x:m) {
            contador++;
           //DEBUG_PRINT( x );
        }
       // std::cout << std::endl;
        s = m.suffix().str();
    }
	if (contador > 0 )
        return true;
    return false;
}

/// Numeros negativos restorna INVALIDO
bool tem_numeros_negativos(string s){
	int conta_negativos = 0;
    std::smatch m;
    std::regex e ("-\\d+");   // matches numeros negativos
    
    //DEBUG_PRINT ("Target sequence: " + s );
    DEBUG_PRINT ("Regular expression: /-\\d+/" );
    DEBUG_PRINT ("The following matches and submatches were found:");
    
    while (std::regex_search (s,m,e)) {
        for (auto x:m) {
            conta_negativos++;
            DEBUG_PRINT ( x );
        }
        //std::cout << std::endl;s
        s = m.suffix().str();
    }
   
	DEBUG_PRINT("total de negativos: " + to_string(conta_negativos));
    if (conta_negativos > 0 )
        return true;
    return false;
}

bool tem_muitos_delimitadores_entre_numeros (string s){
    
    std::string delimitador = ",";
    
    std::regex e (delimitador + "(\\n)*" + delimitador);   // matches delimitador , 0 ou + \n entre eles
    
 
    int contador = 0;
    std::smatch m;
    
   // std::cout << "Target sequence: " << s << std::endl;
    DEBUG_PRINT( "Regular expression: /,(\\n)*,/" );
    DEBUG_PRINT( "The following matches and submatches were found:" );
    
    while (std::regex_search (s,m,e)) {
        for (auto x:m) {
            contador++;
           DEBUG_PRINT( x );
        }
       // std::cout << std::endl;
        s = m.suffix().str();
    }
     if (contador > 0 )
        return true;
    return false;
}
bool define_delimitador(string s){
    int contador = 0;
    std::smatch m;
    std::regex e ("^/{2}");   // matches  '//' no inicio da string 
    
   // std::cout << "Target sequence: " << s << std::endl;
    DEBUG_PRINT( "Regular expression: /\\n$/" );
    DEBUG_PRINT( "The following matches and submatches were found:" );
    
    while (std::regex_search (s,m,e)) {
        for (auto x:m) {
            contador++;
           //DEBUG_PRINT( x );
        }
       // std::cout << std::endl;
        s = m.suffix().str();
    }
	if (contador == 1 )
        return true;
    return false;
}

bool armazena_delimitador (t_calc &entrada)
{
  string s = entrada.dado;
  string buffer;
  bool buffer_ativado = false;
 
 /// elimina delimitadores anteriores
 entrada.v_del.clear();

  for (auto str = s.begin (); str != s.end (); ++str)
    {
      if (buffer_ativado)
	buffer += (*str);
      if ((*str) == '[')
	buffer_ativado = true;
      else if ((*str) == ']')
	{
	  buffer_ativado = false;
	  buffer.pop_back ();
	  entrada.v_del.push_back (buffer);
	  buffer.clear ();
	  if ((*(str + 1)) != '[' && (*(str + 1)) != '\n')
	  {
        DEBUG_PRINT( (*(str + 1)) << " ao invez de \\n!" );
        return false;
	  }
	}

    }
  if (buffer_ativado)
    {
		DEBUG_PRINT( "Nao desligou o buffer" );
		return false;
    } else if (entrada.v_del.size() == 0) {
        DEBUG_PRINT( "Nada de delimitador" );
      return false;
    }
for (auto i : entrada.v_del)
    {
      DEBUG_PRINT( "d: " << i );
    }
  return true;
}

bool delimitador_correto(string s){
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
		DEBUG_PRINT("			"+ to_string((*it)));
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