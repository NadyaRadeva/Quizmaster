#ifndef _USER_H
#define _USER_H

#include "MyString.h"
#include<iostream>
#include<stdexcept>
#include<fstream>

class User {
public:
	User(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password);
	User();
	virtual ~User() = default;

	virtual User* clone() const = 0;

	void setUserFirstName(const MyString& firstName);
	void setUserLastName(const MyString& lastName);
	void setUserName(const MyString& userName);
	void setUserPassword(const MyString& password);

	const MyString& getUserFirstName() const;
	const MyString& getUserLastName() const;
	const MyString& getUserName() const;
	const MyString& getUserPassword() const;

	friend std::ostream& operator<<(std::ostream& os, const User& user);
	virtual void print(std::ostream& os) const = 0;

	virtual bool isAdmin() const = 0;
	bool getIsBanned() const;
	void ban();
	void unban();

private:
	MyString firstName;
	MyString lastName;
	MyString userName;
	MyString password;
	bool isBanned = false;
};

#endif // !_USER_H