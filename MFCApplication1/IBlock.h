#pragma once
#include <fstream>
using namespace std;
class IBlock
{
public:
	virtual void Read(std::ifstream& input) = 0;

protected: void Dispose();
};

