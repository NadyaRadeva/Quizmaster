#include "UserManager.h"

#include "Player.h"
#include "Administrator.h"

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

	Player* newPlayer = new Player(firstName, lastName, username, password);
	allUsers.pushBack(newPlayer);

	std::ofstream outFile("Users.txt", std::ios::app);
	if (outFile.is_open()) {
		outFile << "Player " << firstName << " " << lastName << " " << username << " " << password << " " << newPlayer->getPoints() << " " << newPlayer->getLevel() << std::endl;
		outFile.close();
	}

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

void UserManager::addAdministrator(Administrator* admin) {
	if (!admin) {
		return;
	}

	allUsers.pushBack(admin->clone());
}

void UserManager::quit() {
	std::cout << "Exiting the application. Goodbye!" << std::endl;
	this->freeUsers();
	this->currentUser = nullptr;
}

Player* UserManager::findPlayerByUserName(const MyString& userName) const {
	for (size_t i = 0; i < this->allUsers.getVectorSize(); ++i) {
		if (this->allUsers[i]->getUserName() == userName) {
			Player* p = dynamic_cast<Player*>(allUsers[i]);
			if (p) {
				return p;
			}
		}
	}
	return nullptr;
}

void UserManager::saveAllUsersToFile(const char* filename) const {
	std::ofstream out(filename);
	if (!out.is_open()) return;

	out << this->allUsers.getVectorSize() << std::endl;

	for (size_t i = 0; i < this->allUsers.getVectorSize(); i++) {
		User* user = this->allUsers[i];
		if (Player* p = dynamic_cast<Player*>(user)) {
			out << static_cast<int>(UsersTypes::PLAYER) << std::endl;
			p->save();
		}
		else if (Administrator* a = dynamic_cast<Administrator*>(user)) {
			out << static_cast<int>(UsersTypes::ADMINISTRATOR) << std::endl;
			a->save(out);
		}
	}
	out.close();
}

void UserManager::loadAllUsersFromFile(const char* filename, QuizManager* quizManager, ReportManager* reportManager) {
	std::ifstream in(filename);
	if (!in.is_open()) return;

	size_t userCount = 0;
	in >> userCount;
	in.ignore();

	for (size_t i = 0; i < userCount; i++) {
		int userTypeInt = 0;
		in >> userTypeInt;
		in.ignore();

		UsersTypes userType = static_cast<UsersTypes>(userTypeInt);

		if (userType == UsersTypes::PLAYER) {
			Player* p = new Player();
			p->load(in, *quizManager);
			this->allUsers.pushBack(p);
		}
		else if (userType == UsersTypes::ADMINISTRATOR) {
			Administrator* a = new Administrator();
			a->load(in, reportManager);
			this->allUsers.pushBack(a);
		}
	}
	in.close();
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