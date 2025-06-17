#ifndef _MATCHINGPAIRSQUESTION_H
#define _MATCHINGPAIRSQUESTION_H

#include "Question.h"
#include "MyString.h"
#include "MyVector.hpp"
#include<iostream>
#include<fstream>
#include<stdexcept>

class MatchingPairsQuestion : public Question {
public:
	MatchingPairsQuestion(const MyString& questionText, size_t totalPoints, const MyVector<MyString>& rightColumn, const MyVector<MyString>& leftColumn, const MyString& correctAnswers);
	MatchingPairsQuestion();

	void setRightColumnValues(const MyVector<MyString>& rightColumn);
	void setLeftColumnValues(const MyVector<MyString>& leftColumn);
	void setCorrectAnswers(const MyString& correctAnswers);

	const MyVector<MyString>& getRightColumn() const;
	const MyVector<MyString>& getLeftColumn() const;
	const MyString& getCorrectAnswers() const;

	void printCorrectAnswer() const override;
	double answerEvaluation() override;
	Question* clone() const override;
	void saveToFile(std::ofstream& file) const override;
	void loadFromFile(std::ifstream& file) override;

private:
	MyVector<MyString> rightColumn;
	MyVector<MyString> leftColumn;
	MyString correctAnswers;

	static void readLineToMyStringMPQ(std::ifstream& file, MyString& str);
};

#endif // !_MATCHINGPAIRSQUESTION_H