#include "programmemory.h"

using namespace std;


//contructor
ProgramMemory:: ProgramMemory()	: m_i_instruction_no(0), m_i_PC(0)	//default
{
	this->m_uc_InstructionMemory = NULL;
}

ProgramMemory:: ProgramMemory(const char* file)	//parameterised
{
	this->m_i_instruction_no = 0;
	this->m_i_PC = 0;
	this->m_uc_InstructionMemory = NULL;

	int count = 0;

	unsigned char temp = ' ';
	unsigned char* temparr = NULL;
	CString s;

	InputFileStream infile;

	infile.open(file, "rb");

	while (1)	//executes the body until end of file
	{
		if (feof(infile.m_F_infile))
			break;


		infile.getline(s);


		if (this->m_i_instruction_no == 0)
		{
			this->m_uc_InstructionMemory = new unsigned char;

			this->m_uc_InstructionMemory[0] = s.m_c_data[0];
		}

		else
		{
			temparr = new unsigned char[this->m_i_instruction_no + 1];



			for (int i = 0; i < this->m_i_instruction_no; i++)
			{
				temparr[i] = this->m_uc_InstructionMemory[i];
			}

			temparr[this->m_i_instruction_no] = s.m_c_data[0];

			delete[] this->m_uc_InstructionMemory;

			this->m_uc_InstructionMemory = new unsigned char[this->m_i_instruction_no + 1];

			for (int i = 0; i <= this->m_i_instruction_no; i++)
			{
				this->m_uc_InstructionMemory[i] = temparr[i];
			}

			delete[] temparr;
		}

		this->m_uc_InstructionMemory[this->m_i_instruction_no] = s.m_c_data[0];

		this->m_i_instruction_no++;


	}

	infile.close();
}


//functions
void ProgramMemory::load(const char* file)
{


	this->m_i_instruction_no = 0;
	this->m_i_PC = 0;

	int count = 0;

	unsigned char temp;
	unsigned char* temparr = NULL;
	string s;

	InputFileStream infile;

	infile.open(file/*, ios_base::binary*/);

	while (1)	//executes the body until end of file
	{
		if (feof(infile.m_F_infile))
			break;

		fread((void*)&temp, sizeof(unsigned char), 1, infile.m_F_infile);


		if (this->m_uc_InstructionMemory == NULL)
		{
			this->m_uc_InstructionMemory = new unsigned char;

			this->m_uc_InstructionMemory[0] = temp;
		}

		else
		{
			temparr = new unsigned char[this->m_i_instruction_no + 1];



			for (int i = 0; i < this->m_i_instruction_no + 1; i++)
			{
				temparr[i] = this->m_uc_InstructionMemory[i];
			}

			temparr[this->m_i_instruction_no] = temp;

			delete[] this->m_uc_InstructionMemory;

			this->m_uc_InstructionMemory = new unsigned char[this->m_i_instruction_no + 1];

			for (int i = 0; i < this->m_i_instruction_no + 1; i++)
			{
				this->m_uc_InstructionMemory[i] = temparr[i];
			}

			delete[] temparr;
		}

		this->m_uc_InstructionMemory[this->m_i_instruction_no] = temp;

		this->m_i_instruction_no++;


	}

	infile.close();

}

int ProgramMemory::GetNumberOfInstructions()
{
	return this->m_i_instruction_no;
}

unsigned char ProgramMemory::GetInstruction(int PC)
{
	if (PC >= this->m_i_instruction_no)
		cout << "OUT OF RANGE INSTRUCTION.";

	else
	{

		this->m_i_PC = PC;


		unsigned char temp;

		const char* instruction = NULL;


		temp = this->m_uc_InstructionMemory[PC];



		return temp;
	}

}