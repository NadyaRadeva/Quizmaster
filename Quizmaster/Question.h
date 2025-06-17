#ifndef _QUESTION_H
#define _QUESTION_H

#include "MyString.h"
#include "QuestionTypes.h"

#include <iostream>
#include<stdexcept>

const size_t MAX_LEN_QUESTION_BUFFER = 3000;

class Question {
public:
	Question(const MyString& questionText, size_t totalPoints);
	Question();
	virtual ~Question() = default;

	void setQuestionText(const MyString& questionText);
	void setTotalPoints(size_t totalPoints);

	const MyString& getQuestionText() const;
	size_t getTotalPoints() const;

	virtual void printCorrectAnswer() const = 0;
	virtual double answerEvaluation() = 0;
	virtual Question* clone() const = 0;
	virtual void saveToFile(std::ofstream& out) const = 0;
	virtual void loadFromFile(std::ifstream& in) = 0;

	static Question* createFromType(QuestionTypes type);

private:
	MyString questionText;
	size_t totalPoints;
};

#endif // !_QUESTION_H