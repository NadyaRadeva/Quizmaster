#include "MyString.h"
#include <cstring>

void MyString::setString(const char* str, size_t len) {
    if (!str) {
        throw std::invalid_argument("setString: input string is null.");
    }

    this->free();

    this->len = len;
    this->str = new char[len + 1];
    myStrCpy(this->str, str);
}

const char* MyString::getString() const {
    return this->str;
}

size_t MyString::getLength() const {
    return this->len;
}

size_t MyString::calcStrLen(const char* str) const {
    return str ? std::strlen(str) : 0;
}

void MyString::myStrCpy(char* dest, const char* src) {
    if (!dest || !src) {
        throw std::invalid_argument("myStrCpy: null argument.");
    }

    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

void MyString::myStrCat(char* first, const char* second) {
    if (!first || !second) {
        throw std::invalid_argument("myStrCat: null input!");
    }

    while (*first) {
        ++first;
    }

    while (*second) {
        *first++ = *second++;
    }

    *first = '\0';
}

int MyString::myStrCmp(const char* str1, const char* str2) const {
    if (!str1 || !str2) {
        throw std::invalid_argument("myStrCmp: null argument");
    }

    while (*str1 && *str2 && *str1 == *str2) {
        ++str1;
        ++str2;
    }
    return *str1 - *str2;
}

bool MyString::isLowerCase(char ch) const {
    return ch >= 'a' && ch <= 'z'; 
}
bool MyString::isUpperCase(char ch) const {
    return ch >= 'A' && ch <= 'Z'; 
}

char MyString::toLowerCaseChar(char ch) const {
    return isUpperCase(ch) ? ch + TO_LOWER_CASE_CHANGE : ch;
}

char MyString::toUpperCaseChar(char ch) const {
    return isLowerCase(ch) ? ch - TO_LOWER_CASE_CHANGE : ch;
}

MyString MyString::toLower() const {
    MyString result;
    result.len = this->len;
    result.str = new char[len + 1];
    for (size_t i = 0; i < len; i++) {
        result.str[i] = toLowerCaseChar(this->str[i]);
    }
    result.str[len] = '\0';
    return result;
}

MyString MyString::toUpper() const {
    MyString result;
    result.len = this->len;
    result.str = new char[len + 1];
    for (size_t i = 0; i < len; i++) {
        result.str[i] = toUpperCaseChar(this->str[i]);
    }
    result.str[len] = '\0';
    return result;
}

bool MyString::operator==(const MyString& other) const {
    if (!str || !other.str) {
        return false;
    }
    return myStrCmp(str, other.str) == 0;
}

bool MyString::operator!=(const MyString& other) const {
    return !(*this == other);
}

MyString& MyString::operator+=(char c) {
    size_t len = this->getLength();

    char* newStr = new char[len + 2];

    for (size_t i = 0; i < len; ++i) {
        newStr[i] = this->str[i];
    }

    newStr[len] = c;
    newStr[len + 1] = '\0';

    delete[] this->str;

    this->str = newStr;
    this->len = len + 1;

    return *this;
}

char& MyString::operator[](size_t index) {
    if (index >= this->len) {
        throw std::out_of_range("Index out of bounds in MyString!");
    }
    return this->str[index];
}

const char& MyString::operator[](size_t index) const {
    if (index >= this->len) {
        throw std::out_of_range("Index out of bounds in MyString!");
    }
    return this->str[index];
}

const char* MyString::toChar() const {
    return this->str;
}

int MyString::countDigits(int num) {
    int count = 0;

    do {
        count++;
        num /= 10;
    } while (num != 0);

    return count;
}

int MyString::reverseNumber(int num) {
    int reversed = 0;

    while (num > 0) {
        reversed = reversed * 10 + (num % 10);
        num /= 10;
    }
    return reversed;
}

MyString MyString::toStr(int num) {
    if (num == 0) {
        return MyString("0");
    }

    int digits = countDigits(num);
    int reversedNum = reverseNumber(num);

    char* buffer = new char[digits + 1];
    for (int i = 0; i < digits; ++i) {
        buffer[i] = (reversedNum % 10) + TO_CHAR;
        reversedNum /= 10;
    }
    buffer[digits] = '\0';

    MyString result(buffer);
    delete[] buffer;
    return result;
}

void MyString::print() const {
    std::cout << (this->str ? this->str : "[null]") << std::endl;
}

MyString::MyString(const char* str, size_t len) {
    this->str = nullptr;
    setString(str, len);
}

MyString::MyString(const char* str) {
    this->str = nullptr;
    setString(str, calcStrLen(str));
}

MyString::MyString() : str(nullptr), len(0) {}

MyString::MyString(const MyString& other) {
    this->str = nullptr;
    copyFrom(other);
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        this->free();
        copyFrom(other);
    }
    return *this;
}

MyString::MyString(MyString&& other) noexcept {
    this->str = nullptr;
    moveFrom(std::move(other));
}

MyString& MyString::operator=(MyString&& other) noexcept {
    if (this != &other) {
        this->free();
        moveFrom(std::move(other));
    }
    return *this;
}

MyString::~MyString() {
    this->free();
}

void MyString::copyFrom(const MyString& other) {
    this->len = other.len;
    this->str = new char[other.len + 1];
    myStrCpy(this->str, other.str);
}

void MyString::moveFrom(MyString&& other) noexcept {
    this->str = other.str;
    this->len = other.len;

    other.str = nullptr;
    other.len = 0;
}

void MyString::free() {
    if (this->str != nullptr) {
        delete[] this->str;
        this->str = nullptr;
    }
    this->len = 0;
}

bool MyString::isDigit(char ch) {
    return ch >= '0' && ch < '9';
}

bool MyString::isNumber() {
    for (size_t i = 0; i < this->getLength(); ++i) {
        if (!isDigit(this->str[i])) {
            return false;
        }
    }

    return true;
}

MyString MyString::intToString(int num) {
    if (num == 0) {
        return MyString("0");
    }

    char buffer[MAX_BUFFER_SIZE];
    int i = 0;

    while (num > 0) {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    buffer[i] = '\0';

    return MyString(buffer);
}

MyString MyString::removeSpaces() const {
    MyString result;

    for (size_t i = 0; i < this->getLength(); ++i) {
        if ((*this)[i] != ' ') {
            result += (*this)[i];
        }
    }

    return result;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
	if (!lhs.str || !rhs.str) {
		throw std::invalid_argument("Cannot concatenate null MyString objects!");
	}

	size_t newLen = lhs.len + rhs.len;
	char* newStr = new char[newLen + 1];

	for (size_t i = 0; i < lhs.len; ++i) {
		newStr[i] = lhs.str[i];
	}

	for (size_t i = 0; i < rhs.len; ++i) {
		newStr[lhs.len + i] = rhs.str[i];
	}

	newStr[newLen] = '\0';

	MyString result(newStr, newLen);

	delete[] newStr;

	return result;
}

std::istream& operator>>(std::istream& in, MyString& input) {
    char buffer[MAX_BUFFER_SIZE + 1] = {};
    in.get(buffer, MAX_BUFFER_SIZE);

    size_t len = input.calcStrLen(buffer);
    input.setString(buffer, len);

    return in;
}

std::ostream& operator<<(std::ostream& out, const MyString& output) {
    return out << (output.str ? output.str : "");
}