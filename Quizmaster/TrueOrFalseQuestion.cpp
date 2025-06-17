#include "TrueOrFalseQuestion.h"
#include "QuestionTypes.h"

void TrueOrFalseQuestion::setCorrectAnswer(bool correctAnswer) {
	this->correctAnswer = correctAnswer;
}

bool TrueOrFalseQuestion::getCorrectAnswer() const {
	return this->correctAnswer;
}

void TrueOrFalseQuestion::printCorrectAnswer() const {
	std::cout << "Correct answer: " << (correctAnswer ? "True" : "False") << std::endl;
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

void TrueOrFalseQuestion::saveToFile(std::ofstream& fout) const {
	int questionType = static_cast<int>(QuestionTypes::TRUE_OR_FALSE);
	fout << questionType << "\n";
	fout << getQuestionText() << "\n";
	fout << getTotalPoints() << "\n";
	fout << (correctAnswer ? "true" : "false") << "\n";
}

void TrueOrFalseQuestion::loadFromFile(std::ifstream& file) {
	if (!file.is_open()) {
		throw std::invalid_argument("Error opening file for reading!");
	}

	MyString questionText = MyString().readLine(file);
	MyString totalPointsStr = MyString().readLine(file);
	MyString correctAnswerStr = MyString().readLine(file);

	this->setQuestionText(questionText);
	this->setTotalPoints(totalPointsStr.toInt());

	correctAnswerStr = correctAnswerStr.toLower();
	if (correctAnswerStr == "true") {
		this->correctAnswer = true;
	}
	else if (correctAnswerStr == "false") {
		this->correctAnswer = false;
	}
	else {
		throw std::invalid_argument("Invalid boolean value in file.");
	}
}

TrueOrFalseQuestion::TrueOrFalseQuestion(const MyString& questionText, size_t totalPoints, bool correctAnswer): Question(questionText, totalPoints) {
	this->correctAnswer = correctAnswer;
}

TrueOrFalseQuestion::TrueOrFalseQuestion(): Question() {
	this->correctAnswer = false;
}