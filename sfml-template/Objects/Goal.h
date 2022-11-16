#pragma once
#include "SpriteObj.h"
#include "Button.h"
#include <list>

class Button;

class Goal :
    public SpriteObj
{
public:
    Goal();
    Goal(Vector2f currgrid, float size,string buttonlist);
    virtual ~Goal();

    virtual SpriteObj* NewThis();

    virtual void Update(float dt);
    virtual void Draw(RenderWindow& window);
    void Setbutton(Button* but) { button.push_back(but); }

    void SetDoor(bool Isopen);

    bool IsFinish() { return on; }

    void SetButtonlist(vector<Button*>& button);
public:
    static int GetGoalNum();
protected:
    list<Button*> button;
    vector<int>buttonid;
    static int goalNum;
    bool on;
};

