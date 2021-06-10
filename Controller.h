#pragma once
#include"File.h"
#include "Shape.h"
#include"String.h"
#include"Vector.h"
class Controller
{
public:
	Controller();

	String Open(String);
	String Close();
	String Save();
	String SaveAs(String);
	String Help();
	void Exit();

	String Print();
	String Create(Vector<String>);
	String Erase(int);

	String Within(Vector<String>&);
	String Translate(Vector<String> tokens);

private:
	File* currentFile;
	Vector<File> files;

	String Translate(int, int, int = -1);

	void SplitInput(String& input, Vector<String>& tokens, Vector<char> delimiters);

};
