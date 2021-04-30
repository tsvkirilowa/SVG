#pragma once
#include"Shape.h"

class Rectangle :public Shape
{
private:
	int heightx;
	int widhtx;
	int heighty;
	int widhty;

	char* colour;
	void destroy();

	//virtual bool WithinCircle(int centerx, int centery, int radius) override;
	//virtual bool WithinRectangle(int x, int y, int width, int height) override;
public:
	Rectangle();
	Rectangle(const Rectangle& other);
	Rectangle (const int newHeightx, const int newWidhtx, const int newHeighty, const int newWidhty, const char* newColour);

	void setColour(const char* newColour);
	const char* getColour()const;

	virtual String ToStringPrint() override;
	virtual String ToStringFile() override;
	virtual void Translate(int, int) override;

};

