#include "String.h"
void String::erase()
{
	delete[] this->str;
}

void String::copy(const String& other)
{
	this->str = new char[strlen(other.str) + 1];
	strcpy_s(this->str, strlen(other.str) + 1, other.str);
}

String::String()
{
	this->str = new char[1];
	str[0] = 0;
}

String::String(const char* s)
{
	this->str = new char[strlen(s) + 1];
	strcpy_s(this->str, strlen(s) + 1, s);
}

String::String(char s)
{
	this->str = new char[2];
	this->str[0] = s;
	this->str[1] = 0;
}

String::String(const String& other)
{
	copy(other);
}

String::~String()
{
	delete[] this->str;
}

void String::print() const
{
	std::cout << this->str;
}

int String::lenght() const
{
	return strlen(this->str);
}

void String::clear()
{
	delete[] str;
	copy("");
}

const char* String::c_str() const
{
	return str;
}

bool String::isEmpty() const
{
	return _len == 0;
}

char* String::begin() const
{
	return(str);
}





String& String::operator=(const String& other)
{
	if (this != &other)
	{
		this->erase();
		copy(other);
	}
	return *this;
}

String& String::operator=(const char* other)
{
	this->erase();
	this->str = new char[strlen(other) + 1];
	strcpy_s(this->str, strlen(other) + 1, other);
	return *this;
}

String& String::operator=(char s)
{
	erase();
	this->str = new char[2];
	this->str[0] = s;
	this->str[1] = 0;
	return *this;
}

Vector<String> String::split(char toSplitBy)
{
	Vector<String> result;
	char str[64];

	for (size_t i = 0, k = 0; i < lenght(); i++, k++) {
		if (str[i] == toSplitBy || str[i + 1] == '\0') {
			if (str[i + 1] == '\0') {
				str[k] = str[i];
				str[k + 1] = '\0';
			}
			else str[k] = '\0';
			k = -1;
			result.push_back(str);
		}
		else str[k] = str[i];
	}
	return result;
}

String String::operator+(char s)
{
	String result;
	result.str = new char[this->lenght() + 1 + 1];
	strcpy_s(result.str, this->lenght() + 1, this->str);
	result.str[this->lenght()] = s;
	result.str[this->lenght() + 1] = 0;
	return result;
}

String String::operator+(const char* s)
{
	String result;
	result.str = new char[this->lenght() + strlen(s) + 1];
	strcpy_s(result.str, this->lenght() + 1, this->str);
	strcat_s(result.str, this->lenght() + strlen(s) + 1, s);
	return result;
}

String String::operator+(const String& other)
{
	String result;
	result.str = new char[this->lenght() + other.lenght() + 1];
	strcpy_s(result.str, this->lenght() + 1, this->str);
	strcat_s(result.str, this->lenght() + other.lenght() + 1, other.str);

	return result;
}

String String::operator+=(const String& rhs)
{
	return *(this) + rhs;
}



char& String::operator[](size_t i)
{
	return this->str[i];
}

bool String::operator==(const char* c)
{
	return strcmp(this->c_str(), c) == 0;
}

bool String::operator==(const String& other)
{
	if (strcmp(this->str, other.str) == 0) return true;
	return false;
}

bool String::operator!=(const String& other)
{
	if (*this == other) return false;
	return true;
}

bool String::operator<(const String& other)
{
	if (strcmp(this->str, other.str) == -1)return true;
	return false;
}

bool String::operator>(const String& other)
{
	if (strcmp(this->str, other.str) == 1)return true;
	return false;
}

bool String::operator<=(const String& other)
{
	if (strcmp(this->str, other.str) == -1 || strcmp(this->str, other.str) == 0)return true;
	return false;
}

bool String::operator>=(const String& other)
{
	if (strcmp(this->str, other.str) == 1 || strcmp(this->str, other.str) == 0)return true;
	return false;
}



std::istream& getline(std::istream& is, String& str)
{
	char* c = new char[100];
	is.get(c, 100);
	int i = 0;
	while (c[i] != '\n' && i < strlen(c))
	{
		str += c[i];
		++i;
	}
	str.str[str._len] = NULL;
	delete[]c;
	return is;
}

std::istream& getline(std::istream& is, String& str, char delim)
{
	char* c = new char[100];
	is.get(c, 100, delim);
	int i = 0;
	while (c[i] != delim && i < strlen(c))
	{
		str += c[i];
		++i;
	}
	str.str[str._len] = NULL;
	delete[]c;
	return is;
}

std::ostream& operator<<(std::ostream& out, const String& s)
{
	out << s.str;
	return out;
}

std::istream& operator>>(std::istream& in, String& s)
{
	char c;
	do
	{
		c = in.get();
		if (c != '\n')
		{
			s = s + c;
		}
	} while (c != '\n');

	return in;
}

String operator+(char c, String s)
{
	String result;

	result = c;
	result = result + s;
	return result;

}

String toUpper(String s)
{
	for (int i = 0; i < s.lenght(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 32;
	}
	return s;
}

String toLower(String s)
{
	for (int i = 0; i < s.lenght(); i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] + 32;
	}
	return s;
}

String toString(size_t x)
{
	String result = "";
	while (x)
	{
		if (x < 10)
		{
			result = ('0' + x) + result;
			break;
		}
		result = ('0' + (x % 10)) + result;
		x = x / 10;

	}
	return result;
}
