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

typedef struct tt_calc {
  int resultado;
  string dado;
}t_calc;

/// retorno para dado de entrada que não satisfaz as especificações
const int INVALIDO = -1;

/// função principal
int soma_string(char *string_entrada);

// verifica e retorna
void calcula_resultado(t_calc &entrada);

// descrição
bool termina_com_barra_n(t_calc &entrada);

/// busca e soma 
int soma_numeros (t_calc &entrada);

/// retorna invalido ex: 1,2 \n
bool espaco_no_final(t_calc &entrada);

/// abre e armazena dados de entrada
//void ler_entrada(char * string_entrada);

/// escreve resultado em arquivo de saída
//void escrever_saida();



#endif