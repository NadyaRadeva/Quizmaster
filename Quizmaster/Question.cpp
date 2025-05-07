#include "Question.h"
#pragma warning(disable : 4996)

Question::Question(const char* questionText, size_t points) {
	setQuestionText(questionText);
	setPoints(points);
}

Question::Question() {
	this->questionText = nullptr;
	this->points = 0;
}

Question::Question(const Question& other) {
	this->copyFrom(other);
}

Question& Question::operator=(const Question& other) {
	if (this != &other) {
		this->freeQuestion();
		this->copyFrom(other);
	}

	return *this;
}

Question::Question(Question&& other) noexcept {
	this->moveFrom(std::move(other));
}

Question& Question::operator=(Question&& other) noexcept {
	if (this != &other) {
		this->freeQuestion();
		this->moveFrom(std::move(other));
	}

	return *this;
}

Question::~Question() {
	this->freeQuestion();
}

void Question::setQuestionText(const char* questionText) {
	if (questionText == nullptr) {
		throw std::invalid_argument("Question text cannot be null!");
	}

	this->freeQuestionText();

	this->questionText = new char[strlen(questionText) + 1];
	strcpy(this->questionText, questionText);
}

void Question::setPoints(size_t points) {
	if (points < 0) {
		throw std::invalid_argument("Points cannot be negative!");
	}

	this->points = points;
}

const char* Question::getQuestionText() const {
	return this->questionText;
}

size_t Question::getPoints() const {
	return this->points;
}

void Question::copyFrom(const Question& other) {
	if (other.questionText == nullptr) {
		throw std::invalid_argument("Question text cannot be null!");
	}

	this->freeQuestionText();

	this->questionText = new char[strlen(other.questionText) + 1];
	strcpy(this->questionText, other.questionText);

	
	if (other.points < 0) {
		throw std::invalid_argument("Points cannot be negative!");
	}

	this->points = other.points;
}

void Question::moveFrom(Question&& other) noexcept {
	this->questionText = other.questionText;
	this->points = other.points;

	other.questionText = nullptr;
	other.points = 0;
}

void Question::freeQuestionText() {
	delete[] this->questionText;
	this->questionText = nullptr;
}

void Question::freeQuestion() {
	this->freeQuestionText();
	this->points = 0;
}
