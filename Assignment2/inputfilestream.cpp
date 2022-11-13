#include "inputfilestream.h"

using namespace std;


//constructor defintion
InputFileStream::InputFileStream()
{
	m_cs_instruction = "";

	for (int i = 0; i < sizeof(this->m_c_buffer); i++)
	{
		m_c_buffer[i] = { NULL };
	}

	m_F_infile = NULL;
}

InputFileStream::InputFileStream(const CString& input)	//parameterised
{

	for (int i = 0; i < 100; i++)
	{
		m_c_buffer[i] = { NULL };
	}


	CString const mode("r+");

	this->m_F_infile = fopen(input.m_c_data, mode.m_c_data);

	if (this->m_F_infile == NULL)
	{
		cout << "NO FILE FOUND OF THIS NAME.";
	}

	else
	{
		while (!feof(this->m_F_infile))
		{
			fread(this->m_c_buffer, sizeof(this->m_c_buffer), 1, this->m_F_infile);
			cout << this->m_c_buffer;
		}
	}
}

InputFileStream::InputFileStream(const char* data)	//parameterised
{
	CString input(data);

	for (int i = 0; i < 100; i++)
	{
		m_c_buffer[i] = { NULL };
	}


	CString const mode("r+");

	this->m_F_infile = fopen(input.m_c_data, mode.m_c_data);

	if (this->m_F_infile == NULL)
	{
		cout << "NO FILE FOUND OF THIS NAME.";
	}

	else
	{
		while (!feof(this->m_F_infile))
		{
			fread(this->m_c_buffer, sizeof(this->m_c_buffer), 1, this->m_F_infile);
			cout << this->m_c_buffer;
		}
	}
}



//functions
void InputFileStream::open(const CString& input)
{

	for (int i = 0; i < 100; i++)
	{
		m_c_buffer[i] = { NULL };
	}


	CString const mode("r+");

	this->m_F_infile = fopen(input.m_c_data, mode.m_c_data);

	if (this->m_F_infile == NULL)
	{
		cout << "NO FILE FOUND OF THIS NAME.";
	}

	else
		;

}

void InputFileStream::open(const char* data, const char* mode)
{
	CString input(data);
	this->m_ccp_mode = mode;

	for (int i = 0; i < 100; i++)
	{
		m_c_buffer[i] = { NULL };
	}

	this->m_F_infile = fopen(input.m_c_data, this->m_ccp_mode);

	if (this->m_F_infile == NULL)
	{
		cout << "NO FILE FOUND OF THIS NAME.";
	}

	else
		;

}

void InputFileStream::close()
{
	fclose(this->m_F_infile);
}

void InputFileStream:: getline(const char* data)
{
}

void InputFileStream::getline(CString& instruction)
{

	if (this->m_ccp_mode == "r+")
	{
		char ch = '\n';
		char* chptr = &ch;
		int i = 0;

		fgets(this->m_c_buffer, 128, this->m_F_infile);

		while (this->m_c_buffer[i] != '\n')
		{
			i++;
		}

		instruction.m_c_data = new char[i + 1];
		instruction.m_i_length = i + 1;

		for (int j = 0; j < i; j++)
		{
			instruction.m_c_data[j] = this->m_c_buffer[j];
		}

		instruction.m_c_data[i] = '\0';
	}

	if (this->m_ccp_mode == "rb")
	{
		char ch = '\n';
		char* temparrr = NULL;
		int j = 0;

		instruction.m_c_data = new char[128];

		while (!feof(this->m_F_infile))	//executes the body until end of file
		{
			fgets(this->m_c_buffer, sizeof(this->m_c_buffer), this->m_F_infile);
			{
				for (int i = 0; i < 128; i++)
				{
					instruction.m_c_data[i] = this->m_c_buffer[i];
				}
			}


		}
	}


}

	