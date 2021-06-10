#pragma once
#include <iostream>
#include"Vector.h"

class String
{
private:
	char* str;
	int _len;
	int _capacity;

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
	void clear();
	const char* c_str() const;
	bool isEmpty() const;
	char* begin() const;

	
	String& operator=(const String& other);
	String& operator=(const char* other);
	String& operator=(char s);
	Vector<String> split(char toSplitBy);


	String operator+(char s);
	String operator+(const char* s);
	String operator+(const String& other);

	String operator+=(const String& rhs);

	char& operator[] (size_t i);
	bool operator ==(const char* c);

	bool operator ==(const String& other);
	bool operator !=(const String& other);
	bool operator<(const String& other);
	bool operator>(const String& other);
	bool operator<=(const String& other);
	bool operator>=(const String& other);

	friend std::istream& getline(std::istream& is, String& str);
	friend std::istream& getline(std::istream& is, String& str, char delim);


	friend std::ostream& operator<<(std::ostream& out, const String& s);
	friend std::istream& operator>>(std::istream& in, String& s);
};


String operator+ (char c, String s);

String toUpper(String s);
String toLower(String s);
String toString(size_t x);
