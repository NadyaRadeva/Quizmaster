#include "UserManager.h"

UserManager::UserManager(const MyVector<User*>& allUsers, User* currentUser) {
	setAllUsers(allUsers);
	setCurrentUser(currentUser);
}

UserManager::UserManager() {
	this->allUsers = MyVector<User*>();
	this->currentUser = nullptr;
}

UserManager::UserManager(const UserManager& other) {
	this->copyFrom(other);
}

UserManager& UserManager::operator=(const UserManager& other) {
	if (this != &other) {
		this->freeUsers();
		this->copyFrom(other);
	}

	return *this;
}

UserManager::UserManager(UserManager&& other) noexcept {
	this->moveFrom(std::move(other));
}

UserManager& UserManager::operator=(UserManager&& other) noexcept {
	if (this != &other) {
		this->freeUsers();
		this->moveFrom(std::move(other));
	}

	return *this;
}

UserManager::~UserManager() {
	this->freeUsers();
	this->currentUser = nullptr;
}

void UserManager::setAllUsers(const MyVector<User*>& allUsers) {
	this->freeUsers();
	for (size_t i = 0; i < allUsers.getVectorSize(); ++i) {
		this->allUsers.pushBack(allUsers[i]->clone());
	}
}

void UserManager::setCurrentUser(User* currentUser) {
	this->currentUser = currentUser;
}


const MyVector<User*>& UserManager::getAllUsers() const {
	return this->allUsers;
}

const User* UserManager::getCurrentUser() const {
	return this->currentUser;
}

bool UserManager::signupPlayer(const MyString& firstName, const MyString& lastName, const MyString& username, const MyString& password) {
	for (size_t i = 0; i < allUsers.getVectorSize(); ++i) {
		if (allUsers[i]->getUserName() == username) {
			throw std::invalid_argument("Username already exists!");
		}
	}

	if (firstName.getLength() == 0 || lastName.getLength() == 0 || username.getLength() == 0 || password.getLength() == 0) {
		throw std::invalid_argument("All fields must be filled!");
	}

	allUsers.pushBack(new Player(firstName, lastName, username, password));

	return true;
}

User* UserManager::login(const MyString& username, const MyString& password) {
	for (size_t i = 0; i < this->allUsers.getVectorSize(); ++i) {
		if (this->allUsers[i]->getUserName() == username && this->allUsers[i]->getUserPassword() == password) {
			this->currentUser = this->allUsers[i];
			return this->currentUser;
		}
	}
	return nullptr;
}

void UserManager::logout() {
	if (this->currentUser) {
		std::cout << "User " << this->currentUser->getUserName() << " logged out." << std::endl;
		this->currentUser = nullptr;
	}
	else {
		std::cout << "No user is currently logged in!" << std::endl;
	}
}

void UserManager::banUser(const MyString& username) {
	for (size_t i = 0; i < this->allUsers.getVectorSize(); ++i) {
		if (this->allUsers[i]->getUserName() == username) {
			this->allUsers[i]->ban();
			std::cout << "User " << username << " has been banned." << std::endl;

			if (this->currentUser == this->allUsers[i]) {
				this->currentUser = nullptr;
				std::cout << "Current user has been logged out due to ban." << std::endl;
			}
			return;
		}
	}

	std::cout << "User " << username << " not found!" << std::endl;
}

void UserManager::quit() {
	std::cout << "Exiting the application. Goodbye!" << std::endl;
	this->freeUsers();
	this->currentUser = nullptr;
}

const User* UserManager::findPlayerByUserName(const MyString& userName) const {
	for (size_t i = 0; i < this->allUsers.getVectorSize(); ++i) {
		if (this->allUsers[i]->getUserName() == userName) {
			return this->allUsers[i];
		}
	}

	return nullptr;
}

void UserManager::copyFrom(const UserManager& other) {
	this->freeUsers();
	allUsers.clear();
	currentUser = nullptr;

	for (size_t i = 0; i < other.allUsers.getVectorSize(); ++i) {
		allUsers.pushBack(other.allUsers[i]->clone());
	}

	if (other.currentUser) {
		const MyString& username = other.currentUser->getUserName();

		for (size_t i = 0; i < allUsers.getVectorSize(); ++i) {
			if (allUsers[i]->getUserName() == username) {
				currentUser = allUsers[i];
				break;
			}
		}
	}
}

void UserManager::moveFrom(UserManager&& other) noexcept {
	this->allUsers = other.allUsers;
	this->currentUser = other.currentUser;

	other.allUsers = MyVector<User*>();
	other.currentUser = nullptr;
}

void UserManager::freeUsers() {
	for (size_t i = 0; i < allUsers.getVectorSize(); ++i) {
		delete allUsers[i];
	}

	allUsers.clear();
}