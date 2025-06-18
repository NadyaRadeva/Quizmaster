#ifndef _USERMANAGER_H
#define _USERMANAGER_H

#include "MyString.h"
#include "MyVector.hpp"
#include "User.h"
//#include "QuizManager.h"
//#include "ReportManager.h"
#include "UserTypes.h"

class Administrator;
class Player;
class ReportManager;
class QuizManager;

const size_t MAX_BUFFER_SIZE_USER_MANAGER_CLASS = 10000;

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
	void addAdministrator(Administrator* admin);

	void quit();

	Player* findPlayerByUserName(const MyString& userName) const;

	void saveAllUsersToFile(const char* filename) const;
	void loadAllUsersFromFile(const char* filename, QuizManager* quizManager, ReportManager* reportManager);

private:
	MyVector<User*> allUsers;
	User* currentUser;

	void copyFrom(const UserManager& other);
	void moveFrom(UserManager&& other) noexcept;
	void freeUsers();
};

#endif // !_USERMANAGER_H