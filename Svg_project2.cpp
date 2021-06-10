#include <iostream>
#include"Circle.h"
#include "Shape.h"
# include "Vector.h"
#include"Rectangle.h"
#include"File.h"
#include"Engine.h"

int main()
{
    Engine engine;
    engine.Run();
    /*Vector<Shape*> shapes;
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
    
    return 0;*/
    /*File workingFile;
    Vector<block<String>> file, svg;
    String path = "D:/Tsveti/ФМИ/OPP- praktikum/svg/Svg_project/Svg_project2/test.svg";
    workingFile.DataExtraction(file, path);
    for (size_t i = 0; i < file.getSize(); i++)
    {
        for (size_t j = 0; j < file[i].data.getSize(); j++)
        {

            std::cout << file[i].data[j] << std::endl;

        }
        std::cout << file[i].id << std::endl;
    }



    return 0;*/
   
}

