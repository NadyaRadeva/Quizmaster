#include "Message.h"

Message::Message(const MyString& content) {
	setContent(content);
}

Message::Message() {
	this->content = MyString();
}

void Message::setContent(const MyString& content) {
	if (content.getLength() == 0) {
		throw std::invalid_argument("Message content cannot be empty!");
	}

	this->content = content;
}

const MyString& Message::getContent() const {
	return this->content;
}