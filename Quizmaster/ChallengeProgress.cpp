#include "ChallengeProgress.h"

ChallengeProgress::ChallengeProgress(const MyString& templateId, size_t progress, bool isCompleted, time_t timeCompleted) {
	setTemplateId(templateId);
	setProgress(progress);
	setIsCompleted(isCompleted);
	setTimeCompleted(timeCompleted);
}

ChallengeProgress::ChallengeProgress(const MyString& templateId) {
	setTemplateId(templateId);
	this->progress = 0;
	this->isCompleted = false;
	this->timeCompleted = 0;
}

ChallengeProgress::ChallengeProgress() {
	this->templateId = MyString();
	this->progress = 0;
	this->isCompleted = false;
	this->timeCompleted = 0;
}

void ChallengeProgress::setTemplateId(const MyString& templateId) {
	if (templateId.getLength() == 0) {
		throw std::invalid_argument("Template ID cannot be empty!");
	}

	this->templateId = templateId;
}

void ChallengeProgress::setProgress(size_t progress) {
	if (progress < 0) {
		throw std::invalid_argument("Progress cannot be negative!");
	}

	this->progress = progress;
}

void ChallengeProgress::setIsCompleted(bool isCompleted) {
	this->isCompleted = isCompleted;
}

void ChallengeProgress::setTimeCompleted(time_t timeCompleted) {
	this->timeCompleted = timeCompleted;
}

const MyString& ChallengeProgress::getTemplateId() const {
	return this->templateId;
}

size_t ChallengeProgress::getProgress() const {
	return this->progress;
}

bool ChallengeProgress::getIsCompleted() const {
	return this->isCompleted;
}

time_t ChallengeProgress::getTimeCompleted() const {
	return this->timeCompleted;
}

void ChallengeProgress::incrementProgress(size_t amount, size_t quizzesGoal) {
	if (this->isCompleted) {
		return;
	}

	if (progress + amount >= quizzesGoal) {
		progress = quizzesGoal;
		isCompleted = true;
		timeCompleted = std::time(nullptr);
	}
	else {
		progress += amount;
	}
}

bool ChallengeProgress::tryComplete(size_t goal) {
	if (this->isCompleted) {
		return false;
	}

	if (this->progress >= goal) {
		this->isCompleted = true;
		this->timeCompleted = std::time(nullptr);
		return true;
	}

	return false;
}

void ChallengeProgress::markCompleted() {
	if (!this->isCompleted) {
		this->isCompleted = true;
		this->timeCompleted = std::time(nullptr);
	}
}

void ChallengeProgress::print(std::ostream& os) const {
	os << "Challenge ID: " << this->templateId << std::endl;
	os << "Progress: " << this->progress << std::endl;
	os << "Is Completed: " << (this->isCompleted ? "Yes" : "No") << std::endl;
	if (this->isCompleted) {
		os << "Time Completed: " << std::ctime(&this->timeCompleted);
	}
	else {
		os << "Time Completed: Not completed yet" << std::endl;
	}
}

void ChallengeProgress::load(std::istream& in) {
	char buffer[MAX_BUFFER_SIZE_CHALLENGE_PROGRESS + 1];

	if (!in.getline(buffer, sizeof(buffer))) {
		return;
	}
	MyString line(buffer);
	this->templateId = line;

	if (!in.getline(buffer, sizeof(buffer))) {
		return;
	}
	line = MyString(buffer);
	this->progress = line.toInt();

	if (!in.getline(buffer, sizeof(buffer))) {
		return;
	}
	line = MyString(buffer);
	this->isCompleted = (line.toInt() != 0);

	if (!in.getline(buffer, sizeof(buffer))) {
		return;
	}
	line = MyString(buffer);
	this->timeCompleted = static_cast<time_t>(line.toInt());
}