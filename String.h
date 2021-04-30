#pragma once
#include <iostream>

class String
{
private:
	char* str;

	void erase();
	void copy(const String& other);
public:
	String();
	String(const char* s);
	String(char s);
	String(const String& other);
	~String();

	void print()const;
	int lenght()const;


	String& operator=(const String& other);
	String& operator=(const char* other);
	String& operator=(char s);


	String operator+(char s);
	String operator+(const char* s);
	String operator+(const String& other);

	char& operator[] (size_t i);

	bool operator ==(const String& other);
	bool operator !=(const String& other);
	bool operator<(const String& other);
	bool operator>(const String& other);
	bool operator<=(const String& other);
	bool operator>=(const String& other);




	friend std::ostream& operator<<(std::ostream& out, const String& s);
	friend std::istream& operator>>(std::istream& in, String& s);
};


String operator+ (char c, String s);

String toUpper(String s);
String toLower(String s);
String toString(size_t x);
