#include "Question.h"

#include "TrueOrFalseQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "ShortAnswerQuestion.h"
#include "MatchingPairsQuestion.h"

Question::Question(const MyString& questionText, size_t points) {
	setQuestionText(questionText);
	setTotalPoints(points);
}

Question::Question() {
	this->questionText = MyString();
	this->totalPoints = 0;
}

void Question::setQuestionText(const MyString& questionText) {
	if (questionText.getLength() == 0) {
		throw std::invalid_argument("Question text cannot be empty!");
	}

	this->questionText = questionText;
}

void Question::setTotalPoints(size_t points) {
	this->totalPoints = points;
}

const MyString& Question::getQuestionText() const {
	return this->questionText;
}

size_t Question::getTotalPoints() const {
	return this->totalPoints;
}

Question* Question::createFromType(QuestionTypes type) {
	switch (type) {
	case QuestionTypes::TRUE_OR_FALSE: 
		return new TrueOrFalseQuestion();
	case QuestionTypes::SINGLE_CHOICE: 
		return new SingleChoiceQuestion();
	case QuestionTypes::MULTIPLE_CHOICE: 
		return new MultipleChoiceQuestion();
	case QuestionTypes::SHORT_ANSWER: 
		return new ShortAnswerQuestion();
	case QuestionTypes::MATCHING_PAIRS: 
		return new MatchingPairsQuestion();
	default: 
		return nullptr;
	}
}
