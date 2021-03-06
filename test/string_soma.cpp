/*! 
 *  \brief     Trabalho 1 - MP
 *  \details   Métodos de Programação - 201600
 *  \author    Welton de Almeida Braga - 16/0148880
 *  \date      20-09-2017
 */
/// includes
#include "string_soma.hpp"

//#define DEBUG
#if DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
#else
	#define DEBUG_PRINT(x) 
#endif


int soma_string(char * string_entrada ) {
	//cout <<"\n\n	***		string_soma()\n\n";
	t_calc entrada;
	
	entrada.dado = string(string_entrada );
	//cout << "\n>>>>>>>> **" << entrada.dado << "** <<<<<<<<<<<<<\n\n";
	
	calcula_resultado(entrada);
	DEBUG_PRINT("\n\n	***		fim string_soma()\n\n");
	return entrada.resultado;
}

void calcula_resultado(t_calc &entrada){
	//cout << "calcula_resultado:";
	//cout << ": ("<< entrada.dado << ")"<< endl;
	if( define_delimitador(entrada.dado) ) 
	{
		if ( ! armazena_delimitador(entrada)) {
			//cout << "6 <=" << endl;
			entrada.resultado = INVALIDO;
		}
	}
	
	if( ausencia_barra_n_final( entrada.dado ) ){
		//cout << "1 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else if( tem_espacos_em_branco( entrada.dado ) ){
		//cout << "2 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else if( tem_numeros_negativos( entrada.dado ) ){
		//cout << "3 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else if( tem_muitos_delimitadores_entre_numeros( entrada )){
		//cout << "4 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else if(tem_delimitador_no_inicio_fim(entrada.dado) ){
		//cout << "5 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else if( mais_de_3_num_na_linha(entrada) ){
		//cout << "7 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else if( sem_delimitador_entre_numeros(entrada.dado) ){
		//cout << "8 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else if(delimitador_incorreto(entrada) ){
		//cout << "9 <=" << endl;
		entrada.resultado = INVALIDO;
	}
	else{
		//cout << "10 <=" << endl;
		entrada.resultado = soma_numeros(entrada);	
	}
}


bool ausencia_barra_n_final (string s){
	string s_aux(s);
	
	DEBUG_PRINT( "\n	###### fun ausencia_barra_n_final \n" );
    int contador = 0;
    std::smatch m;
    std::regex e ("\\n$|\\r$");   // matches 
    
    //DEBUG_PRINT( "Target sequence: " << s );
    DEBUG_PRINT( "Regular expression: /\\n$/" );
    
    //cout<< " ausencia_barra_n_final s:("<< s << ")"<< endl;
    while (std::regex_search (s_aux,m,e)) {
        for (auto x:m) {
            contador++;
           DEBUG_PRINT( x );
        }
       // std::cout << std::endl;
        s_aux = m.suffix().str();
    }
	
     if (contador == 0 ){
		 return true;
	} else {
		return false;
	}
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

/*******
*   /^(\\n)*(,)(\\n)*|(\\n)*(,)(\\n)*$/
*   para os casos 1,\n e ,2\n retornarem INVALIDO
********/
bool tem_delimitador_no_inicio_fim(string s){
    int contador = 0;
    std::smatch m;
    std::regex e ("^(,)(\\n)*|(\\n)*(,)(\\n)*$");   // matches espacos em branco
    
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
	
	vector<char> scape_regex {'*', '$','^','{','(','|',')','}','.','%'};//, "$", "^", "{", "[", "(", "|", ")", "*", "+", "?", "|"};

	string s_aux ("(");//" (,|;)(\\n)*(,|;)
	
	string s_aux2 ("(\\n)*");

	for (auto atual_del : entrada.v_del)
	{
		//std::cout << "d:: "<< atual_del << endl;
		for (auto d :atual_del) {
			std::vector<char>::iterator it;
			it = find (scape_regex.begin(), scape_regex.end(), d );
			if (it != scape_regex.end()){
				///Elemento encontrado 
				//std::cout << *it <<"<Achei!!!" << endl;
				s_aux+= "\\";// + d;
				//cout << "\\ + d: "<<s_aux << endl;
			} 
				//std::cout << d << " vs "<< to_string(d) << endl;
				s_aux += d;
				//cout << "  so d: "<<s_aux << endl;
			
		}
		s_aux += "|";
	}
	s_aux.pop_back ();
	
	s_aux += ")";
	
	string a="\%\%\%";
	
	s_aux2 = s_aux + s_aux2 + s_aux;
	
	
	//std::cout << "aki: "<< s_aux2 << std::endl;
 
    int contador = 0;
    std::smatch m;
	std::regex e ( s_aux2 );   // matches delimitador
	string s = entrada.dado;
    //std::cout << "aki" << endl;
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
  string s_aux2 = entrada.dado;
  string s = entrada.dado;
  string buffer;
  bool buffer_ativado = false;
  int contador = 0;
	  
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
	/// contador para saber a extensão da declaração do delimitador
	contador ++;
		if ((*str) == '\n'){
			break;
		}
    }
	//cout << "conta :" << contador << endl << endl;
	//cout << "s_aux antes: "<< s_aux2 << "<fim" << endl;
	/// apega começo da string até o \\n da declaração do delimitador
	int len = s_aux2.size();
	s_aux2 = s_aux2.substr(  contador-1, (len - (contador-1)) );
	//entrada.dado.erase( 0, contador-1 );
	
	entrada.dado = s_aux2;
	//cout << ">>depois de apagado " << entrada.dado << " FIM" << endl;
	
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
	/**************
	string s_aux ("(\\d+(?<todos_delimitadores>");

	for (auto i : entrada.v_del)
	{
	  s_aux += i + "|";
	}
	s_aux.pop_back ();
	
	s_aux += ")){3,}\\d+\\n";
	
	DEBUG_PRINT( s_aux );
 
	**************/
  return true;
}

void cria_regex (){
		string s_aux ("(\\d+(?<todos_delimitadores>");
	
}

bool mais_de_3_num_na_linha (t_calc &entrada){
	//cout << "mais_de_3_num_na_linha\n";
	//cout << "ma: "<< entrada.dado << endl;
	string s_aux ("(\\d+("); // (\d+(?<todos_delimitadores>,)){3,}\d+\\n

	
	//std::cout << s_aux << std::endl;
	
	vector<char> scape_regex {'*', '$','^','{','(','|',')','}','.','%'};//, "$", "^", "{", "[", "(", "|", ")", "*", "+", "?", "|"};

	//string s_aux ("(");//" (,|;)(\\n)*(,|;)
	
	//string s_aux2 ("(\\n)*");

	for (auto atual_del : entrada.v_del)
	{
		//std::cout << "d:: "<< atual_del << endl;
		for (auto d :atual_del) {
			std::vector<char>::iterator it;
			it = find (scape_regex.begin(), scape_regex.end(), d );
			if (it != scape_regex.end()){
				///Elemento encontrado 
				//std::cout << *it <<"<Achei!!!" << endl;
				s_aux+= "\\";// + d;
				//cout << "\\ + d: "<<s_aux << endl;
			} 
				//std::cout << d << " vs "<< to_string(d) << endl;
				s_aux += d;
				//cout << "  so d: "<<s_aux << endl;
			
		}
		s_aux += "|";
	}
	s_aux.pop_back ();
	

	s_aux += ")){3,}\\d+\n";
	
	
	
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

bool delimitador_incorreto(t_calc &entrada){
	DEBUG_PRINT(" \n\n #### delimitador_incorreto \n");
	string s = entrada.dado;
	string buffer;
	bool buffer_ativado = false;

	std::locale loc;
	DEBUG_PRINT( "entrada: " << s );
	for (auto str = s.begin (); str != s.end (); ++str)
	{
		
		if (!isdigit((*str),loc) && (*str) != '\n' ){
			buffer_ativado = true;
			DEBUG_PRINT( "b ativado: " << (*str) );
		}
		else if (buffer_ativado && (isdigit((*str),loc) || (*str) == '\n') )
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
	return soma;
}

void ler_entrada (const string arquivoEntrada, vector<string> *strings) {
	//cout << "LER" << endl; 
	string linha;
	ifstream myfile (arquivoEntrada, std::ios::in); // ifstream = padrão ios:in
	if (myfile.is_open()) {
		while ( myfile.good() ) { //enquanto end of file for false continua
			getline (myfile,linha); // como foi aberto em modo texto(padrão)
					 //e não binário(ios::bin) pega cada linha
			/// apaga \ n final
			//linha.erase( linha.size()-1 );
			//myfile >> linha;
			//cout << "l  : " << linha << "<" << endl;
			
			std::string old("\\n");

			int pos;
			while ((pos = linha.find(old)) != std::string::npos)
				linha.replace(pos, old.length(), "\n");
			
			std::string old2("\r");

			int pos2;
			while ((pos2 = linha.find(old2)) != std::string::npos)
				linha.replace(pos2, old2.length(), "");

			//cout << "de: " << linha << "<" << endl << endl;
			
			strings->push_back( linha );
		}
		myfile.close();
		//return true;
	}else
		cout << "Unable to open file"; 
	//return false;
}

void escrever_saida (const string arquivoSaida, vector<int> *resultado){
	//cout << "ESCREVER" << endl; 
	 
	 std::ofstream outfile(arquivoSaida, std::ios::out);
	  
	 for (auto numero : *resultado) {
        outfile << numero << endl;
    }
	outfile.close();
}

void RUN (string e, string s){
	vector<string> todas_strings;
	vector<int> todos_resultados;
	
	ler_entrada(e, &todas_strings);
	
	for (auto str : todas_strings) {
		
		if (str != "\n" || str != ""){
			//cout << " _s inicio: "<< str << "\n _s FIM\n"<< endl;
			//exit(1);
			char * writable = new char[str.size() + 1];
			std::copy(str.begin(), str.end(), writable);
			writable[str.size()] = '\0'; // don't forget the terminating 0

			int resposta = soma_string( writable );
			
			// don't forget to free the string after finished using it
			delete[] writable;
			todos_resultados.push_back( resposta );
		} else {
				cout << "\n\nerro : " << str << endl;
		}
	}
	escrever_saida (s, &todos_resultados);
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG