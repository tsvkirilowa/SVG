#include "Controller.h"

Controller::Controller()
{
	currentFile = NULL;
}
String Controller::Open(String path)
{
	File* workingFile = new File();

	String message = workingFile->Open(path);

	files.push_back(*workingFile);
	currentFile = workingFile;

	return message;
}

String Controller::Close()
{
	String message = "";
	if (files.getSize() > 1)
	{
		files.pop_back();
		currentFile = &files[files.getSize() - 1];
		message += "Closed \"";
		message += currentFile->FileName() + "\"";
	}
	else if (files.getSize() == 1)
	{
		message += "Closed \"";
		message += currentFile->FileName() + "\"";
		currentFile = NULL;
		files.pop_back();
	}
	return message;
}

String Controller::Save()
{
	if (currentFile->FileName().lenght() == 0)
	{
		throw std::string("The file doesn't have default path. Please use \"saveas\" to provide a path.");
	}
	String message = currentFile->Save();
	return message;
}

String Controller::SaveAs(String path)
{
	String message = currentFile->SaveAs(path);
	return message;
}

String Controller::Help()
{
	String output = "";
	output += "The following commands are supported :\n";
	output += "close........................................................closes currently opened file\n";
	output += "save.........................................................saves the currently opened files\n";
	output += "saveas <file>................................................saves the first open file in <file>\n";
	output += "help.........................................................prints this information\n";
	output += "exit.........................................................exists the program\n";
	output += "print........................................................print all the figures\n";
	output += "create.......................................................creates a figure. For example: create rectangle 1 1 2 3 green\n";
	output += "erase <n>....................................................erases the n-th figure\n";
	output += "translate vertical:<value> horizontal:<value> [n]...........translates the n-th figure or all if n is not spesified\n";
	output += "within <option> .............................................print all the figure who are within the <option=(rectangle,circle)>\n";
	output += "clear........................................................clears the screen";
	return output;
}

void Controller::Exit()
{
	throw std::string("Exiting the program...");
}

String Controller::Print()
{
	String output = "";
	Vector<block<Shape*>> shapes;
	int counter = 1;
	for (size_t i = 0; i < files.getSize(); i++)
	{
		shapes = files[i].GetShapes();

		for (size_t j = 0; j < shapes.getSize(); j++)
		{
			for (size_t k = 0; k < shapes[j].data.getSize(); k++)
			{
				output += toString(counter) + ". " + shapes[j].data[k]->ToStringPrint();
				output += "\n";
				counter++;
			}
		}
	}
	return output;
}

String Controller::Create(Vector<String> tokens)
{
	if (!currentFile)
	{
		currentFile = new File();
	}
	String output = currentFile->CreateShape(tokens);
	if (files.getSize() > 0)
	{
		files.pop_back();
	}

	files.push_back(*currentFile);
	return output;
}

String Controller::Erase(int position)
{
	String message = "There is no figure with number ";
	message += toString(position);
	int counter = 1;
	for (int i = files.getSize() - 1; i >= 0; i--)
	{
		for (int j = 0; j < files[i].GetShapes().getSize(); j++)
		{
			for (int k = 0; k < files[i].GetShapes()[j].data.getSize(); k++)
			{
				if (counter == position)
				{
					for (int p = counter - 1; p < files[i].GetShapes()[j].data.getSize() - 1; p++)
					{
						files[i].GetShapes()[j].data[p] = files[i].GetShapes()[j].data[p + 1];
					}
					files[i].GetShapes()[j].data.pop_back();
					message = "Figure with number ";
					message += toString(position) + " has been deleted.";
					return message;
				}
				else
				{
					counter++;
				}

			}
		}
	}
	return message;
}

String Controller::Translate(int vertical, int horizontal, int possition)
{
	String message = "";
	if (possition == -1)
	{
		Vector<block<Shape*>> shapes;
		int counter = 1;
		for (size_t i = 0; i < files.getSize(); i++)
		{
			shapes = files[i].GetShapes();

			for (size_t j = 0; j < shapes.getSize(); j++)
			{
				for (size_t k = 0; k < shapes[j].data.getSize(); k++)
				{
					shapes[j].data[k]->Translate(vertical, horizontal);
				}
			}
		}

		message += "Translated all figures.";

	}
	else if (possition >= 1)
	{
		int counter = 0;
		Vector<block<Shape*>> shapes;
		for (size_t i = 0; i < files.getSize(); i++)
		{
			shapes = files[i].GetShapes();

			for (size_t j = 0; j < shapes.getSize(); j++)
			{
				for (size_t k = 0; k < shapes[j].data.getSize(); k++)
				{
					counter++;
					if (counter == possition)
					{
						shapes[j].data[k]->Translate(vertical, horizontal);
						String mes = "Translated figure: ";
						mes += toString(counter);
						return mes;
					}
				}
			}
		}
	}
	return message;
}

String Controller::Within(Vector<String>& params)
{
	Vector<Shape*> shapesWithin;
	if (params.getSize() == 4 && params[0] == "circle")
	{
		int x = 0, y = 0, r = 0;
		if (StringToInt(params[1], x) && StringToInt(params[2], y) && StringToInt(params[3], r))
		{
			for (size_t i = 0; i < files.getSize(); i++)
			{


				for (size_t j = 0; j < files[i].GetShapes().getSize(); j++)
				{
					for (size_t k = 0; k < files[i].GetShapes()[j].data.getSize(); k++)
					{
						if (files[i].GetShapes()[j].data[k]->WithinCircle(x, y, r))
						{
							shapesWithin.push_back(files[i].GetShapes()[j].data[k]);
						}
					}
				}
			}
		}
	}
	else if (params.getSize() == 5 && params[0] == "rectangle")
	{
		int x = 0, y = 0, width = 0, height = 0;
		if (StringToInt(params[1], x) && StringToInt(params[2], y) && StringToInt(params[3], width) && StringToInt(params[4], height))
		{
			for (size_t i = 0; i < files.getSize(); i++)
			{
				for (size_t j = 0; j < files[i].GetShapes().getSize(); j++)
				{
					for (size_t k = 0; k < files[i].GetShapes()[j].data.getSize(); k++)
					{
						if (files[i].GetShapes()[j].data[k]->WithinRectangle(x, y, width, height))
						{
							shapesWithin.push_back(files[i].GetShapes()[j].data[k]);
						}
					}
				}
			}
		}
	}
	String output = "";
	for (size_t i = 0; i < shapesWithin.getSize(); i++)
	{
		output += toString(i) + ". " + shapesWithin[i]->ToStringPrint() + "\n";
	}

	return output;
}

String Controller::Translate(Vector<String> tokens)
{
	String message = "";
	size_t size = tokens.getSize();
	Vector<String> firstParameter, secondParameter;
	int vertical = 0, horizontal = 0, shapeIndex = -1;
	Vector<char> charVector;
	charVector.push_back('=');

	switch (size)
	{
	case 2:

		SplitInput(tokens[1], firstParameter, charVector);
		if (firstParameter.getSize() == 2)
		{
			if (firstParameter[0] == "vertical" && StringToInt(firstParameter[1], vertical))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && StringToInt(firstParameter[1], horizontal))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else
			{
				message = "Invalid input.";
			}


		}
		else
		{
			message = "Invalid input.";

		}
		break;
	case 3:
		SplitInput(tokens[1], firstParameter, charVector);
		SplitInput(tokens[2], secondParameter, charVector);

		if (firstParameter.getSize() == 2)
		{
			if (firstParameter[0] == "vertical" && secondParameter.getSize() == 2 && secondParameter[0] == "horizontal" && StringToInt(firstParameter[1], vertical) && StringToInt(secondParameter[1], horizontal))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && secondParameter.getSize() == 2 && secondParameter[0] == "vertical" && StringToInt(firstParameter[1], horizontal) && StringToInt(secondParameter[1], vertical))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "vertical" && secondParameter.getSize() == 1 && StringToInt(firstParameter[1], vertical) && StringToInt(secondParameter[0], shapeIndex))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && secondParameter.getSize() == 1 && StringToInt(firstParameter[1], horizontal) && StringToInt(secondParameter[0], shapeIndex))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else
			{
				message = "Invalid input.";
			}
		}
		else
		{
			message = "Invalid input.";
		}
		break;
	case 4:
		SplitInput(tokens[1], firstParameter, charVector);
		SplitInput(tokens[2], secondParameter, charVector);
		if (firstParameter.getSize() == 2 && secondParameter.getSize() == 2 && StringToInt(tokens[3], shapeIndex))
		{
			if (firstParameter[0] == "vertical" && secondParameter[0] == "horizontal" && StringToInt(firstParameter[1], vertical) && StringToInt(secondParameter[1], horizontal))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else if (firstParameter[0] == "horizontal" && secondParameter[0] == "vertical" && StringToInt(firstParameter[1], horizontal) && StringToInt(secondParameter[1], vertical))
			{
				message = Translate(vertical, horizontal, shapeIndex);
			}
			else
			{
				message = "Invalid input.";
			}
		}
		else
		{
			message = "Invalid input.";
		}
		break;
	default:
		message = "Invalid input.";
		break;
	}

	return message;
}

void Controller::SplitInput(String& input, Vector<String>& tokens, Vector<char> delimiters)
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

