#ifndef _SINGLECHOICEQUESTION_H
#define _SINGLECHOICEQUESTION_H

#include "Question.h"
#include "MyString.h"
#include <iostream>
#include<fstream>
#include <stdexcept>

const size_t NUMBER_OF_ANSWERS = 4;
const size_t ANSWER_A_INDEX = 0;
const size_t ANSWER_B_INDEX = 1;
const size_t ANSWER_C_INDEX = 2;
const size_t ANSWER_D_INDEX = 3;

class SingleChoiceQuestion : public Question {
public:
    SingleChoiceQuestion(const MyString& questionText, size_t totalPoints, const MyString& answerA, const MyString& answerB, const MyString& answerC, const MyString& answerD, char correctAnswerLetter);
    SingleChoiceQuestion();
    ~SingleChoiceQuestion() = default;

    void setOptionA(const MyString& answerA);
    void setOptionB(const MyString& answerB);
    void setOptionC(const MyString& answerC);
    void setOptionD(const MyString& answerD);
    void setCorrectAnswerLetter(char correctAnswerLetter);

    const MyString& getOptionA() const;
    const MyString& getOptionB() const;
    const MyString& getOptionC() const;
    const MyString& getOptionD() const;
    char getCorrectAnswerLetter() const;

    double answerEvaluation() override;
    Question* clone() const override;
    void saveToFile(const char* filename) const override;

private:
    MyString answers[NUMBER_OF_ANSWERS];
    char correctAnswerLetter;
};

#endif // !_SINGLECHOICEQUESTION_H