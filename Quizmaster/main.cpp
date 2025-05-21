#include <iostream>
#include "TrueOrFalseQuestion.h"

int main() {
    try {
        MyString questionText("C++ supports multiple inheritance.");
        size_t points = 5;
        bool correctAnswer = true;

        TrueOrFalseQuestion q1(questionText, points, correctAnswer);

        std::cout << q1.getQuestionText() << " (True/False): ";

        int score = q1.answerEvaluation();
        std::cout << "You earned " << score << " point(s)." << std::endl;

        q1.saveToFile("question_output.txt");
        std::cout << "Question saved to file." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
