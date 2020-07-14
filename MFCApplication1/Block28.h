#pragma once
#include "IBlock.h"
class Block28 :
    public IBlock
{
    virtual void Read(std::ifstream& input) override;
};

