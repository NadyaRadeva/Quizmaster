#include "MultipleChoiceQuestion.h"

MultipleChoiceQuestion::MultipleChoiceQuestion(const MyString& questionText, size_t totalPoints, const MyVector<MyString>& options, const MyVector<char>& correctAnswers): Question(questionText, totalPoints) {
    setOptions(options);
    setCorrectAnswers(correctAnswers);
}

MultipleChoiceQuestion::MultipleChoiceQuestion(): Question(), options(), correctAnswers() {
}

void MultipleChoiceQuestion::setOptions(const MyVector<MyString>& options) {
    if (options.getVectorSize() < 2) {
        throw std::invalid_argument("There must be at least two answer options!");
    }

    for (size_t i = 0; i < options.getVectorSize(); ++i) {
        if (options[i].getLength() == 0) {
            throw std::invalid_argument("Answer options cannot be empty!");
        }
    }

    for (size_t i = 0; i < options.getVectorSize(); ++i) {
        for (size_t j = i + 1; j < options.getVectorSize(); ++j) {
            if (options[i] == options[j]) {
                throw std::invalid_argument("Answer options must be unique!");
            }
        }
    }

    this->options = options;

}

void MultipleChoiceQuestion::setCorrectAnswers(const MyVector<char>& correctAnswers) {
    if (correctAnswers.getVectorSize() == 0) {
        throw std::invalid_argument("There must be at least one correct answer!");
    }

    for (size_t i = 0; i < correctAnswers.getVectorSize(); ++i) {
        char c = correctAnswers[i];
        if (c >= 'A' && c <= 'Z') {
            c += TO_LOWER_CASE_CHANGE;
        }

        if (c < 'a' || c >= 'a' + options.getVectorSize()) {
            throw std::invalid_argument("Correct answer letter out of range!");
        }

        for (size_t j = i + 1; j < correctAnswers.getVectorSize(); ++j) {
            char cj = correctAnswers[j];
            if (cj >= 'A' && cj <= 'Z') {
                cj += TO_LOWER_CASE_CHANGE;
            }
            if (cj == c) {
                throw std::invalid_argument("Duplicate correct answers are not allowed!");
            }
        }
    }

    this->correctAnswers = correctAnswers;
}

const MyVector<MyString>& MultipleChoiceQuestion::getOptions() const {
    return this->options;
}

const MyVector<char>& MultipleChoiceQuestion::getCorrectAnswers() const {
    return this->correctAnswers;
}

double MultipleChoiceQuestion::answerEvaluation() {
    std::cout << "Answer the following question (enter letters, comma-separated, e.g., A,C):" << std::endl;
    for (size_t i = 0; i < options.getVectorSize(); ++i) {
        std::cout << char('A' + i) << ") " << options[i] << std::endl;
    }

    std::cout << "Your answer: ";
    MyString answerInput;
    std::cin >> answerInput;
    for (size_t i = 0; i < answerInput.getLength(); ++i) {
        char c = answerInput[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ',')) {
            throw std::invalid_argument("Invalid character in input!");
        }
    }

    MyVector<char> selectedAnswers;

    for (size_t i = 0; i < answerInput.getLength(); ++i) {
        char c = answerInput[i];
        if (c >= 'a' && c <= 'z') {
            c += TO_UPPER_CASE_CHANGE;
        }

        if (c >= 'A' && c < 'A' + options.getVectorSize()) {
            bool alreadyAdded = false;
            for (size_t j = 0; j < selectedAnswers.getVectorSize(); ++j) {
                if (selectedAnswers[j] == c) {
                    alreadyAdded = true;
                    break;
                }
            }
            if (!alreadyAdded) {
                selectedAnswers.pushBack(c);
            }
        }
    }

    size_t correctSelected = 0;
    size_t totalCorrect = correctAnswers.getVectorSize();

    for (size_t i = 0; i < correctAnswers.getVectorSize(); ++i) {
        for (size_t j = 0; j < selectedAnswers.getVectorSize(); ++j) {
            if (correctAnswers[i] == selectedAnswers[j]) {
                ++correctSelected;
                break;
            }
        }
    }

    if (correctSelected == totalCorrect && selectedAnswers.getVectorSize() == totalCorrect) {
        return this->getTotalPoints();
    }

    if (correctSelected >= (totalCorrect + 1) / 2) {
        return this->getTotalPoints() / 2;
    }

    return 0.0;
}

Question* MultipleChoiceQuestion::clone() const {
    return new MultipleChoiceQuestion(*this);
}

void MultipleChoiceQuestion::saveToFile(const char* filename) const {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::invalid_argument("Error opening file for writing!");
    }

    file << this->getQuestionText() << "?" << std::endl;
    for (size_t i = 0; i < this->options.getVectorSize() - 1; ++i) {
        file << char((int)'A' + i) << ") " << this->options[i] << std::endl;
    }

    file.close();
}