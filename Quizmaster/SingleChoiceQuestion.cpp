//#include "SingleChoiceQuestion.h"
//#pragma warning(disable : 4996)
//
//void SingleChoiceQuestion::freeAnswerAt(size_t index) {
//    if (this->answers[index] != nullptr) {
//        delete[] this->answers[index];
//        this->answers[index] = nullptr;
//    }
//}
//
//void SingleChoiceQuestion::setAnswer(size_t index, const MyString& answer) {
//    if (answer == nullptr) {
//        throw std::invalid_argument("Answer cannot be null!");
//    }
//
//    this->answers[index]
//}
//
//void SingleChoiceQuestion::setAnswerA(const char* answerA) {
//    setAnswer(ANSWER_A_INDEX, answerA);
//}
//
//void SingleChoiceQuestion::setAnswerB(const char* answerB) {
//    setAnswer(ANSWER_B_INDEX, answerB);
//}
//
//void SingleChoiceQuestion::setAnswerC(const char* answerC) {
//    setAnswer(ANSWER_C_INDEX, answerC);
//}
//
//void SingleChoiceQuestion::setAnswerD(const char* answerD) {
//    setAnswer(ANSWER_D_INDEX, answerD);
//}
//
//const char* SingleChoiceQuestion::getAnswerA() const {
//    return this->answers[ANSWER_A_INDEX];
//}
//
//const char* SingleChoiceQuestion::getAnswerB() const {
//    return this->answers[ANSWER_B_INDEX];
//}
//
//const char* SingleChoiceQuestion::getAnswerC() const {
//    return this->answers[ANSWER_C_INDEX];
//}
//
//const char* SingleChoiceQuestion::getAnswerD() const {
//    return this->answers[ANSWER_D_INDEX];
//}
//
//void SingleChoiceQuestion::setCorrectAnswerPosition(size_t userInputPosition) {
//    if (userInputPosition < 1 || userInputPosition > MAX_CORRECT_ANSWER_POSITION) {
//        throw std::invalid_argument("Correct answer position must be between 1 and 4.");
//    }
//    this->correctAnswerPosition = userInputPosition - 1;
//}
//
//size_t SingleChoiceQuestion::getCorrectAnswerPosition() const {
//    return this->correctAnswerPosition + 1;
//}
//
//void SingleChoiceQuestion::setCorrectAnswer(size_t position, const MyString& correctAnswer) {
//    if (position < MIN_CORRECT_ANSWER_POSITION || position > MAX_CORRECT_ANSWER_POSITION) {
//        throw std::invalid_argument("Correct answer position must be between 1 and 4.");
//    }
//
//    if (correctAnswer.getLength() == 0) {
//        throw std::invalid_argument("Correct answer cannot be null!");
//    }
//
//    setAnswer(position - 1, correctAnswer);
//    this->correctAnswerPosition = position - 1;
//}
//
//Question* SingleChoiceQuestion::clone() const {
//    return new SingleChoiceQuestion(*this);
//}
//
//SingleChoiceQuestion::SingleChoiceQuestion(const MyString& questionText, size_t totalPoints, const char* answerA, const char* answerB, const char* answerC, const char* answerD, size_t correctAnswerPosition)
//    : Question(questionText, totalPoints)
//{
//    for (int i = 0; i < NUMBER_OF_ANSWERS; ++i) {
//        answers[i] = nullptr;
//    }
//
//    setAnswerA(answerA);
//    setAnswerB(answerB);
//    setAnswerC(answerC);
//    setAnswerD(answerD);
//    setCorrectAnswerPosition(correctAnswerPosition);
//}
