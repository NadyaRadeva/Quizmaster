#include "ShortAnswerQuestion.h"

ShortAnswerQuestion::ShortAnswerQuestion(const MyString& questionText, size_t totalPoints, const MyString& correctShortAnswer): Question(questionText, totalPoints) {
    setCorrectShortAnswer(correctShortAnswer);
}

ShortAnswerQuestion::ShortAnswerQuestion(): Question() {
    this->correctShortAnswer = MyString();
}

void ShortAnswerQuestion::setCorrectShortAnswer(const MyString& correctShortAnswer) {
    if (correctShortAnswer.getLength() == 0) {
        throw std::invalid_argument("Invalid answer!");
    }

    this->correctShortAnswer = correctShortAnswer;
}
const MyString& ShortAnswerQuestion::getCorrectShortAnswer() const {
    return this->correctShortAnswer;
}

double ShortAnswerQuestion::answerEvaluation() {
    MyString userInput;
    char buffer[MAX_LEN_SHORT_ANSWER_BUFFER + 1];

    std::cout << "Enter your short answer: ";
    std::cin.getline(buffer, MAX_LEN_SHORT_ANSWER_BUFFER + 1);
    userInput = MyString(buffer);

    MyString lowerShortCorrectAnswer = correctShortAnswer.toLower();
    MyString lowerUserInput = userInput.toLower();

    if (lowerShortCorrectAnswer == lowerUserInput) {
        return this->getTotalPoints();
    }

    return 0;
}

Question* ShortAnswerQuestion::clone() const {
    return new ShortAnswerQuestion(*this);
}

void ShortAnswerQuestion::saveToFile(const char* filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::invalid_argument("Error opening file for writing!");
    }

    file << this->getQuestionText() << ":" << std::endl;

    file.close();
}