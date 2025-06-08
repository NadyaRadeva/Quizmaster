#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "MyString.h"
#include <iostream>

class Message {
public:
	Message(const MyString& content);
	Message();

	void setContent(const MyString& content);
	const MyString& getContent() const;

private:
	MyString content;
};

#endif // !_MESSAGE_H