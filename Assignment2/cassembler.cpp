#include "cassembler.h"


//constructors
CAssembler::CAssembler() : m_cs_type("")	//dafault
{ }

CAssembler::CAssembler(const char* type) : m_cs_type(type)	//parameterised
{ }


//functions
void CAssembler::AssyToMachineTranslation(const char* source, const char* destination)
{
	CString left;
	CString right;
	CString instruction;
	int number = 0;
	int instrno = 0;
	unsigned char temp = ' ';

	InputFileStream inputfile;
	inputfile.open(source, "r+");

	OutputFileStream outfile(destination);

	while (!feof(inputfile.m_F_infile))	//executes the body until end of file
	{
		inputfile.getline(instruction);	//stores string of each line in instruction

		if (instruction == "")
			;
		else
		{
			instruction.removespace();	//removes spaces in each instruction

			left = instruction.leftstring('=');
			right = instruction.rightstring('=');

			if (left == "RA" && right.getlength() == 3)	//Testing all conditions of left and right string
			{
				number = right.cstoi();
				temp = (0x08 + number);
			}

			if (left == "RA" && right == "RA+RB;")
			{
				temp = 0x00;
			}

			if (left == "RA" && right == "RA-RB;")
			{
				temp = 0x04;
			}

			if (left == "RB" && right.getlength() == 3)
			{
				number = right.cstoi();
				temp = 0x18 + number;
			}

			if (left == "RB" && right == "RA-RB;")
			{
				temp = 0x14;
			}

			instrno++;

			outfile << temp;
		}

	}

	outfile.close();
	inputfile.close();
}