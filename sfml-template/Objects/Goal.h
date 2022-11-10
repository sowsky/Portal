#pragma once
#include "SpriteObj.h"
class Goal :
    public SpriteObj
{
public:
    Goal();
    virtual ~Goal();

    virtual SpriteObj* NewThis();
protected:
    
};

