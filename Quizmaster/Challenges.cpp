#include "Challenges.h"

Challenges::Challenges(const MyString& challengeTitle, ChallengeType type, size_t quizzesGoal, size_t progress, bool isCompleted, time_t timeCompleted) {
	setChallengeTitle(challengeTitle);
	setChallengeType(type);
	setQuizzesGoal(quizzesGoal);
	setProgress(progress);
	setIsCompleted(isCompleted);
	setTimeCompleted(timeCompleted);
}

Challenges::Challenges() {
	this->challengeTitle = MyString();
	this->type = ChallengeType::TestModeQuizzes;
	this->quizzesGoal = 0;
	this->progress = 0;
	this->isCompleted = false;
	this->timeCompleted = 0;
}

void Challenges::setChallengeTitle(const MyString& challengeTitle) {
	if (challengeTitle.getLength() == 0) {
		throw std::invalid_argument("Challenge title cannot be empty!");
	}

	this->challengeTitle = challengeTitle;
}

void Challenges::setChallengeType(ChallengeType type) {
    this->type = type;
}

void Challenges::setQuizzesGoal(size_t quizzesGoal) {
    this->quizzesGoal = quizzesGoal;
}

void Challenges::setProgress(size_t progress) {
	if (progress > this->quizzesGoal) {
		throw std::invalid_argument("Progress cannot exceed the quizzes goal!");
	}

	this->progress = progress;
}

void Challenges::setIsCompleted(bool isCompleted) {
	this->isCompleted = isCompleted;
}

void Challenges::setTimeCompleted(time_t timeCompleted) {
	this->timeCompleted = timeCompleted;
}

const MyString& Challenges::getChallengeTitle() const {
	return this->challengeTitle;
}

ChallengeType Challenges::getChallengeType() const {
    return this->type;
}

size_t Challenges::getQuizzesGoal() const {
    return this->quizzesGoal;
}

size_t Challenges::getProgress() const {
	return this->progress;
}

bool Challenges::getIsCompleted() const {
    return this->isCompleted;
}

time_t Challenges::getTimeCompleted() const {
    return this->timeCompleted;
}

size_t Challenges::calculatePoints() const {
	if (!this->isCompleted) {
		return 0;
	}

	switch (this->type) {
	case ChallengeType::TestModeQuizzes:
		return (this->quizzesGoal * 10) / 3;
	case ChallengeType::QuizModeQuizzes:
		return (2 * this->quizzesGoal * 10) / 3;
	case ChallengeType::CreatedQuizzes:
		return (this->quizzesGoal * 10) / 2;
	default:
		throw std::invalid_argument("Unknown challenge type!");
	}
}

bool Challenges::tryComplete() {
	if (!this->isCompleted && this->progress >= this->quizzesGoal) {
		this->isCompleted = true;
		this->timeCompleted = std::time(nullptr);
		return true;
	}

	if (this->isCompleted) {
		throw std::invalid_argument("Challenge has already been completed!");
	}
	return false;
}

void Challenges::incrementProgress() {
	if (this->isCompleted) {
		return;
	}

	this->progress++;
	tryComplete();
}

void Challenges::print(std::ostream& os) const {
	os << "Title: " << this->challengeTitle << std::endl;;
	os << "Type: ";
	switch (type) {
	case ChallengeType::TestModeQuizzes: os << "Test Mode Quizzes" << std::endl; break;
	case ChallengeType::QuizModeQuizzes: os << "Normal Mode Quizzes" << std::endl; break;
	case ChallengeType::CreatedQuizzes: os << "Created Quizzes" << std::endl; break;
	}
	os << "Progress: " << this->progress << "/" << this->quizzesGoal;
	if (this->isCompleted) {
		os << " (Completed at " << std::ctime(&this->timeCompleted) << ")" << std::endl;
	}
	os << "Points: " << calculatePoints() << std::endl;
}