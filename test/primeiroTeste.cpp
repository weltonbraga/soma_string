#include "gtest/gtest.h"
 
TEST (TestaStringSoma, PrototipoRetornaZero) { 
    ASSERT_EQ (0, soma_string('0'));
		ASSERT_EQ (3 , soma_string('1,2\n'));
}
 
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}