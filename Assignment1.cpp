//Author: Zain Ali
//Title: 4 Bit Microprocessor Simulator





#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <bitset>

using namespace std;

bool BitValue(unsigned char Byte, int BitNumber)	//takes a bit value from a byte at specific position
{
	unsigned char mask = 0x00;

	switch (BitNumber)	//Conditions to check bit
	{
	case 1:	mask = 0x80;
		break;
	case 2:	mask = 0x40;
		break;
	case 3:	mask = 0x20;
		break;
	case 4:	mask = 0x10;
		break;
	case 5:	mask = 0x08;
		break;
	case 6:	mask = 0x04;
		break;
	case 7:	mask = 0x02;
		break;
	case 8:	mask = 0x01;
		break;
	}

	return (Byte & mask);
}

void Two_to_Four_Decoder(bool D0, bool D1, bool& O3, bool& O2, bool& O1, bool& O0)	//enables 1 bit at a time to perform operation on it
{
	if (D1 == 0 && D0 == 0)
	{
		O3 = 0;
		O2 = 0;
		O1 = 0;
		O0 = 1;
	}

	else if (D1 == 0 && D0 == 1)
	{
		O3 = 0;
		O2 = 0;
		O1 = 1;
		O0 = 0;
	}

	else if (D1 == 1 && D0 == 0)
	{
		O3 = 0;
		O2 = 1;
		O1 = 0;
		O0 = 0;
	}

	else if (D1 == 1 && D0 == 1)
	{
		O3 = 1;
		O2 = 0;
		O1 = 0;
		O0 = 0;
	}
}

struct ControlStruct
{
	bool J = 0;
	bool C = 0;
	bool D1 = 0;
	bool D0 = 0;
	bool Sreg = 0;
	bool S = 0;
	bool imm1 = 0;
	bool imm2 = 0;
	bool Reserved = 0;
	bool R0_En = 0;
	bool RB_En = 0;
	bool RA_En = 0;
};

struct ControlStruct InstructionDecoder(unsigned char MachineCode, int& RA, int& RB, int& R0)
{
	//stores each bit in the corresponding variable
	bool J = BitValue(MachineCode, 1);
	bool C = BitValue(MachineCode, 2);
	bool D1 = BitValue(MachineCode, 3);
	bool D0 = BitValue(MachineCode, 4);
	bool Sreg = BitValue(MachineCode, 5);
	bool S = BitValue(MachineCode, 6);
	bool imm1 = BitValue(MachineCode, 7);
	bool imm2 = BitValue(MachineCode, 8);

	bool Reserved = 0;
	bool R0_En = 0;
	bool RB_En = 0;
	bool RA_En = 0;

	Two_to_Four_Decoder(D0, D1, Reserved, R0_En, RB_En, RA_En);

	//storing values in new structure
	struct ControlStruct myStruct;
	myStruct.J = J;
	myStruct.C = C;
	myStruct.D1 = D1;
	myStruct.D0 = D0;
	myStruct.Sreg = Sreg;
	myStruct.S = S;
	myStruct.imm1 = imm1;
	myStruct.imm2 = imm2;
	myStruct.RA_En = RA_En;
	myStruct.RB_En = RB_En;
	myStruct.R0_En = R0_En;

	return myStruct;

}

string leftstring(string instruction)
{

	for (int i = 0; i < instruction.length(); i++)
	{
		if (instruction.at(i) == '=')	//gets the part of the string before = operator
		{
			return instruction.substr(0, i);
		}
	}
}

string rightstring(string instruction)
{
	for (int i = 0; i < instruction.length(); i++)
	{
		if (instruction.at(i) == '=')	//gets the part of the string after = operator
		{
			return instruction.substr(i + 1, instruction.length());
		}

	}
}

void removespaces(string& instruction)
{
	for (int i = 0; i < instruction.length(); i++)
	{
		while (instruction.at(i) == ' ')	//searches for the whitespace character and removes it
		{
			instruction.erase(instruction.begin() + i);
		}
	}
}

void instrFetch(int& programcounter, unsigned char* instrMem, unsigned char& instrReg)	//stores instruction from instruction memory to instruction register
{
	instrReg = instrMem[programcounter];
	programcounter++;

}

void Assembler(string infile, unsigned char* instrMem, int& instrno)	//converts instruction to machine code
{
	string instruction;
	string left;
	string right;
	int number = 0;

	ifstream inputfile;
	inputfile.open(infile);

	while (!inputfile.eof())	//executes the body until end of file
	{
		getline(inputfile, instruction);	//stores string of each line in instruction

		if (instruction == "")
			;
		else
		{
			removespaces(instruction);	//removes spaces in each instruction

			left = leftstring(instruction);
			right = rightstring(instruction);

			cout << "Instruction is \"" << left << "=" << right << "\"" << endl;

			if (left == "RA" && right.length() == 2)	//Testing all conditions of left and right string
			{
				number = stoi(right);
				instrMem[instrno] = (0x08 + number);
			}
			else if (left == "RA" && right == "RA+RB;")
			{
				instrMem[instrno] = 0x00;
			}
			else if (left == "RA" && right == "RA-RB;")
			{
				instrMem[instrno] = 0x04;
			}
			else if (left == "RB" && right.length() == 2)
			{
				number = stoi(right);
				instrMem[instrno] = 0x18 + number;
			}
			else if (left == "RB" && right == "RA-RB;")
			{
				instrMem[instrno] = 0x14;
			}

			bitset<8>x(instrMem[instrno]);
			cout << "Machine Code is: " << x[7] << x[6] << x[5] << x[4] << x[3] << x[2] << x[1] << x[0] << endl << endl;

			instrno++;
		}
	}
}

int InstructionExecutor(int& RA, int& RB, struct ControlStruct myStruct)	//tests different op codes for specific operation
{
	//performs the operation and returns it depending on the S bit
	if (myStruct.S == 0)
	{
		return (RA + RB);
	}

	else
	{
		return (RA - RB);
	}
}

void WriteBack(int& RA, int& RB, int& R0, struct ControlStruct myStruct, int ALU_output)
{

	//updates and stores the value in the register depending on enable bits for data registers
	int temp = 0;
	int imm = (myStruct.S * 4) + (myStruct.imm1 * 2) + (myStruct.imm2 * 1);

	if (myStruct.Sreg == 1)
	{
		temp = imm;
	}

	else
	{
		temp = ALU_output;
	}

	if (myStruct.RA_En == 1)
	{
		RA = temp;
		cout << endl << "RA: " << RA;
	}

	else if (myStruct.RB_En == 1)
	{
		RB = temp;
		cout << endl << "RB: " << RB;
	}

	else if (myStruct.R0_En == 1)
	{
		R0 = RA;
		cout << endl << "R0: " << R0;
	}
}

int main()
{
	unsigned char instrMem[100] = { 0 };
	int instrno = 0;
	unsigned char instructionReg = 0;
	int programcounter = 0;
	int RA = 0;
	int RB = 0;
	int R0 = 0;
	int ALU_output = 0;
	string file = "swap.asm";

	Assembler(file, &instrMem[0], instrno);	//generates & machine code

	for (int i = 0; i < instrno; i++)
	{
		instrFetch(programcounter, &instrMem[i], instructionReg);	//stores current instruction in machinecode variable
		struct ControlStruct myControlStruct = InstructionDecoder(instructionReg, RA, RB, R0);	//decodes the instruction
		ALU_output = InstructionExecutor(RA, RB, myControlStruct);	//executes the operation
		WriteBack(RA, RB, R0, myControlStruct, ALU_output);	//updates the value of the register
	}

	return 0;
}
