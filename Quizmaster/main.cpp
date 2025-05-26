#include <iostream>
#include "MatchingPairsQuestion.h"

int main() {
    try {
        MyString questionText("Match the capitals to their countries:");
        size_t totalPoints = 10;

        MyVector<MyString> leftColumn;
        leftColumn.pushBack("France");
        leftColumn.pushBack("Germany");
        leftColumn.pushBack("Italy");

        MyVector<MyString> rightColumn;
        rightColumn.pushBack("Rome");
        rightColumn.pushBack("Paris");
        rightColumn.pushBack("Berlin");

        MyString correctAnswers("Ab Bc Ca");

        MatchingPairsQuestion question(questionText, totalPoints, rightColumn, leftColumn, correctAnswers);

        std::cout << "Question: " << question.getQuestionText() << std::endl;

        const MyVector<MyString>& left = question.getLeftColumn();
        const MyVector<MyString>& right = question.getRightColumn();

        size_t maxSize = std::max(left.getVectorSize(), right.getVectorSize());

        for (size_t i = 0; i < maxSize; ++i) {
            if (i < left.getVectorSize()) {
                std::cout << char('A' + i) << ") " << left[i];
            }
            else {
                std::cout << "   ";
            }

            std::cout << "          ";

            if (i < right.getVectorSize()) {
                std::cout << char('a' + i) << ") " << right[i];
            }

            std::cout << std::endl;
        }

        double score = question.answerEvaluation();
        std::cout << "You scored: " << score << " out of " << totalPoints << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
