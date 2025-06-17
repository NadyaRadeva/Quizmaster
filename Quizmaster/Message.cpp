#include "Message.h"

Message::Message(const MyString& content, User* sender, User* receiver) {
	setContent(content);
	setSender(sender);
	setReceiver(receiver);
}

Message::Message() {
	this->content = MyString();
	this->sender = nullptr;
	this->receiver = nullptr;
}

void Message::setContent(const MyString& content) {
	if (content.getLength() == 0) {
		throw std::invalid_argument("Message content cannot be empty!");
	}

	this->content = content;
}

void Message::setSender(User* sender) {
	if (sender == nullptr) {
		throw std::invalid_argument("Sender cannot be null!");
	}

	this->sender = sender;
}

void Message::setReceiver(User* receiver) {
	if (receiver == nullptr) {
		throw std::invalid_argument("Receiver cannot be null!");
	}

	this->receiver = receiver;
}

const MyString& Message::getContent() const {
	return this->content;
}

User* Message::getSender() const {
	return this->sender;
}

User* Message::getReceiver() const {
	return this->receiver;
}

void Message::save(std::ofstream& out) const {
	out << content << std::endl;

	if (sender) {
		out << sender->getUserName() << std::endl;
	}
	else {
		out << "NULL" << std::endl;
	}

	if (receiver) {
		out << receiver->getUserName() << std::endl;
	}
	else {
		out << "NULL" << std::endl;
	}
}

void Message::load(std::ifstream& in) {
	MyString senderUsername, receiverUsername;
	content.readLine(in);
	senderUsername.readLine(in);
	receiverUsername.readLine(in);

	sender = nullptr;
	receiver = nullptr;
}