#include <iostream>
#include "FrameWork/stdafx.h"
#include "FrameWork/Const.h"
#include "FrameWork/Framework.h"

int main()
{
	FRAMEWORK->Init(1920, 1080);
	FRAMEWORK->Do();

	return 0;

}