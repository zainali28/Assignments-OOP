#pragma once

#include "cstring.h"

using namespace std;

class OutputFileStream
{
private:
	CString m_cs_instruction;
	char m_c_buffer[128];
	FILE* m_F_outfile;

public:

	//friend classes

	friend class CAssembler;

	
	//constructor prototype
	OutputFileStream();	//default
	OutputFileStream(const CString& output);	//parameterised
	OutputFileStream(const char* data);	//parameterised



	//mutator functions




	//functions
	void open(CString& input);	//opens the file
	void close();	//closes the stream file
	void write(const char* data, streamsize );


	//operator overloaders
	void operator << (const CString& data);
	void operator << (const unsigned char data);
};