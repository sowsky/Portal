#pragma once
#include "WireableObject.h"
#include "SpriteObj.h"
#include "Button.h"
#include <list>

class Button;

class Goal : public WireableObject

{
public:
    Goal();
    Goal(Vector2f currgrid, float size, vector<int> buttonlist);
    virtual ~Goal();

    virtual SpriteObj* NewThis();

    virtual void Update(float dt);
    virtual void Draw(RenderWindow& window);
    void Setbutton(Button* but) { button.push_back(but); }
    bool GetOn() { return on; }

    void SetDoor(float dt);

    bool IsFinish() { return on; }

    virtual void SetButtonlist(vector<Button*>& button);
    virtual void SetButtonList(vector<int> idList) { buttonid = idList; }
    
protected:
    list<Button*> button;
    vector<int>buttonid;    
    bool on;

    VertexArray door;
    float leftDoorTexCoords;
    float rightDoorTexCoords;

    Texture* doorTex;
    float leftDoorPos;
    float rightDoorPos;

    
};