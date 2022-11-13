#include "inputfilestream.h"
#include "cassembler.h"
#include "outputfilestream.h"
#include <iostream>
#include "cstring.h"
#include "programmemory.h"

using namespace std;

int main()
{
	CAssembler myAss;

	myAss.AssyToMachineTranslation("swap.asm", "swap.bin");

	ProgramMemory microProgramMemory("swap.bin");
	int totalNumberOfInstructions = microProgramMemory.GetNumberOfInstructions();


	for (int PC = 0; PC < totalNumberOfInstructions; PC++)
	{
		unsigned char MachineCode = microProgramMemory.GetInstruction(PC);
		cout << hex << int(MachineCode) << endl;
	}




	return 0;
}