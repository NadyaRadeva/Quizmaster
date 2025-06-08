#include "MatchingPairsQuestion.h"

double MatchingPairsQuestion::answerEvaluation() {
    std::cout << "Enter the answers in a format like 'Ab Cd Ef': ";

    char buffer[MAX_BUFFER_SIZE];
    std::cin.getline(buffer, MAX_BUFFER_SIZE);
    MyString userAnswer(buffer);

    MyString cleanCorrect = correctAnswers.removeSpaces();
    MyString cleanUser = userAnswer.removeSpaces();

    size_t correctLen = cleanCorrect.getLength();
    size_t userLen = cleanUser.getLength();

    if (correctLen % 2 != 0 || userLen % 2 != 0 || userLen != correctLen) {
        std::cout << "Invalid input format!" << std::endl;
        return 0.0;
    }

    size_t correctPairs = correctLen / 2;
    size_t matchCount = 0;

    for (size_t i = 0; i < correctLen; i += 2) {
        char correctLeft = cleanCorrect[i];
        char correctRight = cleanCorrect[i + 1];

        for (size_t j = 0; j < userLen; j += 2) {
            char userLeft = cleanUser[j];
            char userRight = cleanUser[j + 1];

            if (userLeft == correctLeft && userRight == correctRight) {
                ++matchCount;
                break;
            }
        }
    }

    std::cout << "Correct pairs: " << matchCount << " out of " << correctPairs << std::endl;

    return (double(matchCount) / correctPairs) * this->getTotalPoints();
}


Question* MatchingPairsQuestion::clone() const {
    return new MatchingPairsQuestion(*this);
}

void MatchingPairsQuestion::saveToFile(std::ofstream& file) const {
    if (!file.is_open()) {
        throw std::invalid_argument("Error opening file for writing!");
    }

    file << this->getQuestionText() << std::endl;

    size_t leftSize = this->leftColumn.getVectorSize();
    size_t rightSize = this->rightColumn.getVectorSize();
    size_t maxSize = (leftSize > rightSize) ? leftSize : rightSize;

    for (size_t i = 0; i < maxSize; ++i) {
        if (i < leftSize) {
            file << char('A' + i) << ") " << leftColumn[i];
        }
        else {
            file << "   ";
        }

        file << "          ";

        if (i < rightSize) {
            file << char('a' + i) << ") " << rightColumn[i];
        }

        file << std::endl;
    }
}

MatchingPairsQuestion::MatchingPairsQuestion(const MyString& questionText, size_t totalPoints, const MyVector<MyString>& rightColumn, const MyVector<MyString>& leftColumn, const MyString& correctAnswers): Question(questionText, totalPoints) {
    setRightColumnValues(rightColumn);
    setLeftColumnValues(leftColumn);
    setCorrectAnswers(correctAnswers);
}

MatchingPairsQuestion::MatchingPairsQuestion(): Question(), rightColumn(), leftColumn() {
    this->correctAnswers = MyString();

}

void MatchingPairsQuestion::setRightColumnValues(const MyVector<MyString>& rightColumn) {
    if (rightColumn.getVectorSize() < 1) {
        throw std::invalid_argument("There must be at least one input in the column!");
    }

    for (size_t i = 0; i < rightColumn.getVectorSize(); ++i) {
        if (rightColumn[i].getLength() == 0) {
            throw std::invalid_argument("Answer options cannot be empty!");
        }
    }

    for (size_t i = 0; i < rightColumn.getVectorSize(); ++i) {
        for (size_t j = i + 1; j < rightColumn.getVectorSize(); ++j) {
            if (rightColumn[i] == rightColumn[j]) {
                throw std::invalid_argument("Answer options must be unique!");
            }
        }
    }

    this->rightColumn = rightColumn;
}

void MatchingPairsQuestion::setLeftColumnValues(const MyVector<MyString>& leftColumn) {
    if (leftColumn.getVectorSize() < 1) {
        throw std::invalid_argument("There must be at least one input in the column!");
    }

    for (size_t i = 0; i < leftColumn.getVectorSize(); ++i) {
        if (leftColumn[i].getLength() == 0) {
            throw std::invalid_argument("Answer options cannot be empty!");
        }
    }

    for (size_t i = 0; i < leftColumn.getVectorSize(); ++i) {
        for (size_t j = i + 1; j < leftColumn.getVectorSize(); ++j) {
            if (leftColumn[i] == leftColumn[j]) {
                throw std::invalid_argument("Answer options must be unique!");
            }
        }
    }

    this->leftColumn = leftColumn;
}

void MatchingPairsQuestion::setCorrectAnswers(const MyString& correctAnswers) {
    if (correctAnswers.getLength() == 0) {
        throw std::invalid_argument("Invalid answers!");
    }

    this->correctAnswers = correctAnswers;
}

const MyVector<MyString>& MatchingPairsQuestion::getRightColumn() const {
    return this->rightColumn;
}

const MyVector<MyString>& MatchingPairsQuestion::getLeftColumn() const {
    return this->leftColumn;
}

const MyString& MatchingPairsQuestion::getCorrectAnswers() const {
    return this->correctAnswers;
}