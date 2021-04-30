#include <iostream>
#include"Circle.h"
#include "Shape.h"
# include "Vector.h"
#include"Rectangle.h"

int main()
{
    Vector<Shape*> shapes;
    shapes.push_back(new Circle(5,4,3,"red"));
    shapes.push_back(new Rectangle(2, 2, 3, 3, "blue"));
    for (size_t i = 0; i < shapes.getSize(); i++)
    {
        std::cout << shapes[i]->ToStringPrint() << std::endl;
      
    }
   shapes[0]->Translate(1, 1);
   shapes[1]->Translate(2, 2);
    for (size_t i = 0; i < shapes.getSize(); i++)
    {
        std::cout << shapes[i]->ToStringPrint() << std::endl;


    }
    
    return 0;
   
}

