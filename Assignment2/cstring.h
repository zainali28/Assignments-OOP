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
	CString();	//default
	CString(const char* data);	//parameterised


	//copy constructor
	CString(CString& s);


	//destructor
	~CString();


	//mutator functions
	void setstring(const char* data)	//setter for string
	{
		m_i_length = strlen(data) + 1;
		delete[] m_c_data;

		m_c_data = new char[m_i_length];

		strcpy(m_c_data, data);
	}
	
	void getstring()	//getter for string
	{
		for (int i = 0; i < m_i_length; i++)
			cout << m_c_data[i];
	}

	int getlength()	//getter for length of string
	{
		return m_i_length;
	}



	//operator overloaders
	bool operator == (const CString& s);	//equality checker for string
	bool operator == (const char* data);	//equality checker for string parameterised
	CString& operator + (const CString& s);	//string contatenation 
	CString& operator + (const char* data);	//string concatenation parameterised
	CString& operator = (const CString& s);	//string assignment
	CString& operator += (const CString& s);	//string contatenation to itself 
	CString& operator += (const char* data);	//string contatenation to itself parameterised
	char operator [] (int index);	//character return at index
	friend ostream& operator << (ostream& output, const CString& s);	//displaying string
	friend istream& operator >> (istream& input, CString& s);	//storing string (without spaced)



	//functions
	char* get();	//getter for string
	void set(char* data);	//setter for string
	int find(const char* keyword);	//finding and returning the index of keyword string
	void removespace();	//removes spaces of string
	CString substring(int index, int length);	//returns substring from a string starting at index and length as specified by user
	CString leftstring(const char data);	//returns string to left of char at which to break string
	CString rightstring(const char data);	//returns string to left of char at which to break string
	int cstoi();	//conversion from string to int
};
