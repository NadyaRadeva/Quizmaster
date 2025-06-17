#ifndef _SHORTANSWERQUESTION_H
#define _SHORTANSWERQUESTION_H

#include "Question.h"
#include "MyString.h"
#include "MyVector.hpp"
#include<iostream>
#include<fstream>
#include<stdexcept>

const size_t MAX_LEN_SHORT_ANSWER_BUFFER = 3000;

class ShortAnswerQuestion : public Question {
public:
	ShortAnswerQuestion(const MyString& questionText, size_t totalPoints, const MyString& correctShortAnswer);
	ShortAnswerQuestion();

	void setCorrectShortAnswer(const MyString& correctShortAnswer);
	const MyString& getCorrectShortAnswer() const;

	void printCorrectAnswer() const override;
	double answerEvaluation() override;
	Question* clone() const override;
	void saveToFile(std::ofstream& file) const override;
	void loadFromFile(std::ifstream& file) override;

private:
	MyString correctShortAnswer;
};

#endif // !_SHORTANSWERQUESTION_H