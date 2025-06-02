#include "Administrator.h"

Administrator::Administrator(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password): User(firstName, lastName, userName, password) {
}

Administrator::Administrator(): User() {
}

User* Administrator::clone() const {
	return new Administrator(*this);
}

void Administrator::approveQuiz(size_t quizId) {
	std::cout << "Quiz " << quizId << " approved!" << std::endl;
}

void Administrator::rejectQuiz(size_t quizId, const MyString& reason) {
	std::cout << "Quiz " << quizId << " has been rejected! Reason: " << reason << std::endl;
}

bool Administrator::isAdmin() const {
	return true;
}