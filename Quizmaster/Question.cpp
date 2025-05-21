#include "Question.h"

Question::Question(const MyString& questionText, size_t points) {
	setQuestionText(questionText);
	setTotalPoints(points);
}

Question::Question() {
	this->questionText = MyString();
	this->totalPoints = 0;
}

void Question::setQuestionText(const MyString& questionText) {
	if (questionText.getLength() == 0) {
		throw std::invalid_argument("Question text cannot be empty!");
	}

	this->questionText = questionText;
}

void Question::setTotalPoints(size_t points) {
	this->totalPoints = points;
}

const MyString& Question::getQuestionText() const {
	return this->questionText;
}

size_t Question::getTotalPoints() const {
	return this->totalPoints;
}