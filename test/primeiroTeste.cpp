#include "gtest/gtest.h"
#include "string_soma.hpp"

const int INVALIDO = -1;

///Verifica se é invalido quando entrada não termina em '\n'
TEST (TestaStringSoma, TerminaComBarraN) {
	char * entrada;
	char dado_01[]="3,4";
	entrada = dado_01;
	ASSERT_EQ (INVALIDO, soma_string(entrada));
	char dado_02[]="1,2\n";
	entrada = dado_02;
	ASSERT_EQ (3 , soma_string(entrada));
}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
