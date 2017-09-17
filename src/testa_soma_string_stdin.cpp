#include "string_soma.hpp"

#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
	#define DEBUG_PRINT(x) 
#endif

int main(){

	char str[] = "1,2\n";
	char * entrada = str;
	int r = soma_string(entrada);
	DEBUG_PRINT(r);
	return 0;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG