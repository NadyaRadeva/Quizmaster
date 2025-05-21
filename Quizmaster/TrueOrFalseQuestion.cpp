#include "TrueOrFalseQuestion.h"

void TrueOrFalseQuestion::setCorrectAnswer(bool correctAnswer) {
	this->correctAnswer = correctAnswer;
}

bool TrueOrFalseQuestion::getCorrectAnswer() const {
	return this->correctAnswer;
}

int TrueOrFalseQuestion::answerEvaluation() {
	MyString userInput;
	std::cin >> userInput;

	userInput = userInput.toLower();

	bool inputValue;

	if (userInput == "true" || userInput == "t") {
		inputValue = true;
	}
	else if (userInput == "false" || userInput == "f") {
		inputValue = false;
	}
	else {
		throw std::invalid_argument("Your input value is incorrect! Please, try again!");
	}

	return inputValue == correctAnswer ? this->getTotalPoints() : 0;
}

Question* TrueOrFalseQuestion::clone() const {
	return new TrueOrFalseQuestion(*this);
}

void TrueOrFalseQuestion::saveToFile(const char* filename) const {
	std::ofstream file(filename);

	if (!file.is_open()) {
		throw std::invalid_argument("Error opening file for writing!");
	}

	file << this->getQuestionText() << std::endl;
	file << this->correctAnswer << std::endl;

	file.close();
}

TrueOrFalseQuestion::TrueOrFalseQuestion(const MyString& questionText, size_t totalPoints, bool correctAnswer): Question(questionText, totalPoints) {
	this->correctAnswer = correctAnswer;
}

TrueOrFalseQuestion::TrueOrFalseQuestion(): Question() {
	this->correctAnswer = false;
}