#pragma once
#include"Shape.h"
#include"Circle.h"
#include"Rectangle.h"
#include"Vector.h"
#include "String.h"
#include<fstream>
//#include<cstring>

template<class T>
struct block
{
    Vector<T> data;
    int id;
};

bool StringToInt(String& strInt, int& integer);

class File
{
public:
    File();

    String Open(String path);
    String Save();
    String SaveAs(String newPath);

    String CreateShape(Vector<String> parameters);
    Vector<block<Shape*>>& GetShapes();
    String FileName();

public:
    String path;
    Vector<block<String>> file;
    Vector<block<Shape*>> shapes;
    int localId; 

    void splitInput(String& input, Vector<String>& tokens, Vector<char> delimiters);
    String print(Vector<String> collection);

    // The functions for handling the reading and writing to file.
    void DataExtraction(Vector<block<String>>& file, String& path);
    void DataSaving(Vector<block<String>>& file, String path);

    // The functions for extracting only the SVG elemnts from file and creating the objects.
    void ExtractSvg(Vector<block<String>>& file, Vector<block<String>>& svgElements);
    void CreateObjects(Vector<block<String>>& svgElements, Vector<block<Shape*>>& objects);

    // Used to synchronize the file and shapes before writing to file.
    void SynchronizeFileAndShapes();

    bool ContainsElement(String& text, String element);

};
