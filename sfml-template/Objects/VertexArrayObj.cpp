#include "VertexArrayObj.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h";
#include "../FrameWork/Const.h"

void VertexArrayObj::SetDepth(float dp)
{
	depth = dp;
}

void VertexArrayObj::SetAllSidesTex(string id)
{
	texSize = RESOURCEMGR->GetTexture(id)->getSize();		

	for (int i = 0; i < sides.size(); i++)
	{		
		tileTextures[i] = RESOURCEMGR->GetTexture(id);
		sides[i].first = true;
		sides[i].second.setPrimitiveType(Quads);
		sides[i].second.resize(4);
		sides[i].second[0].texCoords = { 0.f, 0.f };
		sides[i].second[1].texCoords = { (float)texSize.x, 0.f };
		sides[i].second[2].texCoords = (Vector2f)texSize;
		sides[i].second[3].texCoords = { 0.f, (float)texSize.y };
	}
}

void VertexArrayObj::SetBackFaceOrigin(Origins origin)
{
	Utils::SetOrigin(backFace, origin);
}

void VertexArrayObj::SetBackFaceSize(Vector2f size)
{
	float dp = depth * 2 - 1.f;
	backFace.setSize({ size.x * dp, size.y * dp });	
}

void VertexArrayObj::ChageCoords(Vector2u texSize)
{
	for (int i = 0; i < sides.size(); i++)
	{
		sides[i].second[0].texCoords = { texSize.x * 0.25f, texSize.y * 0.25f };
		sides[i].second[1].texCoords = { texSize.x * 0.75f, texSize.y * 0.25f };
		sides[i].second[2].texCoords = { texSize.x * 0.75f, texSize.y * 0.75f };
		sides[i].second[3].texCoords = { texSize.x * 0.25f, texSize.y * 0.75f };
	}
}

void VertexArrayObj::ReturnPrevCoords()
{
	for (int i = 0; i < sides.size(); i++)
	{
		sides[i].second[0].texCoords = { 0.f, 0.f };
		sides[i].second[1].texCoords = { (float)texSize.x, 0.f };
		sides[i].second[2].texCoords = (Vector2f)texSize;
		sides[i].second[3].texCoords = { 0.f, (float)texSize.y };
	}
}

void VertexArrayObj::SetTransparent(int color)
{
	for (int i = 0; i < sides.size(); i++)
	{
		sides[i].second[0].color = Color(255, 255, 255, color);
		sides[i].second[1].color = Color(255, 255, 255, color);
		sides[i].second[2].color = Color(255, 255, 255, color);
		sides[i].second[3].color = Color(255, 255, 255, color);
	}
}

void VertexArrayObj::Update()
{

}

void VertexArrayObj::Draw(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();		

	frontFace.setPosition(
		pivotSprite.getPosition() - (vanishingPoint - pivotSprite.getPosition()) * (1.f - depth)
	);	

	backFace.setPosition(
		pivotSprite.getPosition() + (vanishingPoint - pivotSprite.getPosition()) * (1.f - depth)
	);

	frontFace.setRotation(pivotSprite.getRotation());
	backFace.setRotation(pivotSprite.getRotation());	

	Vector2f backLt = backFace.getTransform().transformPoint(backFace.getPoint(0));
	Vector2f backRt = backFace.getTransform().transformPoint(backFace.getPoint(1));
	Vector2f backRb = backFace.getTransform().transformPoint(backFace.getPoint(2));
	Vector2f backLb = backFace.getTransform().transformPoint(backFace.getPoint(3));
	
	FloatRect frontRect = frontFace.getLocalBounds();
	Vector2f frontLt = frontFace.getTransform().transformPoint({ frontRect.left, frontRect.top });
	Vector2f frontRt = frontFace.getTransform().transformPoint({ frontRect.left + frontRect.width, frontRect.top });
	Vector2f frontRb = frontFace.getTransform().transformPoint({ frontRect.left + frontRect.width, frontRect.top + frontRect.height });
	Vector2f frontLb = frontFace.getTransform().transformPoint({ frontRect.left, frontRect.top + frontRect.height });	

	if (sides[0].first)
	{
		sides[0].second[0].position = backLt;
		sides[0].second[1].position = backRt;
		sides[0].second[2].position = frontRt;
		sides[0].second[3].position = frontLt;
	}

	if (sides[1].first)
	{
		sides[1].second[0].position = frontRt;
		sides[1].second[1].position = backRt;
		sides[1].second[2].position = backRb;
		sides[1].second[3].position = frontRb;
	}

	if (sides[2].first)
	{
		sides[2].second[0].position = backLb;
		sides[2].second[1].position = backRb;
		sides[2].second[2].position = frontRb;
		sides[2].second[3].position = frontLb;
	}

	if (sides[3].first)
	{
		sides[3].second[0].position = frontLt;
		sides[3].second[1].position = backLt;
		sides[3].second[2].position = backLb;
		sides[3].second[3].position = frontLb;
	}	

	//backFace.setFillColor(Color::Red);
	//window.draw(backFace);

	//window.draw(pivotSprite);

	window.draw(sides[1].second, tileTextures[1]);
	window.draw(sides[3].second, tileTextures[3]);
	window.draw(sides[0].second, tileTextures[0]);
	window.draw(sides[2].second, tileTextures[2]);
}

void VertexArrayObj::DrawRenderStates(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	frontFace.setPosition(
		pivotSprite.getPosition() - (vanishingPoint - pivotSprite.getPosition()) * (1.f - depth)
	);

	backFace.setPosition(
		pivotSprite.getPosition() + (vanishingPoint - pivotSprite.getPosition()) * (1.f - depth)
	);

	frontFace.setRotation(pivotSprite.getRotation());
	backFace.setRotation(pivotSprite.getRotation());

	Vector2f backLt = backFace.getTransform().transformPoint(backFace.getPoint(0));
	Vector2f backRt = backFace.getTransform().transformPoint(backFace.getPoint(1));
	Vector2f backRb = backFace.getTransform().transformPoint(backFace.getPoint(2));
	Vector2f backLb = backFace.getTransform().transformPoint(backFace.getPoint(3));

	FloatRect frontRect = frontFace.getLocalBounds();
	Vector2f frontLt = frontFace.getTransform().transformPoint({ frontRect.left, frontRect.top });
	Vector2f frontRt = frontFace.getTransform().transformPoint({ frontRect.left + frontRect.width, frontRect.top });
	Vector2f frontRb = frontFace.getTransform().transformPoint({ frontRect.left + frontRect.width, frontRect.top + frontRect.height });
	Vector2f frontLb = frontFace.getTransform().transformPoint({ frontRect.left, frontRect.top + frontRect.height });

	if (sides[0].first)
	{
		sides[0].second[0].position = backLt;
		sides[0].second[1].position = backRt;
		sides[0].second[2].position = frontRt;
		sides[0].second[3].position = frontLt;
	}

	if (sides[1].first)
	{
		sides[1].second[0].position = frontRt;
		sides[1].second[1].position = backRt;
		sides[1].second[2].position = backRb;
		sides[1].second[3].position = frontRb;
	}

	if (sides[2].first)
	{
		sides[2].second[0].position = backLb;
		sides[2].second[1].position = backRb;
		sides[2].second[2].position = frontRb;
		sides[2].second[3].position = frontLb;
	}

	if (sides[3].first)
	{
		sides[3].second[0].position = frontLt;
		sides[3].second[1].position = backLt;
		sides[3].second[2].position = backLb;
		sides[3].second[3].position = frontLb;
	}

	//backFace.setFillColor(Color::Red);
	//window.draw(backFace);

	//window.draw(pivotSprite);

	window.draw(sides[1].second, state);
	window.draw(sides[3].second, state);
	window.draw(sides[0].second, state);
	window.draw(sides[2].second, state);
}

VertexArrayObj::VertexArrayObj(Sprite& front, Sprite& pivot)
	:frontFace(front), pivotSprite(pivot)
{
}

void VertexArrayObj::SetRotatable(bool rot)
{
	rotatable = rot;
}
