#include "stdafx.h"
#include "Block04.h"

void Block04::Read(std::ifstream& input)
{
	input.seekg(16, ios::cur);
	input.seekg(32, ios::cur);
	input.seekg(36, ios::cur);
	IBlock::Dispose();
}
