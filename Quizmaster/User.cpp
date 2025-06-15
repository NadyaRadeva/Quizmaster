#include "User.h"

User::User(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password) {
	setUserFirstName(firstName);
	setUserLastName(lastName);
	setUserName(userName);
	setUserPassword(password);
}

User::User() {
	this->firstName = MyString();
	this->lastName = MyString();
	this->userName = MyString();
	this->password = MyString();
}

void User::setUserFirstName(const MyString& firstName) {
	if (firstName.getLength() == 0) {
		throw std::invalid_argument("First name of user cannot be empty!");
	}

	this->firstName = firstName;
}

void User::setUserLastName(const MyString& lastName) {
	if (lastName.getLength() == 0) {
		throw std::invalid_argument("Last name of user cannot be empty!");
	}

	this->lastName = lastName;
}

void User::setUserName(const MyString& userName) {
	if (userName.getLength() == 0) {
		throw std::invalid_argument("User name cannot be empty!");
	}

	this->userName = userName;
}

void User::setUserPassword(const MyString& password) {
	if (password.getLength() == 0) {
		throw std::invalid_argument("Password cannot be empty!");
	}

	this->password = password;
}

const MyString& User::getUserFirstName() const {
	return this->firstName;
}

const MyString& User::getUserLastName() const {
	return this->lastName;
}

const MyString& User::getUserName() const {
	return this->userName;
}

const MyString& User::getUserPassword() const {
	return this->password;
}

bool User::getIsBanned() const {
	return this->isBanned;
}

void User::ban() {
	this->isBanned = true;
}

void User::unban() {
	this->isBanned = false;
}

bool User::checkPassword(const MyString& pass) const {
	return this->password == pass;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
	user.print(os);
	return os;
}