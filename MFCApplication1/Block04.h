#pragma once
#include "IBlock.h"
class Block04 :
    public IBlock
{
    // ������������ ����� IBlock
    virtual void Read(std::ifstream& input) override;
};

