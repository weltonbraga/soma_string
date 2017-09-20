#include "gtest/gtest.h"
#include "string_soma.hpp"

/**** Teste que não passa, não implementado

Ao adicionar um novo delimitador
*/
TEST (TestaStringSoma_Necessario, UsadoDelimitadorCorreto) {
	t_calc entrada;
	
	entrada.dado ="//[;]\n1;2\n";
	ASSERT_FALSE( delimitador_incorreto(entrada) );
	
	entrada.dado ="//[**]\n1**2\n**3**4\n";
	ASSERT_FALSE( delimitador_incorreto(entrada) );
	
	entrada.dado ="1;2\n";
	ASSERT_TRUE( delimitador_incorreto(entrada) );
}

/// Verifica se é invalido quando entrada não termina em '\n'
TEST (TestaStringSoma_Necessario, TerminaComBarraN) {
	EXPECT_TRUE( ausencia_barra_n_final("1,\n2"));
	EXPECT_TRUE( ausencia_barra_n_final("1,\n\n\n\n0"));

	EXPECT_FALSE( ausencia_barra_n_final("1,2\n\n\n"));
	EXPECT_FALSE( ausencia_barra_n_final("1\n\n,0\n"));
}


/**** Teste que não passa, não implementado 

Aceita entradas inválidas de numeros e letras misturadas

*/

TEST (TestaStringSoma, ApenasNumeros) {
	char * entrada;

	char dado_01[]="3,a\n";
	entrada = dado_01;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
	
	char dado_02[]="b2,22c\n";
	entrada = dado_02;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
}
/// numero no inicio ou no meio da string
TEST (TestaStringSoma_Proibido, NumNegativos) {
	EXPECT_TRUE( tem_numeros_negativos("-1,2,3") );
	EXPECT_TRUE( tem_numeros_negativos("1,\n\n2,3,-4\n") );
	
	EXPECT_FALSE( tem_numeros_negativos("1,2,3") );
	EXPECT_FALSE( tem_numeros_negativos("1,\n\n2,3\n4\n") );
}

/// verifica espaços entre '\n' e no meio da string
TEST (TestaStringSoma_Proibido, EspacosEmBranco) {
	EXPECT_TRUE( tem_espacos_em_branco("1,2 \n") );
	EXPECT_TRUE( tem_espacos_em_branco("1 ,\n \n2,3,-4\n") );
	
	EXPECT_FALSE( tem_espacos_em_branco("1,2,3") );
	EXPECT_FALSE( tem_espacos_em_branco("1,\n\n2,3\n4\n") );
}
/// delimitadores separados por nenhum ou mais '\n'
TEST (TestaStringSoma_Proibido, tem_varios_delimitadores_entre_2_numeros) {
	t_calc entrada;
	entrada.dado = "1,,2\n";
	EXPECT_TRUE( tem_muitos_delimitadores_entre_numeros(entrada) );
	entrada.dado = "1,\n,\n2,3,4\n";
	EXPECT_TRUE( tem_muitos_delimitadores_entre_numeros(entrada) );
	
	entrada.dado = "1,2,3";
	EXPECT_FALSE( tem_muitos_delimitadores_entre_numeros(entrada) );
	entrada.dado = "1,\n\n2,3\n4\n";
	EXPECT_FALSE( tem_muitos_delimitadores_entre_numeros(entrada) );
}
/// verifica capitura de delimitador caso nao seja declarado novo delimitador
TEST (TestaStringSoma_PodeAcontecer, DefineDelimitadores) {
	EXPECT_TRUE( define_delimitador( "//[;]\n2;3\n" ) );
	
	EXPECT_FALSE( define_delimitador( "2***3***4\n" ) );
}

/// verifica casos em que delimitadores novo são invalidos
TEST (TestaStringSoma_PodeAcontecer, ArmazenaNovosDelimitadores) {
	t_calc entrada;
	entrada.dado = "//[;]\n2;3\n" ;
	EXPECT_TRUE( armazena_delimitador( entrada ) );
	entrada.dado ="//[**][%%%]\n2**1%%%3\n";
	EXPECT_TRUE( armazena_delimitador( entrada ) );
	
	entrada.dado = "2***3***4\n"  ;
	EXPECT_FALSE( armazena_delimitador( entrada ) );
	entrada.dado = "//[***]2***3***4\n";
	EXPECT_FALSE( armazena_delimitador( entrada ) );
	entrada.dado = "//[]1;2\n";
	EXPECT_FALSE( armazena_delimitador( entrada ) );


}

/// verifica se os delimitadores usados são conhecidos
TEST (TestaStringSoma_PodeAcontecer, delimitador_incorreto){
	t_calc entrada;
	entrada.dado = "1;2\n";
	EXPECT_TRUE( delimitador_incorreto( entrada ) );
	entrada.dado = "1,2\n";
	EXPECT_FALSE( delimitador_incorreto( entrada ) );
}


/// quantidade de numeros menor que 1 ou maior que 3
TEST (TestaStringSoma_Proibido, MaisDe3naLinha) {
	t_calc entrada;
	entrada.dado = "1,2,3,4\n";
	EXPECT_TRUE (mais_de_3_num_na_linha(entrada));
	
	entrada.dado = "1,2,3\n,4\n";
	EXPECT_FALSE (mais_de_3_num_na_linha(entrada));

}

/// verifica numeros separados por '\n' e delimitadores misturados
TEST (TestaStringSoma_Proibido, SemDelimitador) {

	EXPECT_TRUE (sem_delimitador_entre_numeros("1,2\n3,4\n"));
	
	EXPECT_FALSE (sem_delimitador_entre_numeros("1,2,3\n,4\n"));

}


/// Quando o teste acima passar quero que o resultado aqui seja correto
TEST (TestaStringSoma_calcular, ResultadoDaSoma) {
	char * entrada;

	char dado_01[]=",\n";
	entrada = dado_01;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
	
	char dado_02[]="1,2,3\n";
	entrada = dado_02;
	EXPECT_EQ (6 , soma_string(entrada));
	
	char dado_03[]="1,2,3";
	entrada = dado_03;
	EXPECT_EQ (INVALIDO , soma_string(entrada));
}

/// quantidade de numeros menor que 1 ou maior que 3
TEST (TestaStringSoma, DeZeroAteTresNum) {
	char * entrada;

	char dado_01[]="3\n";
	entrada = dado_01;
	EXPECT_EQ (3, soma_string(entrada));
	
	char dado_02[]="1,2,3,4\n";
	entrada = dado_02;
	EXPECT_EQ (INVALIDO, soma_string(entrada));

}

/// Proibido numeros negativos
TEST (TestaStringSoma, ProibidoNumNegativos) {
	char * entrada;

	char dado_01[]="10,-7\n";
	entrada = dado_01;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
	
	char dado_02[]="-1\n";
	entrada = dado_02;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
}

/// ignora numeros maiores que 1000
TEST (TestaStringSoma, IgnoraMaioresQue1000) {
	char * entrada;

	char dado_01[]="3,2000\n";
	entrada = dado_01;
	EXPECT_EQ (3, soma_string(entrada));
	
	char dado_02[]="1001,1000\n";
	entrada = dado_02;
	EXPECT_EQ (1000, soma_string(entrada));
}

/// espaco no meio da string
TEST (TestaStringSoma, Delimitador) {
	char * entrada;

	char dado_01[]="5,6 \n";
	entrada = dado_01;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
	
	char dado_02[]="7, 8\n";
	entrada = dado_02;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
	
	char dado_03[]="1 ,2,3\n";
	entrada = dado_03;
	EXPECT_EQ (INVALIDO , soma_string(entrada));
}
/// numeros negativos em varias posições da strings
TEST (TestaStringSoma, PROIBIDO) {
	EXPECT_FALSE(tem_numeros_negativos("1,2,3\n4\n"));
	EXPECT_TRUE(tem_numeros_negativos("-1,2,-3\n4\n"));
	EXPECT_TRUE(tem_numeros_negativos("1,2,-3\n4\n"));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
