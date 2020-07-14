#include "stdafx.h"
#include "Block29.h"




void Block29::Read(std::ifstream& input)
{
	/*input.seekg(16, ios::cur);
input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
input.seekg(4, ios::cur);
input.seekg(28, ios::cur);
if (i_null == 4)
{
	input.seekg(4, ios::cur);
}
else
{
	;
}
input.seekg(4, ios::cur);*/
	input.seekg(16, ios::cur); //xyzw
	int t29_num0;
	int t29_num1;
	input.read(reinterpret_cast<char*>(&t29_num0), sizeof(int));
	input.read(reinterpret_cast<char*>(&t29_num1), sizeof(int));
	input.seekg(12, ios::cur);
	input.seekg(12, ios::cur);
	for (int k = 0; k < t29_num0 - 2; k++)
	{
		input.seekg(4, ios::cur);
	}
	input.seekg(4, ios::cur);
}
