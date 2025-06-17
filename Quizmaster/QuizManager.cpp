#include "QuizManager.h"

QuizManager::QuizManager(const MyVector<Quiz*>& allQuizzes) {
	setAllQuizzes(allQuizzes);
}

QuizManager::QuizManager() {
	this->allQuizzes = MyVector<Quiz*>();
}

QuizManager::QuizManager(const QuizManager& other) {
	this->copyFrom(other);
}

QuizManager& QuizManager::operator=(const QuizManager& other) {
	if (this != &other) {
		this->freeQuizzes();
		this->copyFrom(other);
	}

	return *this;
}

QuizManager::QuizManager(QuizManager&& other) noexcept {
	this->moveFrom(std::move(other));
}

QuizManager& QuizManager::operator=(QuizManager&& other) noexcept {
	if (this != &other) {
		this->freeQuizzes();
		this->moveFrom(std::move(other));
	}

	return *this;
}

QuizManager::~QuizManager() {
	this->freeQuizzes();
}

void QuizManager::setAllQuizzes(const MyVector<Quiz*>& allQuizzes) {
	this->freeQuizzes();
	this->allQuizzes.clear();
	for (size_t i = 0; i < allQuizzes.getVectorSize(); ++i) {
		this->allQuizzes.pushBack(new Quiz(*allQuizzes[i]));
	}
}

Quiz* QuizManager::getQuizById(size_t quizId) const {
	for (size_t i = 0; i < allQuizzes.getVectorSize(); ++i) {
		if (allQuizzes[i]->getQuizId() == quizId) {
			return allQuizzes[i];
		}
	}
	return nullptr;
}

const MyVector<Quiz*>& QuizManager::getAllQuizzes() const {
	return allQuizzes;
}

void QuizManager::addQuiz(Quiz* quiz) {
	if (!quiz) {
		throw std::invalid_argument("Quiz cannot be null!");
	}

	for (size_t i = 0; i < allQuizzes.getVectorSize(); ++i) {
		if (allQuizzes[i]->getQuizId() == quiz->getQuizId()) {
			throw std::runtime_error("Quiz with the same ID already exists!");
		}
	}

	allQuizzes.pushBack(quiz);
}

void QuizManager::removeQuizById(size_t quizId) {
	for (size_t i = 0; i < this->allQuizzes.getVectorSize(); ++i) {
		if (this->allQuizzes[i]->getQuizId() == quizId) {
			delete this->allQuizzes[i];
			this->allQuizzes.removeAt(i);
			return;
		}
	}

	throw std::invalid_argument("Quiz with the given ID not found!");
}

void QuizManager::clear() {
	this->freeQuizzes();
	this->allQuizzes = MyVector<Quiz*>();
}

void QuizManager::saveQuizById(int quizId) {
	MyString filename = Quiz::getQuizFilename(quizId);
	Quiz* quiz = getQuizById(quizId);
	if (quiz != nullptr) {
		quiz->saveToFile(filename);
	}
}

Quiz* QuizManager::loadQuizById(int quizId) {
	MyString filename = Quiz::getQuizFilename(quizId);
	Quiz* quiz = new Quiz();
	quiz->loadFromFile(filename);
	return quiz;
}

void QuizManager::copyFrom(const QuizManager& other) {
	this->allQuizzes = MyVector<Quiz*>();

	for (size_t i = 0; i < other.allQuizzes.getVectorSize(); ++i) {
		Quiz* copied = new Quiz(*other.allQuizzes[i]);
		this->allQuizzes.pushBack(copied);
	}
}

void QuizManager::moveFrom(QuizManager&& other) noexcept {
	this->allQuizzes = std::move(other.allQuizzes);

	other.allQuizzes = MyVector<Quiz*>();
}

void QuizManager::freeQuizzes() {
	for (size_t i = 0; i < this->allQuizzes.getVectorSize(); ++i) {
		delete this->allQuizzes[i];
	}

	this->allQuizzes.clear();
}