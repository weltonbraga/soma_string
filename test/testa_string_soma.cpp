#include "gtest/gtest.h"
#include "string_soma.hpp"

///Verifica se é invalido quando entrada não termina em '\n'
TEST (TestaStringSoma_Necessario, TerminaComBarraN) {
	EXPECT_TRUE( ausencia_barra_n_final("1,\n2"));
	EXPECT_TRUE( ausencia_barra_n_final("1,\n\n\n\n0"));

	EXPECT_FALSE( ausencia_barra_n_final("1,2\n\n\n"));
	EXPECT_FALSE( ausencia_barra_n_final("1\n\n,0\n"));
}

TEST (TestaStringSoma_Proibido, NumNegativos) {
	EXPECT_TRUE( tem_numeros_negativos("-1,2,3") );
	EXPECT_TRUE( tem_numeros_negativos("1,\n\n2,3,-4\n") );
	
	EXPECT_FALSE( tem_numeros_negativos("1,2,3") );
	EXPECT_FALSE( tem_numeros_negativos("1,\n\n2,3\n4\n") );
}

TEST (TestaStringSoma_Proibido, EspacosEmBranco) {
	EXPECT_TRUE( tem_espacos_em_branco("1,2 \n") );
	EXPECT_TRUE( tem_espacos_em_branco("1 ,\n \n2,3,-4\n") );
	
	EXPECT_FALSE( tem_espacos_em_branco("1,2,3") );
	EXPECT_FALSE( tem_espacos_em_branco("1,\n\n2,3\n4\n") );
}
TEST (TestaStringSoma_Proibido, tem_varios_delimitadores_entre_2_numeros) {
	EXPECT_TRUE( tem_muitos_delimitadores_entre_numeros("1,,2\n") );
	EXPECT_TRUE( tem_muitos_delimitadores_entre_numeros("1,\n,\n2,3,4\n") );
	
	EXPECT_FALSE( tem_muitos_delimitadores_entre_numeros("1,2,3") );
	EXPECT_FALSE( tem_muitos_delimitadores_entre_numeros("1,\n\n2,3\n4\n") );
}

TEST (TestaStringSoma_PodeAcontecer, DefineDelimitadores) {
	EXPECT_TRUE( define_delimitador( "//[;]\n2;3\n" ) );
	
	EXPECT_FALSE( define_delimitador( "2***3***4\n" ) );
}

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

}

/*// Quando o teste acima passar quero que o resultado aqui seja correto
TEST (TestaStringSoma, ResultadoDaSoma) {
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
///invalida entrada com letras
TEST (TestaStringSoma, ApenasNumeros) {
	char * entrada;

	char dado_01[]="3,a\n";
	entrada = dado_01;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
	
	char dado_02[]="b2,22c\n";
	entrada = dado_02;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
}
//
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

TEST (TestaStringSoma, PROIBIDO) {
	EXPECT_FALSE(tem_numeros_negativos("1,2,3\n4\n"));
	EXPECT_TRUE(tem_numeros_negativos("-1,2,-3\n4\n"));
	EXPECT_TRUE(tem_numeros_negativos("1,2,-3\n4\n"));
}
*/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
