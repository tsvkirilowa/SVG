#include "Engine.h"
#include<iostream>

Engine::Engine()
{
}
void Engine::Run()
{
    /*String input;
    Controller conttroler;
    String message;
   
  
    std::cin >> input;
    while (input != "out") {
        if (input== "open" )
        {
            String path;
            std::cin >> path;
            String message = conttroler.Open(path);
        }
        else if(input=="close"){
            
            message = controller.Close();

        }
        else if (input == "save") {

            message = controller.Save();
        }
        else if (input == "saveas") {

            String path;
            std::cin >> path;
            String message = conttroler.SaveAs(path);
        }
        else if (input == "help") {

            message = controller.Help();
            message.print();
        }
        else if (input == "exit") {

           controller.Exit();
        }
        else if (input == "print") {

            message = controller.Print();
        }
        else if (input == "create" )
        {
            int m;
            std::cin >> m;
            Vector<String> tokens;
            
            for (size_t i = 0; i < m; i++)
            {
                String temp;
                getline(std::cin, temp);
                tokens[i] = temp;
                  
            }
            // Removing the "create" from the collection.
            for (size_t i = 0; i < tokens.getSize()-1; i++)
            {
           
                tokens[i] = tokens[i + 1];
            }
            tokens.pop_back();

            message = controller.Create(tokens);
        }
        else{
            String newInput;
            std::cin >> newInput;
            input = newInput;
        }
            



    }*/
    /*
    String input;
    String command = "";
    String message = "";
    Vector<String> tokens;

    while (true)
    {
        try {
            std::cout << "@>";
           // getline(std::cin, input);
            std::cin >> input;
            tokens.clear();
            message = "";
            Vector<char> charVector;
            charVector.push_back(' ');
            charVector.push_back('\t');
            charVector.push_back('\n');
            
            if (input.lenght() > 0)
            {

                SplitInput(input, tokens, charVector);
                if (!tokens.isEmpty())
                {
                    command = tokens[0];
                    size_t size = tokens.getSize();

                    if (command == "open" && size == 2)
                    {
                        String path = tokens[1];
                        message = controller.Open(path);
                    }
                    else if (command == "close" && size == 1)
                    {
                        message = controller.Close();
                    }
                    else if (command == "save" && size == 1)
                    {
                        message = controller.Save();
                    }
                    else if (command == "saveas" && size == 2)
                    {
                        String path = tokens[1];
                        message = controller.SaveAs(path);
                    }
                    else if (command == "help" && size == 1)
                    {
                        message = controller.Help();
                    }
                    else if (command == "exit" && size == 1)
                    {
                        controller.Exit();
                    }
                    else if (command == "print" && size == 1)
                    {
                        message = controller.Print();
                    }
                    else if (command == "create" && size > 1)
                    {
                        // Removing the "create" from the collection.
                        for (size_t i = 0; i < tokens.getSize() - 1; i++)
                        {
                            tokens[i] = tokens[i + 1];
                        }
                        tokens.pop_back();

                        message = controller.Create(tokens);
                    }
                    else if (command == "erase" && size == 2)
                    {
                        int possition = StringToInt(tokens[1]);
                        message = controller.Erase(possition);
                    }
                    else if (command == "within")
                    {
                        //Removing the "withing" from the collection.
                        for (size_t i = 0; i < tokens.getSize() - 1; i++)
                        {
                            tokens[i] = tokens[i + 1];
                        }
                        tokens.pop_back();
                        if (!tokens.isEmpty())
                        {
                            message = controller.Within(tokens);
                        }
                        else
                        {
                            message = "Invalid input.";
                        }
                    }
                    else if (command == "translate" && (size == 2 || size == 3 || size == 4))
                    {
                        message = controller.Translate(tokens);
                    }
                    else if (command == "clear" && size == 1)
                    {
                        system("CLS");
                    }
                    else
                    {
                        message = "Invalid command.";
                    }

                    if (message.lenght() > 0)
                    {
                        std::cout << message << std::endl;
                    }

                }
            }
        }
        catch (String ms)
        {
            std::cout << ms << std::endl;
            if (ms == "Exiting the program...")
            {
                break;
            }
        }
    }*/
std::cout << "Welcome to your personal callendar!" << std::endl;
char commandTxt[256];
Controller conttroler;

do
{
    std::cout << "> ";

    std::cin.getline(commandTxt, 256);

    Vector<String> command = String(commandTxt).split(' ');

    if (strcmp(command[0].c_str(), "open") == 0) {
        controller.Open(command[1]);
    }
    else if (strcmp(command[0].c_str(), "close") == 0) {
        controller.Close();
    }
    else if (strcmp(command[0].c_str(), "save") == 0) {
        controller.Save();
    }
    else if (strcmp(command[0].c_str(), "saveas") == 0) {
        controller.SaveAs(command[1]);
    }
    else if (strcmp(command[0].c_str(), "help") == 0)
    {
        controller.Help();
    }
    else if (strcmp(command[0].c_str(), "exit") == 0) {
        std::cout << "Bye! :)" << std::endl;
        break;
    }
} while (strcmp(commandTxt, "exit") != 0);
    
}

void Engine::SplitInput(String& input, Vector<String>& tokens, Vector<char> delimiters)
{
    char* memblock = &*input.begin();
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
            temp += memblock[i];
        }

    }
    if (temp != "")
    {
        tokens.push_back(temp);
    }
}

int Engine::StringToInt(String& input)
{
    int num = 0;
    for (size_t i = 0; i < input.lenght(); i++)
    {
        if (isdigit(input[i]))
        {
            num *= 10;
            num += (input[i] - '0');
        }
        else if (i > 0)
        {
            throw std::string("Invalid input.");
        }
    }
    if (input.lenght() > 0 && input[0] == '-')
    {
        num *= (-1);
    }
    return num;
}