#include "gtest/gtest.h"
#define INVALIDO -1

///Verifica se é invalido quando entrada não termina em '\n'
TEST (TestaStringSoma, TerminaComBarraN) { 
	ASSERT_EQ (INVALIDO, soma_string('3,4'));
	ASSERT_EQ (3 , soma_string('1,2\n'));
}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
