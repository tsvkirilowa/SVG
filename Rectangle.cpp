#include "Rectangle.h"
#include<iostream>

void Rectangle::destroy()
{
	delete[] this->colour;
}

bool Rectangle::WithinCircle(int centerx, int centery, int radius)
{
    bool condition = (heightx <= (centerx - radius) && (centerx + radius) <= (heightx + heighty)) && (widhtx <= (centery - radius) && (centery + radius) <= (widhtx + widhty));
    return condition;
   
}

bool Rectangle::WithinRectangle(int heightx, int widhtx, int heighty, int widhty)
{
    if (((this->heightx + this->heighty) < (heightx + heighty)) && (this->heightx > heightx)
        && (this->widhtx > widhtx) && ((this->widhtx + this->heighty) < (widhtx + heighty)))
    {
         return true;
    }
    return false;
}

Rectangle::Rectangle()
{
   heightx=0;
   widhtx=0;
   heighty=0;
   widhty=0;
}

Rectangle::Rectangle(const Rectangle& other)
{
    heightx = other.heightx;
    widhtx = other.widhtx;
    heighty = other.heighty;
    widhty = other.widhty;
}

Rectangle::Rectangle(const int newHeightx, const int newWidhtx, const int newHeighty, const int newWidhty, const char* newColour)
{
    if (heightx < 0 || widhtx < 0 || heighty < 0 || widhty<0)
    {
        String("Invalid argument.");
    }
    heightx = newHeightx;
    widhtx = newWidhtx;
    heighty = newHeighty;
    widhty = newWidhty;
    setColour(newColour);
}

void Rectangle::setColour(const char* newColour)
{
    if (newColour != NULL)
    {
        this->destroy();
        this->colour = new char[strlen(newColour) + 1];
        strcpy_s(this->colour, strlen(newColour) + 1, newColour);
    }
}

const char* Rectangle::getColour() const
{
    return this->colour;
}

String Rectangle::ToStringPrint()
{
    String output = "";
    output = toString(heightx) + " " + toString(widhtx) + " " + toString(heighty) + " " + toString(widhty) + " " + colour;
    return output;
}

String Rectangle::ToStringFile()
{
    String output = "";
    output = "<regtangle heightx=\"+ toString(heightx) + \" widhtx=\" + toString(widhtx) +  heighty=\" + toString(heighty) +  widhty=\" + toString(widhty) +\" colour=\" + colour + \" />";
    return output;
}

void Rectangle::Translate(int vertical, int horizontal)
{
    if ((heightx + horizontal) >= 0 && (widhtx + vertical) >= 0)
    {
        heightx += horizontal;
        widhtx += vertical;
    }
}
