#include "ShortAnswerQuestion.h"
#include "QuestionTypes.h"

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

void ShortAnswerQuestion::printCorrectAnswer() const {
	std::cout << "Correct answer: " << this->getCorrectShortAnswer() << '\n';
}

double ShortAnswerQuestion::answerEvaluation() {
    MyString userInput;
    char buffer[MAX_LEN_SHORT_ANSWER_BUFFER + 1];

    std::cout << "Enter your short answer: ";
    std::cin.getline(buffer, MAX_LEN_SHORT_ANSWER_BUFFER);
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

void ShortAnswerQuestion::saveToFile(std::ofstream& file) const {
    if (!file.is_open()) {
        throw std::invalid_argument("Error opening file for writing!");
    }

    file << static_cast<int>(QuestionTypes::SHORT_ANSWER) << '\n';
    file << this->getQuestionText() << '\n';
    file << this->getTotalPoints() << '\n';
    file << this->correctShortAnswer << '\n';
}

void ShortAnswerQuestion::loadFromFile(std::ifstream& file) {
    if (!file.is_open()) {
        throw std::invalid_argument("Error opening file for reading!");
    }

    char buffer[MAX_LEN_SHORT_ANSWER_BUFFER + 1];

    if (!file.getline(buffer, MAX_LEN_SHORT_ANSWER_BUFFER)) {
        throw std::runtime_error("Failed to read question text!");
    }
    MyString questionText(buffer);

    if (!file.getline(buffer, MAX_LEN_SHORT_ANSWER_BUFFER)) {
        throw std::runtime_error("Failed to read total points!");
    }
    MyString totalPointsStr(buffer);

    if (!file.getline(buffer, MAX_LEN_SHORT_ANSWER_BUFFER)) {
        throw std::runtime_error("Failed to read correct answer!");
    }
    MyString correctAnswer(buffer);

    this->setQuestionText(questionText);
    this->setTotalPoints(totalPointsStr.toInt());
    this->setCorrectShortAnswer(correctAnswer);
}