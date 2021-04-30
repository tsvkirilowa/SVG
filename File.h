#pragma once
#include"Shape.h"
#include"Circle.h"
#include"Vector.h"

class File
{
    String path;
    Vector<String> file;
    Vector<Shape*> shapes;
    int localId; 

    void splitInput(String& input, Vector<String>& tokens, Vector<char> delimiters);
    String print(Vector<String> collection);

};
