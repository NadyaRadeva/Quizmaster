#ifndef _MULTIPLECHOICEQUESTION_H
#define _MULTIPLECHOICEQUESTION_H

#include "Question.h"
#include "MyString.h"
#include "MyVector.hpp"
#include<iostream>
#include<fstream>
#include<stdexcept>

const size_t MAX_LEN_MULTIPLE_CHOICE_BUFFER = 10000;

class MultipleChoiceQuestion : public Question {
public:
	MultipleChoiceQuestion(const MyString& questionText, size_t totalPoints, const MyVector<MyString>& options, const MyVector<char>& correctAnswers);
	MultipleChoiceQuestion();

	void setOptions(const MyVector<MyString>& options);
	void setCorrectAnswers(const MyVector<char>& correctAnswers);

	const MyVector<MyString>& getOptions() const;
	const MyVector<char>& getCorrectAnswers() const;

	void printCorrectAnswer() const override;
	double answerEvaluation() override;
	Question* clone() const override;
	void saveToFile(std::ofstream& file) const override;
	void loadFromFile(std::ifstream& file) override;

private:
	MyVector<MyString> options;
	MyVector<char> correctAnswers;

	static void readLineFromFile(std::ifstream& file, MyString& line);
};

#endif // !_MULTIPLECHOICEQUESTION_H