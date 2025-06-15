#ifndef _MYSTRING_H
#define _MYSTRING_H

#include<iostream>
#include<stdexcept>

const int TO_LOWER_CASE_CHANGE = 'a' - 'A';
const int TO_UPPER_CASE_CHANGE = 'A' - 'a';
const int TO_CHAR = '0';

const size_t MAX_BUFFER_SIZE = 10000;

class MyString {
public:
	MyString(const char* str, size_t len);
	MyString(const char* str);
	MyString();
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;
	~MyString();

	void setString(const char* str, size_t len);
	const char* getString() const;

	size_t getLength() const;
	size_t calcStrLen(const char* str) const;
	void myStrCpy(char* dest, const char* src);
	void myStrCat(char* first, const char* second);
	int myStrCmp(const char* str1, const char* str2) const;
	bool isNumber();
	static MyString intToString(int num);
	MyString removeSpaces() const;

	//Case insensitivity
	bool isLowerCase(char ch) const;
	bool isUpperCase(char ch) const;
	char toLowerCaseChar(char ch) const;
	char toUpperCaseChar(char ch) const;
	MyString toLower() const;
	MyString toUpper() const;
	
	//Operator overloading
	bool operator==(const MyString& str) const;
	bool operator!=(const MyString& str) const;
	MyString& operator+=(char c);
	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::istream& operator>>(std::istream& in, MyString& input);
	friend std::ostream& operator<<(std::ostream& out, const MyString& output);
	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	const char* toChar() const;

	//Number handling
	static int countDigits(int num);
	static int reverseNumber(int num);
	static MyString toStr(int num);

	void print() const;

private:
	char* str;
	size_t len;

	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other) noexcept;
	void free();

	bool isDigit(char ch);
};

#endif // !_MYSTRING_H