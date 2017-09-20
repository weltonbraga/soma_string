#include "string_soma.hpp"

#if DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
#else
	#define DEBUG_PRINT(x) 
#endif


int soma_string(char * string_entrada ) {
	DEBUG_PRINT("\n\n	***		string_soma()\n\n");
	t_calc entrada;
	
	entrada.dado = string(string_entrada );
	DEBUG_PRINT( " >>>>>>>>> " << entrada.dado << " <<<<<<<<<<<<<");
	
	calcula_resultado(entrada);
	DEBUG_PRINT("\n\n	***		fim string_soma()\n\n");
	return entrada.resultado;
}

void calcula_resultado(t_calc &entrada){
	DEBUG_PRINT("calcula_resultado()");
	
	if( ausencia_barra_n_final( entrada.dado ) )
		entrada.resultado = INVALIDO;
	else if( tem_espacos_em_branco( entrada.dado ) )
		entrada.resultado = INVALIDO;
	else if( tem_numeros_negativos( entrada.dado ) )
		entrada.resultado = INVALIDO;
	else if( tem_muitos_delimitadores_entre_numeros( entrada ))
		entrada.resultado = INVALIDO;
	else if( define_delimitador(entrada.dado) ) 
	{
		if ( ! armazena_delimitador(entrada)) 
			entrada.resultado = INVALIDO;
	}
	else if( mais_de_3_num_na_linha(entrada) )
		entrada.resultado = INVALIDO;
	else if( sem_delimitador_entre_numeros(entrada.dado) )
		entrada.resultado = INVALIDO;
	else if(delimitador_incorreto(entrada) )
		entrada.resultado = INVALIDO;
	else
		entrada.resultado = soma_numeros(entrada);	
}

/// verifica '\n' final e se tem apenas letras
bool ausencia_barra_n_final (string s){
	DEBUG_PRINT( "\n	###### fun ausencia_barra_n_final \n" );
    int contador = 0;
    std::smatch m;
    std::regex e ("\\n$");   // matches 
    
    DEBUG_PRINT( "Target sequence: " << s );
    DEBUG_PRINT( "Regular expression: /\\n$/" );
    
    
    while (std::regex_search (s,m,e)) {
        for (auto x:m) {
            contador++;
           DEBUG_PRINT( x );
        }
       // std::cout << std::endl;
        s = m.suffix().str();
    }
	DEBUG_PRINT( "contador:" << contador );
	DEBUG_PRINT( "\n	###### FIM FIM  fun ausencia_barra_n_final \n" );
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

bool tem_muitos_delimitadores_entre_numeros (t_calc &entrada){
    //std::cout << "f: tem_muitos_delimitadores_entre_numeros\n";
	string s_aux ("(");//" (,|;)(\\n)*(,|;)
	
	string s_aux2 ("(\\n)*");

	for (auto i : entrada.v_del)
	{
	  s_aux += i + "|";
	}
	s_aux.pop_back ();
	
	s_aux += ")";
	
	s_aux2 = s_aux + s_aux2 + s_aux;
	
	
	//std::cout << s_aux2 << std::endl;
 
    int contador = 0;
    std::smatch m;
	std::regex e ( s_aux2 );   // matches delimitador
	string s = entrada.dado;
    
   // std::cout << "Target sequence: " << s << std::endl;
    DEBUG_PRINT( "Regular expression: /"<< s_aux <<"/" );
    //DEBUG_PRINT( "The following matches and submatches were found:" );
    
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
	if (contador == 1 ){
		//armazena_delimitador(entrada);
        return true;
	}
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
	  /// eveita buffer vazio quando a string for "//[]"
	  if ( buffer.size() == 0)
			return false;
			
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
	/**************/
	string s_aux ("(\\d+(?<todos_delimitadores>");

	for (auto i : entrada.v_del)
	{
	  s_aux += i + "|";
	}
	s_aux.pop_back ();
	
	s_aux += ")){3,}\\d+\\n";
	
	DEBUG_PRINT( s_aux );
 
	/**************/
  return true;
}

bool mais_de_3_num_na_linha (t_calc &entrada){
	//cout << "mais_de_3_num_na_linha\n";
	string s_aux ("(\\d+("); // (\d+(?<todos_delimitadores>,)){3,}\d+\\n

	for (auto i : entrada.v_del)
	{
	  s_aux += i + "|";
	}
	s_aux.pop_back ();
	
	s_aux += ")){3,}\\d+\n";
	
	//std::cout << s_aux << std::endl;
	
	int contador = 0;
    smatch m;
	
	//cout << "aki\n\n";
	//string s_aux2 ("(\\d+(?<todos_delimitadores>,)){3,}\\d+\\n");
	//string s_aux2 ("(A candy)?(?(1) is true| is false)");
	//std::cout << s_aux2 << std::endl;
    regex e ( s_aux );   // matches  '//' no inicio da string 
	///cout << "aki\n\n";
    string s = entrada.dado;
   // std::cout << "Target sequence: " << s << std::endl;
    //DEBUG_PRINT( "Regular expression: /\\n$/" );
   // DEBUG_PRINT( "The following matches and submatches were found:" );
    
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
bool sem_delimitador_entre_numeros (string s){
	
int contador = 0;
    std::smatch m;
    std::regex e ("\\d+(\\n)+\\d+");   // matches  '//' no inicio da string 
    
   // std::cout << "Target sequence: " << s << std::endl;
    DEBUG_PRINT( "Regular expression: /\\d+(\\n)+\\d+" );
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
/// Testa se os delimitadores usados são os corretos
bool delimitador_incorreto(t_calc &entrada){
	DEBUG_PRINT(" \n\n #### delimitador_incorreto \n");
	string s = entrada.dado;
	string buffer;
	bool buffer_ativado = false;
	bool travado = true;
	std::locale loc;
	DEBUG_PRINT( "entrada: " << s );
	for (auto str = s.begin (); str != s.end (); ++str)
	{
		
		if (!isdigit((*str),loc) && (*str) != '\n' && !travado){
			buffer_ativado = true;
			DEBUG_PRINT( "b ativado: " << (*str) );
		} 
		else if( isdigit((*str),loc) && (*str) != '\n' ){
			travado = false;
		}
		else if (buffer_ativado && isdigit((*str),loc) && !travado)
		{
			buffer_ativado = false;
			DEBUG_PRINT( "b desativado: " << (*str) );
			std::vector<string>::iterator it;
			it = find (entrada.v_del.begin(), entrada.v_del.end(), buffer);
			if (it != entrada.v_del.end()){
				DEBUG_PRINT( "Element found in myvector: " << *it );
				buffer.clear();
			}else{
				DEBUG_PRINT("b >" <<buffer <<"< Element not found in myvector" );
				for (std::vector<string>::iterator i = entrada.v_del.begin(); i != entrada.v_del.end(); ++i)
					DEBUG_PRINT("v: " <<  *i );
				DEBUG_PRINT( "len v_del: "<< entrada.v_del.size() <<"fim v_del" );
				return true;
			}
		  
		} else {
			if( (*str) == '/' ){
				if((*(str+1)) != '/' ){
					armazena_delimitador(entrada);
					//travado = false;
				}
			} else if( (*str) == '\n' )
				travado = false;
		}
		
		if (buffer_ativado){
			buffer += (*str);
			DEBUG_PRINT( "buffer +=" << (*str) );
		}
    }
	DEBUG_PRINT(" ###  delimitador chegou no fim ok");
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