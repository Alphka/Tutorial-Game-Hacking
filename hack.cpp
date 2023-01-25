#include <windows.h>
#include <iostream>
#include <string>

void LogError(std::string process){
	std::cout << process << " failed. GetLastError = " << GetLastError() << std::endl;
}

int main(){
	DWORD pid;

	std::cout << "PID: ";
	std::cin >> pid;

	const auto handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if(handle == NULL){
		LogError("OpenProcess");
		return EXIT_FAILURE;
	}

	uintptr_t memoryAddress;

	std::cout << "Memory address of the integer to overwrite (in hexadecimal): 0x";
	std::cin >> std::hex >> memoryAddress;

	int value;

	std::cout << "Integer to write (in decimal): ";
	std::cin >> std::dec >> value;

	auto written = WriteProcessMemory(handle, (LPVOID) memoryAddress, &value, sizeof(value), nullptr);

	if(written == FALSE){
		LogError("WriteProcessMemory");
		return EXIT_FAILURE;
	}

	std::cout << "Overwritten successfully" << std::endl;

	return EXIT_SUCCESS;
}
