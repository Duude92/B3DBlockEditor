#include "stdafx.h"
#include "Block05.h"

void Block05::Read(std::ifstream& input)
{
	input.seekg(16, ios::cur);
	input.seekg(32, ios::cur);
	input.seekg(4, ios::cur);
	IBlock::Dispose();
}
