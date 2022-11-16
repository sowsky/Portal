#pragma once
#include "WireableObject.h"

class Button;
class Goal : public WireableObject
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

