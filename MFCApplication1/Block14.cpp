#include "stdafx.h"
#include "Block14.h"

void Block14::Read(std::ifstream& input)
{
	input.seekg(16, ios::cur); //xyzw
	input.seekg(16, ios::cur); //xyzw (1)
	int t14_some_var;
	int t14_var0;
	int t14_var1;

	input.read(reinterpret_cast<char*>(&t14_some_var), sizeof(int));
	input.read(reinterpret_cast<char*>(&t14_var0), sizeof(int));
	input.read(reinterpret_cast<char*>(&t14_var1), sizeof(int));
	if (t14_some_var > 99) {
		int skip_len = 0;
		int name_len = strlen(objName);

		if (name_len > 15) {
			skip_len = 20;
		}
		else if (11 < name_len <= 15) {
			skip_len = 16;
		}
		else if (7 < name_len <= 11) {
			skip_len = 12;
		}
		else if (3 < name_len <= 7) {
			skip_len = 8;
		}
		else if (name_len <= 3) {
			skip_len = 4;
		}

		input.seekg(skip_len, ios::cur);
	}
}
