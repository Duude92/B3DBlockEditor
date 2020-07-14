#include "stdafx.h"
#include "Block31.h"



void Block31::Read(std::ifstream & input)
{
	input.seekg(16, ios::cur); //xyzw
	int t31_num0;
	input.read(reinterpret_cast<char*>(&t31_num0), sizeof(int));
	input.seekg(16, ios::cur);
	input.seekg(16, ios::cur);
	for (int i = 0; i < t31_num0; i++)
	{
		input.seekg(8, ios::cur);
	}
	//input.seekg(4, ios::cur);
}
