#include "TrueOrFalseQuestion.h"

void TrueOrFalseQuestion::setCorrectAnswer(bool correctAnswer) {
	this->correctAnswer = correctAnswer;
}

bool TrueOrFalseQuestion::getCorrectAnswer() const {
	return this->correctAnswer;
}

double TrueOrFalseQuestion::answerEvaluation() {
	std::cout << "Enter your answer (true/t and and false/f) :";
	MyString userInput;
	std::cout << "Enter your answer: ";
	std::cin >> userInput;
	if (!std::cin) {
		throw std::invalid_argument("Invalid input type!");
	}

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

void TrueOrFalseQuestion::saveToFile(std::ofstream& file) const {
	file << this->getQuestionText() << std::endl;
	file << "True/False" << std::endl;
}

TrueOrFalseQuestion::TrueOrFalseQuestion(const MyString& questionText, size_t totalPoints, bool correctAnswer): Question(questionText, totalPoints) {
	this->correctAnswer = correctAnswer;
}

TrueOrFalseQuestion::TrueOrFalseQuestion(): Question() {
	this->correctAnswer = false;
}