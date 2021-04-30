#pragma once
#include "String.h"

class Shape
{
public:
	Shape()
	{

	}
	virtual void Translate(int, int) = 0;
	virtual String ToStringPrint() = 0;
	virtual String ToStringFile() = 0;
	//virtual bool WithinCircle(int, int, int) = 0;
	//virtual bool WithinRectangle(int, int, int, int) = 0;
};