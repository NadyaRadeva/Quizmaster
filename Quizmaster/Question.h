#ifndef _QUESTION_H
#define _QUESTION_H

#include "MyString.h"

#include <iostream>
#include<stdexcept>

class Question {
public:
	Question(const MyString& questionText, size_t totalPoints);
	Question();
	virtual ~Question() = default;

	void setQuestionText(const MyString& questionText);
	void setTotalPoints(size_t totalPoints);

	const MyString& getQuestionText() const;
	size_t getTotalPoints() const;

	virtual int answerEvaluation() = 0;
	virtual Question* clone() const = 0;
	virtual void saveToFile(const char* filename) const = 0;

private:
	MyString questionText;
	size_t totalPoints;
};

#endif // !_QUESTION_H