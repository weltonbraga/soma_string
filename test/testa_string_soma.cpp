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
TEST (TestaStringSoma, resultadoDaSoma) {
	char * entrada;

	char dado_01[]="1,2\n";
	entrada = dado_01;
	EXPECT_EQ (3, soma_string(entrada));
	
	char dado_02[]="1,2,3\n";
	entrada = dado_02;
	EXPECT_EQ (6 , soma_string(entrada));
}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
