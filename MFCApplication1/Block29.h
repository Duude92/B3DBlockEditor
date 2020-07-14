#pragma once
#include "IBlock.h"
class Block29 :
    public IBlock
{
    virtual void Read(std::ifstream& input) override;
};

