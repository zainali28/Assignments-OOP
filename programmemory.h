#pragma once

#include"inputfilestream.h"
#include"outputfilestream.h"
#include "cstring.h"

using namespace std;

class ProgramMemory
{
private:
	unsigned char* m_uc_InstructionMemory;
	int m_i_PC;
	int m_i_instruction_no;


public:

	//friend classes

	friend class CAssembler;
	friend class InputFileStream;


	//contructor prototype
	ProgramMemory();	//default
	ProgramMemory(const char* file);	//parameterised


	//functions
	void load(const char* file);
	int GetNumberOfInstructions();
	unsigned char GetInstruction(int PC);
};
