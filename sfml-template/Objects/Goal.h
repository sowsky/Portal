#pragma once
#include "SpriteObj.h"
class Goal :
    public SpriteObj
{
public:
    Goal();
    virtual ~Goal();

    virtual SpriteObj* NewThis();

    void SetDoor(bool Isopen);
public:
    static int GetGoalNum();
protected:
    static int goalNum;
    bool on;
};

