#include "string_soma.hpp"

int main(){
	
	char dado[] = "1,2\n";
	char * entrada = dado;
	soma_string(entrada);
	cout << "ok" << endl;
	return 0;
}