#include "WireableObject.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Utils.h"
#include "../FrameWork/Const.h"
#include "../Objects/Button.h"
//#include "../Objects/NumBox.h"

Phase WireableObject::phase = Phase::None;

WireableObject::WireableObject()
{

}

WireableObject::~WireableObject()
{
	//if (!numbox.empty())
	//{
	//	for (auto i : numbox)
	//	{
	//		delete i;
	//	}
	//}
	//numbox.clear();

	if (!wires.empty())
	{
		for (auto w : wires)
			delete w;

		wires.clear();
	}
}

void WireableObject::Init()
{
	Object::Init();
	SetWireCheckBox();
	orange = RESOURCEMGR->GetTexture("Graphics/orange.png");
	blue = RESOURCEMGR->GetTexture("Graphics/blue.png");
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

	//if (!numbox.empty() && isWiring)
	//{
	//	for (auto i : numbox)
	//	{
	//		i->Draw(window);
	//	}
	//}
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
		wires.back()->buttonNum = temp->GetButtonId();
		wires.back()->isConnected = false;
		wires.back()->wire.setPrimitiveType(Lines);
		wires.back()->wire.resize(2);
	}

	if (phase == Phase::CatcherSelect
		&& InputMgr::GetMouseButtonDown(Mouse::Right))
	{
		SetPhase(Phase::TriggerSelect);
		delete wires.back();
		wires.pop_back();
	}

	if (wires.empty())
		return;

	wires.back()->wire[0].position = position;
	wires.back()->wire[1].position
		= window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());


	for (auto w : wires)
	{
		window.draw(w->wire, w->isConnected ? orange : blue);			
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

list<int> WireableObject::GetWireListFromMapTool()
{
	list<int> temp;

	//for (auto boxnum : numbox)
	//{
	//	temp.push_back(boxnum->GetNum());
	//}

	return temp;
}
