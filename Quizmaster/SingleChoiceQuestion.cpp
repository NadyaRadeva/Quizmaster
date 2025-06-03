#include "SingleChoiceQuestion.h"

double SingleChoiceQuestion::answerEvaluation() {
	std::cout << "Enter your answer: ";
	char userAnswer;
	std::cin >> userAnswer;
	if (!std::cin || !(('A' <= userAnswer && userAnswer <= 'Z') || ('a' <= userAnswer && userAnswer <= 'z'))) {
		throw std::invalid_argument("Invalid user input!");
	}
	
	if (userAnswer >= 'A' && userAnswer <= 'Z') {
		userAnswer += TO_LOWER_CASE_CHANGE;
	}

	char correct = correctAnswerLetter;
	if (correct >= 'A' && correct <= 'Z') {
		correct += TO_LOWER_CASE_CHANGE;
	}

	return (userAnswer == correct) ? this->getTotalPoints() : 0;
}

Question* SingleChoiceQuestion::clone() const {
	return new SingleChoiceQuestion(*this);
}

void SingleChoiceQuestion::saveToFile(std::ofstream& file) const {
	file << this->getQuestionText() << "?" << std::endl;
	file << "A) " << this->getOptionA() << ";" << std::endl;
	file << "B) " << this->getOptionB() << ";" << std::endl;
	file << "C) " << this->getOptionC() << ";" << std::endl;
	file << "D) " << this->getOptionD() << std::endl;
}

SingleChoiceQuestion::SingleChoiceQuestion(const MyString& questionText, size_t totalPoints, const MyString& answerA, const MyString& answerB, const MyString& answerC, const MyString& answerD, char correctAnswerLetter): Question(questionText, totalPoints) {
	setOptionA(answerA);
	setOptionB(answerB);
	setOptionC(answerC);
	setOptionD(answerD);
	setCorrectAnswerLetter(correctAnswerLetter);
}

SingleChoiceQuestion::SingleChoiceQuestion(): Question() {
	this->answers[ANSWER_A_INDEX] = MyString();
	this->answers[ANSWER_B_INDEX] = MyString();
	this->answers[ANSWER_C_INDEX] = MyString();
	this->answers[ANSWER_D_INDEX] = MyString();
	this->correctAnswerLetter = '0';
}

void SingleChoiceQuestion::setOptionA(const MyString& answerA) {
	this->answers[ANSWER_A_INDEX] = answerA;
}

void SingleChoiceQuestion::setOptionB(const MyString& answerB) {
	this->answers[ANSWER_B_INDEX] = answerB;
}

void SingleChoiceQuestion::setOptionC(const MyString& answerC) {
	this->answers[ANSWER_C_INDEX] = answerC;
}

void SingleChoiceQuestion::setOptionD(const MyString& answerD) {
	this->answers[ANSWER_D_INDEX] = answerD;
}

void SingleChoiceQuestion::setCorrectAnswerLetter(char correctAnswerLetter) {
	if (!((correctAnswerLetter >= 'A' && correctAnswerLetter <= 'D') || (correctAnswerLetter >= 'a' && correctAnswerLetter <= 'd'))) {
		throw std::invalid_argument("Incorrect letter! Your answer should be A-D or a-d!");
	}

	this->correctAnswerLetter = correctAnswerLetter;
}

const MyString& SingleChoiceQuestion::getOptionA() const {
	return this->answers[ANSWER_A_INDEX];
}

const MyString& SingleChoiceQuestion::getOptionB() const {
	return this->answers[ANSWER_B_INDEX];
}

const MyString& SingleChoiceQuestion::getOptionC() const {
	return this->answers[ANSWER_C_INDEX];
}

const MyString& SingleChoiceQuestion::getOptionD() const {
	return this->answers[ANSWER_D_INDEX];
}

char SingleChoiceQuestion::getCorrectAnswerLetter() const {
	return this->correctAnswerLetter;
}