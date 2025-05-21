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
    if (!dest || !src) throw std::invalid_argument("myStrCpy: null argument.");
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
