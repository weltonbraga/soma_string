#include "gtest/gtest.h"
#include "string_soma.hpp"

///Verifica se é invalido quando entrada não termina em '\n'
TEST (TestaStringSoma, TerminaComBarraN) {
	char * entrada;

	char dado_01[]="0,0";
	entrada = dado_01;
	EXPECT_EQ (INVALIDO, soma_string(entrada));
	
	char dado_02[]="0,0\n";
	entrada = dado_02;
	EXPECT_EQ (0 , soma_string(entrada));
}
/// Quando o teste acima passar quero que o resultado aqui seja correto
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

	char dado_01[]="1,-2\n";
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



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
