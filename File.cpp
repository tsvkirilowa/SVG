#include "File.h"
#include "Vector.h"
#include"String.h"
#include<iostream>
//#include<string>

void File::splitInput(String& input, Vector<String>& tokens, Vector<char> delimiters)
{
    char* memblock = &input[0];
    String temp = "";

    for (size_t i = 0; i < input.lenght(); i++)
    {
        bool condition = false;
        for (size_t j = 0; j < delimiters.getSize(); j++)
        {

            condition = condition || (memblock[i] == delimiters[j]);

        }
        if (condition)
        {
            if (temp != "")
            {
                tokens.push_back(temp);
                temp = "";
            }
        }
        else
        {
            temp=temp + memblock[i];
        }

    }
    if (temp != "")
    {
        tokens.push_back(temp);
    }
}

String File::print(Vector<String> collection)
{
    {
        String output = "";
        for (size_t i = 0; i < collection.getSize(); i++)
        {
            output += collection[i];
            output += "\n";
        }
        return output;
    }
}

void File::DataExtraction(Vector<block<String>>& file, String& path)
{
    std::ifstream svgFile(path.c_str());

    if (svgFile.is_open())
    {
        String line;
        Vector<String> svgPart, notSvgLines;
        int fileLocation = 0;

        while (getline(svgFile, line))
        {
            bool svgOpenTag = false;
            bool svgCloseTag = false;

            if (line.lenght() > 0)
            {
                svgOpenTag = ContainsElement(line, "<svg>");
                svgCloseTag = ContainsElement(line, "</svg>");
                if (svgOpenTag && !svgCloseTag)
                {
                    if (!notSvgLines.isEmpty())
                    {
                        Vector<String> cveti;
                        String str = "NOTSVGSTART";
                        cveti.push_back(str);
                        file.push_back({ cveti,-1 });
                        file.push_back({ notSvgLines,fileLocation });
                        fileLocation++;
                        Vector<String> cvet;
                        String s1 = "NOTSVGEND";
                        cveti.push_back(s1);
                        file.push_back({ cvet,-1 });
                        notSvgLines.clear();
                    }
                    while (getline(svgFile, line))
                    {
                        svgCloseTag = ContainsElement(line, "</svg>");
                        if (svgCloseTag)
                        {
                            break;
                        }
                        else
                        {
                            svgPart.push_back(line);
                        }
                    }

                    if (!svgCloseTag)
                    {
                        throw std::string("Format error.");
                    }

                    if (!svgPart.isEmpty())
                    {
                        Vector<String> t1;
                        String str = "SVGSTART";
                        t1.push_back(str);
                        file.push_back({t1,-1 });
                        file.push_back({ svgPart,fileLocation });
                        fileLocation++;
                        Vector<String> t2;
                        String st = "SVGEND";
                        t2.push_back(st);
                        file.push_back({ t1,-1 });
                        file.push_back({t2,-1 });
                        svgPart.clear();
                    }
                }
                else if (svgCloseTag)
                {
                    throw std::string("Format error.");
                }
                else
                {
                    notSvgLines.push_back(line);
                }
            }
        }

        svgFile.close();
    }
    else
    {
        //throw std::string("Unable to open file.");
    }

    return;
}

void File::DataSaving(Vector<block<String>>& file, String path)
{
    std::ofstream svgFile(path.c_str(), std::ios::trunc);

    if (svgFile.is_open())
    {
        for (size_t i = 0; i < file.getSize(); i++)
        {
            if (file[i].id == -1 && file[i].data[0] == "SVGSTART" && (i + 2) < file.getSize())
            {
                i += 1;
                svgFile << "<svg>\n";
                svgFile << print(file[i].data);
            }
            else if (file[i].id == -1 && file[i].data[0] == "SVGEND")
            {
                svgFile << "</svg>\n";
            }
            else if (file[i].id == -1 && file[i].data[0] == "NOTSVGSTART" && (i + 2) < file.getSize())
            {
                i += 1;
                svgFile << print(file[i].data);
            }
        }
        svgFile.close();
    }
}

void File::CreateObjects(Vector<block<String>>& svgElements, Vector<block<Shape*>>& objects)
{
    Vector<String> tokens;
    Vector<Shape*> shapes;

    Shape* shape = nullptr;
    for (size_t i = 0; i < svgElements.getSize(); i++)
    {
        shapes.clear();
        int blockId = svgElements[i].id;
        for (size_t j = 0; j < svgElements[i].data.getSize(); j++)
        {
            tokens.clear();
            if (!svgElements[i].data[j].isEmpty())
            {
                Vector<char> charVector;
                charVector.push_back(' ');
                charVector.push_back('<');
                charVector.push_back('>');
                charVector.push_back('/');
                charVector.push_back('=');
                charVector.push_back('\"');
                splitInput(svgElements[i].data[j], tokens, charVector);
                if (tokens[0] == "rect")
                {
                    int heightx = 0, widhtx = 0, heighty = 0, widhty = 0;
                    String colour = "";
                    if (tokens.getSize() == 11 && StringToInt(tokens[2], heightx) && StringToInt(tokens[4], widhtx) && StringToInt(tokens[6], heighty) && StringToInt(tokens[8], widhty))
                    {
                        colour = tokens[10];
                        shape = new Rectangle( heightx, widhtx, heighty, widhty, colour.c_str());
                        shapes.push_back(shape);
                    }
                }
                else if (tokens[0] == "circle")
                {
                    int centerx = 0, centery = 0, radius = 0;
                    String colour = "";
                    if (StringToInt(tokens[2], centerx) && StringToInt(tokens[4], centery) && StringToInt(tokens[6], radius))
                    {
                        colour = tokens[8];
                        shape = new Circle(centerx, centery, radius, colour.c_str());
                        shapes.push_back(shape);
                    }
                }
            }

        }
        objects.push_back({ shapes,svgElements[i].id });
    }
}

void File::SynchronizeFileAndShapes()
{
    int counter = 0;
    for (size_t i = 0; i < shapes.getSize(); i++)
    {
        counter = shapes[i].id;
        size_t j = 0;
        Vector<String> data;
        for (size_t k = 0; k < shapes[i].data.getSize(); k++)
        {
            data.push_back(shapes[i].data[k]->ToStringFile());
        }
        while (j < file.getSize() && file[j].id != counter)
        {
            j++;
        }
        if (file[j].id == counter)
        {
            file[j].data.clear();

            file[j].data = data;
        }
        else
        {
            size_t lastSVGTagIndex = 0;
            for (size_t k = 0; i < file.getSize(); i++)
            {
                if (file[k].data.getSize() == 1 && file[k].data[0] == "SVGSTART")
                {
                    lastSVGTagIndex = k + 2;
                }
            }

            file.push_back({ Vector<String>{},0 });
            for (size_t k = file.getSize() - 1; k > lastSVGTagIndex; k--)
            {
                file[k] = file[k - 1];
            }
            file[lastSVGTagIndex + 1].data = data;
            file[lastSVGTagIndex + 1].id = counter;

        }
    }
}

bool File::ContainsElement(String& text, String element)
{
    bool contains = false;

    if (text.lenght() > 0)
    {
        char* memblock = &*text.begin();
        for (size_t i = 0; i < text.lenght() - element.lenght() + 1; i++)
        {
            for (size_t j = 0; j < element.lenght(); j++)
            {
                if (memblock[i + j] == element[j])
                {
                    contains = true;
                }
                else
                {
                    contains = false;
                    break;
                }
            }
            if (contains)
            {
                break;
            }
        }
    }
    return contains;
}

void File::ExtractSvg(Vector<block<String>>& file, Vector<block<String>>& svgElements)
{
    for (size_t i = 0; i < file.getSize(); i++)
    {
        if (file[i].id == -1 && file[i].data[0] == "SVGSTART" && (i + 1) < file.getSize())
        {
            i++;
            block<String> data = file[i];
            svgElements.push_back(data);
        }
    }
}


bool StringToInt(String& strInt, int& integer)
{//trqbva da si napisha begin() v stringa
    char* memblock = &*strInt.begin();
    int number = 0;
    for (size_t i = 0; i < strInt.lenght(); i++)
    {
        if (isdigit(memblock[i]))
        {
            number *= 10;
            number += (memblock[i] - '0');
        }
        else
        {
            return false;
        }
    }
    integer = number;
    return true;
}

File::File()
{
    path = "";
    file.clear();
    shapes.clear();
    localId = 100;
}

String File::Open(String path)
{
    localId = 100;
    this->path = path;
    String message = "\"";
    message+=path + "\" has been opened.";
    DataExtraction(file, path);
    Vector<block<String>> svgElements;
    ExtractSvg(file, svgElements);
    CreateObjects(svgElements, shapes);

    return message;
}

String File::Save()
{
    SynchronizeFileAndShapes();
    DataSaving(file, path);
    String mes = "Successfully  save \"";
    mes += path + "\"";
    return mes;
}

String File::SaveAs(String newPath)
{
    SynchronizeFileAndShapes();
    DataSaving(file, newPath);
    String mes = "Successfully saved \"";
    mes+= newPath + "\"";
    return mes;
       
}

String File::CreateShape(Vector<String> parameters)
{
    Shape* shape = NULL;
    String shapeName = parameters[0];
    if (shapeName == "rectangle" && parameters.getSize() == 6)
    {
        int heightx = 0, widhtx = 0, heighty = 0, widhty = 0;
        String colour = "";
        if (StringToInt(parameters[1], heightx) && StringToInt(parameters[2], widhtx) && StringToInt(parameters[3], heighty) && StringToInt(parameters[4], widhty))
        {
            Vector<Shape*> t5;
            colour = parameters[5];
            shape = new Rectangle(heightx, widhtx, heighty, widhty, colour.c_str());
            t5.push_back(shape);
            shapes.push_back({t5, localId++ });
        }
    }
    else if (parameters[0] == "circle" && parameters.getSize() == 5)
    {
        int centerx = 0, centery = 0, radius = 0;
        String colour = "";
        if (StringToInt(parameters[1], centerx) && StringToInt(parameters[2], centery) && StringToInt(parameters[3], radius))
        {
            Vector<Shape*> temp;
            colour = parameters[4];
            shape = new Circle( centerx, centery, radius, colour.c_str());
            temp.push_back(shape);
            shapes.push_back({ temp, localId++ });
        }
    }
    else
    {
        throw std::string("Not supported shape.");
    }
    String mes = "Successfully created a ";
    mes += parameters[0];
    return mes;
}

Vector<block<Shape*>>& File::GetShapes()
{
    return shapes;
}

String File::FileName()
{
    return path;
}

