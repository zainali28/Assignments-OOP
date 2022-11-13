#pragma once
#include "cstring.h"
#include "inputfilestream.h"
#include "outputfilestream.h"

using namespace std;

class CAssembler
{
private:
	CString m_cs_type;

public:


	//constructor prototype
	CAssembler();	//default
	CAssembler(const char* type);	//parameterised


	//functions
	void AssyToMachineTranslation(const char* source, const char* destination);	//Assembly to Machine instructions
};