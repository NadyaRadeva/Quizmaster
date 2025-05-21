//#ifndef _SINGLECHOICEQUESTION_H
//#define _SINGLECHOICEQUESTION_H
//
//#include "Question.h"
//#include "MyString.h"
//#include <iostream>
//#include <stdexcept>
//
//const size_t NUMBER_OF_ANSWERS = 4;
//
//class SingleChoiceQuestion : public Question {
//public:
//    SingleChoiceQuestion(const MyString& questionText, size_t totalPoints, const MyString& answerA, const MyString& answerB, const MyString& answerC, const MyString& answerD, char correctAnswer); //
//    SingleChoiceQuestion();
//    ~SingleChoiceQuestion() = default;
//
//    void setAnswer(char letter, const MyString& answer);   // letter: 'A'-'D'
//    const MyString& getAnswer(char letter) const;
//
//    void setCorrectAnswer(char letter); // letter: 'A'-'D'
//    char getCorrectAnswerLetter() const;
//
//    const MyString& getCorrectAnswer() const;
//
//    Question* clone() const override;
//
//private:
//    MyString answers[NUMBER_OF_ANSWERS];
//    size_t correctAnswerIndex;
//};
//
//#endif // !_SINGLECHOICEQUESTION_H
