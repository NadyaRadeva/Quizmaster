#ifndef _USERMANAGER_H
#define _USERMANAGER_H

#include "MyVector.hpp"
#include "User.h"
#include "Player.h"
#include "Administrator.h"

class UserManager {
public:
	UserManager(const MyVector<User*>& allUsers, User* currentUser);
	UserManager();
	UserManager(const UserManager& other);
	UserManager& operator=(const UserManager& other);
	UserManager(UserManager&& other) noexcept;
	UserManager& operator=(UserManager&& other) noexcept;
	~UserManager();

	void setAllUsers(const MyVector<User*>& allUsers);
	void setCurrentUser(User* currentUser);

	const MyVector<User*>& getAllUsers() const;
	const User* getCurrentUser() const;

	bool signupPlayer(const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password);
	User* login(const MyString& username, const MyString& password);
	void logout();

	void banUser(const MyString& username);

	void quit();

	const User* findPlayerByUserName(const MyString& userName) const;

private:
	MyVector<User*> allUsers;
	User* currentUser;

	void copyFrom(const UserManager& other);
	void moveFrom(UserManager&& other) noexcept;
	void freeUsers();
};

#endif // !_USERMANAGER_H