#include "ChallengeTemplate.h"

ChallengeTemplate::ChallengeTemplate(const MyString& id, const MyString& title, ChallengeType type, size_t quizzesGoal) {
    setId(id);
    setTitle(title);
	setType(type);
	setQuizzesGoal(quizzesGoal);
}

ChallengeTemplate::ChallengeTemplate() {
	this->id = MyString();
	this->title = MyString();
	this->type = ChallengeType::TestModeQuizzes;
	this->quizzesGoal = 0;
}

void ChallengeTemplate::setId(const MyString& id) {
	if (id.getLength() == 0) {
		throw std::invalid_argument("Challenge ID cannot be empty!");
	}
	this->id = id;
}

void ChallengeTemplate::setTitle(const MyString& title) {
	if (title.getLength() == 0) {
		throw std::invalid_argument("Challenge title cannot be empty!");
	}

	this->title = title;
}

void ChallengeTemplate::setType(ChallengeType type) {
	this->type = type;
}

void ChallengeTemplate::setQuizzesGoal(size_t quizzesGoal) {
	if (quizzesGoal == 0) {
		throw std::invalid_argument("Quizzes goal must be greater than zero!");
	}

	this->quizzesGoal = quizzesGoal;
}

const MyString& ChallengeTemplate::getId() const {
    return this->id;
}

const MyString& ChallengeTemplate::getTitle() const {
    return this->title;
}

ChallengeType ChallengeTemplate::getType() const {
    return this->type;
}

size_t ChallengeTemplate::getQuizzesGoal() const {
    return this->quizzesGoal;
}