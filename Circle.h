#pragma once
#include<iostream>
#include"Shape.h"

class Circle : public Shape
{
private:
	int centerx;
	int centery;
	int radius;

	char* colour;
	void destroy();
	
	virtual bool WithinCircle(int centerx, int centery, int radius) override;
    virtual bool WithinRectangle(int heightx, int widthx, int heighty, int widthy) override;

public:
	Circle();
	Circle(const Circle& other);
	//Circle& operator=(const Circle& other);
	Circle(const int newCenterx, const int newCentery, const int newRadius, const char* newColour);

	/*void setCenterx(int newCenterx);
	int getCenterx()const;

	void setCentery(int newCentery);
	int getCentery()const;

	void setRadius(int newRadius);
	int getRadius()const;*/

	void setColour(const char* newColour);
	const char* getColour()const;

	virtual String ToStringPrint() override;
	virtual String ToStringFile() override;
	virtual void Translate(int, int) override;


};

