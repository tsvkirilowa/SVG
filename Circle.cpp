#include "Circle.h"
#include"String.h"

void Circle::destroy()
{
	delete[] this->colour;
}

bool Circle::WithinCircle(int centerx, int centery, int radius)
{
	double x = centerx - this->centerx;
	double y = centery - this->centery;
	double distance = sqrt(x * x + y * y);
	if (distance + this->radius <= radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Circle::WithinRectangle(int heightx, int widthx, int heighty, int widthy)
{
	bool condition = (heightx <= (centerx - radius) && (centerx + radius) <= (heightx + heighty)) && (widthx <= (centery - radius) && (centery + radius) <= (widthx + widthy));
	return condition;
}

Circle::Circle()
{
	centerx = 0;
	centery = 0;
	radius = 1;
}

Circle::Circle(const Circle& other)
{
	centerx = other.centerx;
	centery = other.centery;
	radius = other.radius;
}

Circle::Circle(const int newCenterx, const int newCentery, const int newRadius, const char* newColour)
{
	if (centerx < 0 || centery < 0 || radius < 0)
	{
		String("Invalid argument.");
	}
	centerx = newCenterx;
	centery = newCentery;
	radius = newRadius;
	setColour(newColour);	
}

/*void Circle::setCenterx(int newCenterx)
{
	this->centerx = newCenterx;
}

void Circle::setCentery(int newCentery)
{
	this->centery = newCentery;
}

void Circle::setRadius(int newRadius)
{

	this->radius = newRadius;
}

int Circle::getCenterx() const
{
	return this-> centerx;
}

int Circle::getCentery() const
{
	return this->centery;
}

int Circle::getRadius() const
{
	return this->radius;
}*/

void Circle::setColour(const char* newColour)
{
	if (newColour != NULL)
	{
		this->destroy();
		this->colour = new char[strlen(newColour) + 1];
		strcpy_s(this->colour, strlen(newColour) + 1, newColour);
	}
}

const char* Circle::getColour() const
{
	return this->colour;
}

String Circle::ToStringPrint()
{
	String output = "";
	output = toString(centerx) + " " + toString(centery) + " " + toString(radius) + " " + colour;
	return output;
}

String Circle::ToStringFile()
{
	String output = "";
	output = "<circle centerx=\"+ toString(centerx) + \" centery=\" + toString(centery) +  radius=\" + toString(radius) + \" colour=\" + colour + \" />";
	return output;
}

void Circle::Translate(int vertical, int horizontal)
{
	if ((centerx + horizontal) >= 0 && (centery + vertical) >= 0)
	{
		centerx += horizontal;
		centery += vertical;
	}
}
