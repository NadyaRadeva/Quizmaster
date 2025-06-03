#ifndef _MULTIPLECHOICEQUESTION_H
#define _MULTIPLECHOICEQUESTION_H

#include "Question.h"
#include "MyString.h"
#include "MyVector.hpp"
#include<iostream>
#include<fstream>
#include<stdexcept>

class MultipleChoiceQuestion : public Question {
public:
	MultipleChoiceQuestion(const MyString& questionText, size_t totalPoints, const MyVector<MyString>& options, const MyVector<char>& correctAnswers);
	MultipleChoiceQuestion();

	void setOptions(const MyVector<MyString>& options);
	void setCorrectAnswers(const MyVector<char>& correctAnswers);

	const MyVector<MyString>& getOptions() const;
	const MyVector<char>& getCorrectAnswers() const;

	double answerEvaluation() override;
	Question* clone() const override;
	void saveToFile(std::ofstream& file) const override;

private:
	MyVector<MyString> options;
	MyVector<char> correctAnswers;
};

#endif // !_MULTIPLECHOICEQUESTION_H