#include "WireableObject.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Utils.h"
#include "../FrameWork/Const.h"
#include "../Objects/Button.h"
//#include "../Objects/NumBox.h"

Phase WireableObject::phase = Phase::None;
WireableObject* WireableObject::targetCatcherPtr = nullptr;
Wire* WireableObject::currWire = nullptr;

WireableObject::WireableObject()
{

}

WireableObject::~WireableObject()
{
	if (type == ObjectType::Trigger
		&& !wires.empty())
	{
		for (auto w : wires)
		{
			if (w->isActive)
			{
				list<Wire*>& targetWires = w->targetPtr->GetWireList();
				auto targetIt = targetWires.begin();
				{
					while (targetIt != targetWires.end())
					{
						if ((*targetIt)->buttonNum == w->buttonNum)
						{
							targetIt = targetWires.erase(targetIt);
						}
						else ++targetIt;
					}
				}
			}
			delete w;
		}	
		wires.clear();
	}
}

void WireableObject::Init()
{
	Object::Init();
	SetWireCheckBox();
}

void WireableObject::Update(float dt)
{

}

void WireableObject::Update(float dt, Vector2f mouse)
{

}

void WireableObject::Draw(RenderWindow& window)
{	
	SpriteObj::Draw(window);
	WireModDraw(window);
}

void WireableObject::SetWireCheckBox()
{
	wireCheckBox.setTexture(RESOURCEMGR->GetTexture("Graphics/Ui/wirebox.png"));
	wireCheckBox.setSize((Vector2f)sprite.getTexture()->getSize());
	Utils::SetOrigin(wireCheckBox, Origins::BC);
	Vector2f scale = sprite.getScale();
	wireCheckBox.setSize((Vector2f)sprite.getTexture()->getSize());
	wireCheckBox.setScale(scale);
	wireCheckBox.setPosition(sprite.getPosition());
	wireCheckBox.setRotation(sprite.getRotation());
}

void WireableObject::WireModDraw(RenderWindow& window)
{
	isMouseIn = false;
	Vector2f mouseWorldPos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());
	isMouseIn = wireCheckBox.getGlobalBounds().contains(mouseWorldPos);

	wireCheckBox.setFillColor(isMouseIn ? Color(248, 147, 30) : Color(37, 255, 254));

	if(isWiring)
		DrawWire(window);

	if (isWiring && isInMapTool)
	{
		if (phase == Phase::TriggerSelect
			&& type == ObjectType::Trigger)
			window.draw(wireCheckBox);

		if (phase == Phase::CatcherSelect
			&& type == ObjectType::Catcher)
			window.draw(wireCheckBox);
	}	
}

void WireableObject::DrawWire(RenderWindow& window)
{
	if (isMouseIn && type == ObjectType::Trigger
		&& phase == Phase::TriggerSelect
		&& InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		SetPhase(Phase::CatcherSelect);
		Button* temp = (Button*)this;		
		wires.push_back(new Wire);
		currWire = wires.back();
		wires.back()->buttonNum = temp->GetButtonId();
	}

	if (phase == Phase::CatcherSelect
		&& InputMgr::GetMouseButtonDown(Mouse::Right)
		&& !wires.back()->isConnected)
	{
		delete wires.back();		
		wires.pop_back();
		SetPhase(Phase::TriggerSelect);
	}

	if (phase == Phase::CatcherSelect
		&& InputMgr::GetMouseButton(Mouse::Left)
		&& type == ObjectType::Catcher
		&& isMouseIn)
	{
		targetCatcherPtr = this;		
		wires.push_back(currWire);
	}

	if (wires.empty())
		return;

	if (type == ObjectType::Trigger)
		for (auto& w : wires)
		{			
			w->wire[0].position = sprite.getPosition();
		}
	
	if (!wires.back()->isConnected)
	{
		if(!targetCatcherPtr)
			wires.back()->wire[1].position
			= window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());
		else
		{			
			wires.back()->targetPtr = targetCatcherPtr;
			//wires.back()->wire[1].position = targetCatcherPtr->GetSpritePos();
			wires.back()->isConnected = true;
			targetCatcherPtr = nullptr;
			currWire = nullptr;
			phase = Phase::TriggerSelect;	
		}
	}

	if(type == ObjectType::Trigger)
		for (auto w : wires)
		{
			if (w->isActive)
			{
				if(w->isConnected)
					w->wire[1].position = w->targetPtr->GetSpritePos();
				
				window.draw(w->wire);
			}
		}
}

//void WireableObject::AddNumBox(NumBox* nb)
//{	
//	if (numbox.empty())
//	{
//		numbox.push_back(new NumBox);
//		numbox.back()->SetNum(nb->GetNum());
//		numbox.back()->SetPos(GetPos());
//	}
//	else
//	{
//		Vector2f pos = numbox.back()->GetPos();
//		Vector2f fixPos{ NUMBOX_SIZE, 0 };
//		numbox.push_back(new NumBox);
//		numbox.back()->SetNum(nb->GetNum());
//		numbox.back()->SetPos(pos + fixPos);
//	}
//}
//
//void WireableObject::AddNumBox(int num)
//{
//	numbox.push_back(new NumBox);
//	numbox.back()->SetNum(num);
//	numbox.back()->SetPos(sprite.getPosition());
//}
//
//void WireableObject::RemoveNumBox()
//{
//	if (numbox.empty())
//		return;
//
//	delete numbox.back();
//	numbox.pop_back();
//}

void WireableObject::AddWire(WireableObject* target)
{	
	Button* temp = (Button*)this;
	wires.push_back(new Wire);	
	wires.back()->buttonNum = temp->GetButtonId();
	wires.back()->targetPtr = target;	
	wires.back()->isConnected = true;	
}

list<int> WireableObject::GetWireListFromMapTool()
{
	list<int> temp;

	//for (auto boxnum : numbox)
	//{
	//	temp.push_back(boxnum->GetNum());
	//}

	return temp;
}
