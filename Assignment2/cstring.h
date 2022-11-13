//CString.h
#pragma once
#include <iostream>

using namespace std;

class CString
{
private:
	char* m_c_data;
	int m_i_length;

public:

	//friend classes
	friend class InputFileStream;
	friend class OutputFileStream;
	friend class CAssembler;
	friend class ProgramMemory;
	 
	
	//Constructors
	CString();
	CString(const char* data);


	//copy constructor
	CString(CString& s);


	//destructor
	~CString();


	//mutator functions
	void setstring(const char* data)
	{
		m_i_length = strlen(data) + 1;
		delete[] m_c_data;

		m_c_data = new char[m_i_length];

		strcpy(m_c_data, data);
	}
	
	void getstring()
	{
		for (int i = 0; i < m_i_length; i++)
			cout << m_c_data[i];
	}

	int getlength()
	{
		return m_i_length;
	}



	//operator overloaders
	bool operator == (const CString& s);
	bool operator == (const char* data);
	CString& operator + (const CString& s);
	CString& operator + (const char* data);
	CString& operator = (const CString& s);
	CString& operator += (const CString& s);
	CString& operator += (const char* data);
	char operator [] (int index);
	friend ostream& operator << (ostream& output, const CString& s);
	friend istream& operator >> (istream& input, CString& s);



	//functions
	char* get();
	void set(char* data);
	int find(const char* keyword);
	void removespace();
	CString substring(int index, int length);
	CString leftstring(const char data);
	CString rightstring(const char data);
	int cstoi();
};