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
	/*for (size_t i = 0; i < allUsers.getVectorSize(); ++i) {
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

	return true;*/

	for (size_t i = 0; i < allUsers.getVectorSize(); ++i) {
		if (allUsers[i]->getUserName() == username) {
			throw std::invalid_argument("Username already exists!");
		}
	}

	if (firstName.isEmpty() || lastName.isEmpty() || username.isEmpty() || password.isEmpty()) {
		throw std::invalid_argument("All fields must be filled!");
	}

	Player* newPlayer = new Player(firstName, lastName, username, password);
	allUsers.pushBack(newPlayer);

	saveAllUsersToFile("Users.txt");

	return true;
}

User* UserManager::login(const MyString& username, const MyString& password) {
	//std::ifstream in("Users.txt");
	//if (!in.is_open()) {
	//	std::cerr << "Could not open Users.txt for reading!";
	//	return nullptr;
	//}

	//char buffer[MAX_BUFFER_SIZE_USER_MANAGER_CLASS + 1];

	//while (in.getline(buffer, sizeof(buffer))) {
	//	MyString line(buffer);

	//	if (line.getLength() == 0)
	//		continue;

	//	MyVector<MyString> words;

	//	size_t start = 0;
	//	for (size_t i = 0; i <= line.getLength(); ++i) {
	//		if (i == line.getLength() || line[i] == ' ') {
	//			if (i > start) {
	//				MyString word = line.subStr(start, i - start);
	//				words.pushBack(word);
	//			}
	//			start = i + 1;
	//		}
	//	}

	//	if (words.getVectorSize() >= 5) {
	//		MyString fileUsername = words[3].trim();
	//		MyString filePassword = words[4].trim();

	//		if (fileUsername == username && filePassword == password) {
	//			for (size_t i = 0; i < this->allUsers.getVectorSize(); ++i) {
	//				if (this->allUsers[i]->getUserName() == username &&
	//					this->allUsers[i]->getUserPassword() == password) {
	//					this->currentUser = this->allUsers[i];
	//					return this->currentUser;
	//				}
	//			}
	//		}
	//	}
	//}

	//std::cout << "Login failed for username: " << username.toChar() << std::endl;
	//return nullptr;

	for (size_t i = 0; i < allUsers.getVectorSize(); ++i) {
		if (allUsers[i]->getUserName() == username &&
			allUsers[i]->getUserPassword() == password) {
			currentUser = allUsers[i];
			std::cout << "Successfully logged in as " << username << std::endl;
			return currentUser;
		}
	}
	std::cout << "Login failed for username: " << username << std::endl;
	return nullptr;
}


void UserManager::logout() {
	if (this->currentUser) {
		std::cout << "User " << this->currentUser->getUserName() << " logged out!" << std::endl;
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
	if (!out.is_open()) {
		return;
	}

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
	if (!in.is_open()) {
		std::cerr << "Failed to open " << filename << " for loading users!" << std::endl;
		return;
	}

	while (in) {
		MyString userTypeStr;
		if (!(in >> userTypeStr)) break;

		if (userTypeStr == "Player") {
			MyString firstName, lastName, username, password;
			int points = 0, level = 1;

			if (!(in >> firstName >> lastName >> username >> password >> points >> level)) {
				std::cerr << "Error reading Player data from file!" << std::endl;
				break;
			}
			in.ignore();

			MyVector<Quiz*> createdQuizzes;
			MyVector<Quiz*> likedQuizzes;
			MyVector<Quiz*> favouriteQuizzes;
			MyVector<ChallengeProgress> challenges;
			MyVector<Message> messages;

			Player* p = new Player(firstName, lastName, username, password,
				size_t(points), size_t(level),
				createdQuizzes, likedQuizzes, favouriteQuizzes,
				challenges, messages, quizManager);
			allUsers.pushBack(p);

			std::cout << "Loaded Player: " << username << std::endl;
		}
		else if (userTypeStr == "Administrator") {
			MyString firstName, lastName, username, password;

			if (!(in >> firstName >> lastName >> username >> password)) {
				std::cerr << "Error reading Administrator data from file!" << std::endl;
				break;
			}
			in.ignore();

			Administrator* a = new Administrator(firstName, lastName, username, password, quizManager, reportManager);
			allUsers.pushBack(a);

			std::cout << "Loaded Administrator: " << username << std::endl;
		}
		else {
			std::cerr << "Unknown user type: " << userTypeStr << std::endl;
			break;
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