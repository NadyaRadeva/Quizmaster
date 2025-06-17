#ifndef _TRUEORFALSEQUESTION_H
#define _TRUEORFALSEQUESTION_H

#include "Question.h"
#include "MyString.h"
#include <iostream>
#include<fstream>

class TrueOrFalseQuestion : public Question {
public:
	TrueOrFalseQuestion(const MyString& questionText, size_t totalPoints, bool correctAnswer);
	TrueOrFalseQuestion();

	void setCorrectAnswer(bool correctAnswer);
	bool getCorrectAnswer() const;

	void printCorrectAnswer() const override;
	double answerEvaluation() override;
	Question* clone() const override;
	void saveToFile(std::ofstream& file) const override;
	void loadFromFile(std::ifstream& file) override;

private:
	bool correctAnswer;
};

#endif // !_TRUEORFALSEQUESTION_H