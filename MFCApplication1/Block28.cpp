#include "stdafx.h"
#include "Block28.h"

void Block28::Read(std::ifstream& input)
{

	//После всего, что между нами было, как я могу не сохранить данный кусочек сладкого кода
//input.seekg(16, ios::cur);
//input.seekg(12, ios::cur);
//input.read(reinterpret_cast<char*>(&i_null), sizeof(int));
//int i_null1, i_null2;

//if (i_null == 1)
//{
//	input.read(reinterpret_cast<char*>(&i_null1), sizeof(int));
//	input.seekg(12, ios::cur);
//	input.read(reinterpret_cast<char*>(&i_null2), sizeof(int));

//	if (i_null1 > 1)
//	{
//		for (int i = 0; i < i_null2; i++)
//		{
//			input.seekg(16, ios::cur);
//		}
//	}
//	else
//	{
//		input.seekg(32, ios::cur);
//	}
//}
//else if (i_null == 2)
//{
//	input.seekg(20, ios::cur);
//	for (int i = 0; i < 4; i++)
//	{
//		input.seekg(28, ios::cur);
//	}
//	//input.read(reinterpret_cast<char*>(&testkey), sizeof(int));

//	input.seekg(4, ios::cur);
//}
//else if ((i_null == 10) || (i_null == 6))
//{
//	for (int i = 0; i < i_null1; i++)
//	{
//		input.seekg(16, ios::cur);
//		input.read(reinterpret_cast<char*>(&i_null2), sizeof(int));
//		for (int j = 0; j < i_null2; j++)
//		{
//			input.seekg(8, ios::cur);
//		}
//	}
//}




	input.seekg(16, ios::cur); //xyzw
	input.seekg(12, ios::cur);

	//int t28_var0;
	//int t28_var1;
	//int t28_var2;

	//input.read(reinterpret_cast<char*>(&t28_var0), sizeof(int));
	//input.read(reinterpret_cast<char*>(&t28_var1), sizeof(int));
	//input.read(reinterpret_cast<char*>(&t28_var2), sizeof(int));

	int t28_num;
	input.read(reinterpret_cast<char*>(&t28_num), sizeof(int));

	for (int i = 0; i < t28_num; i++)
	{
		int t28_format;
		input.read(reinterpret_cast<char*>(&t28_format), sizeof(int));
		input.seekg(4, ios::cur); // float var
		input.seekg(4, ios::cur); // num_32767
		input.seekg(4, ios::cur); // texNum
		int vertNum;
		input.read(reinterpret_cast<char*>(&vertNum), sizeof(int));
		if (t28_format == 0) {
			for (int k = 0; k < vertNum; k++)
			{
				input.seekg(8, ios::cur);
			}
		}


		if (t28_format == 256 || t28_format == 1 || t28_format == 2) {
			for (int k = 0; k < vertNum; k++)
			{
				input.seekg(16, ios::cur);
			}
		}

		if (t28_format == -256) {
			for (int k = 0; k < vertNum; k++)
			{
				input.seekg(8, ios::cur);
			}
		}

	}

}
