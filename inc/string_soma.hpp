/*! 
 *  \brief     Trabalho 1 - MP
 *  \details   Métodos de Programação - 201600
 *  \author    Welton de Almeida Braga - 16/0148880
 *  \date      20-09-2017
 */
/// diretivas de compilador
//#ifndef MYLIB
//#define MYLIB

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <locale> 

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::vector;
using std::regex;
using std::smatch;
using std::regex_search;
using std::stoi;
using std::to_string;

using std::ifstream;

typedef struct tt_calc {
  int resultado; /// resultado da soma ou INVALIDO
  string dado; /// string de entrada
  vector<string> v_del{","}; /// vetor de delimitadores
  regex regex_del;
}t_calc;

/// retorno para dado de entrada que não satisfaz as especificações
const int INVALIDO = -1;

/// função principal
int soma_string(char *string_entrada);

/// verifica e retorna resultado ou INVALIDO
void calcula_resultado(t_calc &entrada);

/// retorna verdadeiro se NÃO houver '\n' no final da string de entrada 
bool ausencia_barra_n_final(string );

/// retorna verdadeiro se houver números negativos na string de entrada 
bool tem_numeros_negativos(string );

/// retorna verdadeiro se houver espaçoes em branco na string de entrada 
bool tem_espacos_em_branco(string );

/// retorna verdadeiro caso seja usado mais de um delimitador entre números. Ex: '1,,2\n'
bool tem_muitos_delimitadores_entre_numeros(t_calc &entrada);

/// retorna verdadeiro caso caso a string comece com '//' indicando a entrada de novos delimitadores
bool define_delimitador(string );

/// retorna verdadeiro se conseguir armazenar os delimitadores
bool armazena_delimitador(t_calc &entrada);

/// retorna o resultado da soma ou INVALIDO
int soma_numeros (t_calc &entrada);

/// retorna verdadeiro caso exista delimitadores não conhecidos na string
bool delimitador_incorreto(t_calc &entrada);

/// retorna verdadeiro caso exista mais de 3 números na mesma linha
bool mais_de_3_num_na_linha(t_calc &entrada);

/// retorna verdadeiro caso o nunero não sejam separados por delimitador mas por '\n'
bool sem_delimitador_entre_numeros (string);

/// começa ou termina com delimitador
bool tem_delimitador_no_inicio_fim (string);
	

/// [Não implementado] abre e armazena dados do arquivo de entrada
void ler_entrada(const string, vector<string> *);

/// [Não implementado] escreve resultado em arquivo de saída
void escrever_saida(const string, vector<int> *);

void RUN (const string, const string);



//#endif