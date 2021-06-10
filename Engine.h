#pragma once
#include "Controller.h"
#include"String.h"
class Engine
{
public:
	Engine();
	void Run();
private:
	Controller controller;
	void SplitInput(String& input, Vector<String>& tokens, Vector<char> delimiters);
	int StringToInt(String& input);
};

