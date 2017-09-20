#ifndef MYLIB
#define MYLIB

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>

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

typedef struct tt_calc {
  int resultado;
  string dado;
  vector<string> v_del;
}t_calc;

/// retorno para dado de entrada que não satisfaz as especificações
const int INVALIDO = -1;

/// função principal
int soma_string(char *string_entrada);

// verifica e retorna
void calcula_resultado(t_calc &entrada);

// descrição
bool ausencia_barra_n_final(string );

bool tem_numeros_negativos(string );

bool tem_espacos_em_branco(string );

bool tem_muitos_delimitadores_entre_numeros(string );

bool define_delimitador(string s);

bool armazena_delimitador(t_calc &entrada);

/// busca e soma 
int soma_numeros (t_calc &entrada);



/// retorna invalido ex: 1,2 \n
//bool tem_espacos_na_string(string &entrada);

/// abre e armazena dados de entrada
//void ler_entrada(char * string_entrada);

/// escreve resultado em arquivo de saída
//void escrever_saida();



#endif