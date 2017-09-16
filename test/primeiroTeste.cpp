#include "gtest/gtest.h"
#include "string_soma.hpp"
#define INVALIDO -1

///Verifica se é invalido quando entrada não termina em '\n'
TEST (TestaStringSoma, TerminaComBarraN) {
	char entrada1[]="3,4";
	ASSERT_EQ (INVALIDO, soma_string(entrada1));
	char entrada2[]="1,2\n";
	ASSERT_EQ (3 , soma_string(entrada2));
}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
