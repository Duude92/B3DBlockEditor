#pragma once
#include "IBlock.h"
class Block14 :
    public IBlock
{
public:
    virtual void Read(std::ifstream& input) override;
    char* objName;
};

