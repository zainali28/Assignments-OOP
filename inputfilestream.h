
#pragma once

#include <iostream>
#include "cstring.h"
#include <cstdio>

using namespace std;

class InputFileStream
{
private:
	CString m_cs_instruction;	//path to file
	char m_c_buffer[128];	//buffer to temporarily store the data to reduce operation speed
	FILE* m_F_infile;
	const char* m_ccp_mode;

public:
	//friend classes
	friend class ProgramMemory;
	friend class CAssembler;

	//constructor prototype
	InputFileStream();	//default
	InputFileStream(const CString& input);	//parameterised
	InputFileStream(const char* data);	//parameterised
	

	//functions
	void open(const CString& input);	//opens the file
	void open(const char* data, const char* mode);	//opens the file
	void close();	//closes the stream
	void getline(const char* data);	//extracts strings line by line
	void getline(CString& instruction);	//extracts strings line by line
};

