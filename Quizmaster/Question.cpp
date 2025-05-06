#include "Question.h"

Question::Question(const char* questionText, size_t points) {
	if (questionText == nullptr) {
		throw std::invalid_argument("Question text cannot be null!");
	}

	this->freeQuestionText();

	this->questionText = new char[strlen(questionText) + 1];
	strcpy(this->questionText, questionText);


	if (points < 0) {
		throw std::invalid_argument("Points cannot be negative!");
	}

	this->points = points;
}
