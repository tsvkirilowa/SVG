#include "File.h"
#include "Vector.h"
#include"String.h"
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
