#pragma once
#include "IBlock.h"
class Block31 :
    public IBlock
{
    virtual void Read(std::ifstream& input) override;
};

