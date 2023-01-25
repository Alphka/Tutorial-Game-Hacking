#include <windows.h>
#include <iostream>
#include <sstream>
#include <string>

auto printAddress(void* address){
	std::stringstream hex;
	hex << "(" << std::hex << address << ")";
	return hex.str();
}

int main(){
	int varInt = 123456;

	while(true){
		std::cout << "Process ID: " << GetCurrentProcessId() << std::endl;
		std::cout << std::endl;
		std::cout << "int        " << printAddress(&varInt) << " = " << std::dec << varInt << std::endl;
		std::cout << std::endl;
		std::cout << "Press ENTER to print again." << std::endl;

		getchar();

		std::cout << std::endl << "---------------------------------------------------" << std::endl;
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
