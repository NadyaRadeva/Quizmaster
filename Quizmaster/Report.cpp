#include "Report.h"

Report::Report(time_t dateReported, const Player* reporter, size_t quizID, const MyString& reason) {
	setDateReported(dateReported);
	setReporter(reporter);
	setQuizID(quizID);
	setReason(reason);
}

Report::Report() {
	this->dateReported = 0;
	this->reporter = nullptr;
	this->quizID = 0;
	this->reason = MyString();
}

void Report::setDateReported(time_t dateReported) {
	if (dateReported < 0) {
		throw std::invalid_argument("Date reported cannot be negative!");
	}

	this->dateReported = dateReported;
}

void Report::setReporter(const Player* reporter) {
	if (reporter == nullptr) {
		throw std::invalid_argument("Reporter cannot be null!");
	}

	this->reporter = reporter;
}

void Report::setQuizID(size_t quizID) {
	if (quizID < 0) {
		throw std::invalid_argument("Quiz ID cannot be zero!");
	}

	this->quizID = quizID;
}

void Report::setReason(const MyString& reason) {
	if (reason.getLength() == 0) {
		throw std::invalid_argument("Reason for the report cannot be empty!");
	}

	this->reason = reason;
}

time_t Report::getDateReported() const {
	return this->dateReported;
}

const Player* Report::getReporter() const {
	return this->reporter;
}

size_t Report::getQuizID() const {
	return this->quizID;
}

const MyString& Report::getReason() const {
	return this->reason;
}

void Report::printReportDetails(std::ostream& os, const QuizManager& quizManager) const {
	const Quiz* quiz = quizManager.getQuizById(quizID);

	if (quiz == nullptr) {
		os << "Quiz with ID " << quizID << " not found." << std::endl;
		return;
	}

	os << this->dateReported << " | sent by " << (reporter ? reporter->getUserName() : "Unknown") << " | quiz id " << quiz->getQuizId() << " by " << quiz->getQuizAuthor()->getUserName() << " | reason: " << this->reason << std::endl;
}

void Report::save(std::ofstream& out) const {
	out << (int)dateReported << std::endl;
	if (reporter) {
		out << reporter->getUserName() << std::endl;
	}
	else {
		out << "NULL" << std::endl;
	}
	out << quizID << std::endl;
	out << reason << std::endl;
}

void Report::load(std::ifstream& in, const UserManager& userManager) {
	MyString reporterUsername;
	reporterUsername = reporterUsername.readLine(in);

	in >> quizID;
	in.ignore();

	reason = reason.readLine(in);

	int timestamp;
	in >> timestamp;
	in.ignore();
	dateReported = static_cast<time_t>(timestamp);

	const Player* playerPtr = userManager.findPlayerByUserName(reporterUsername);
	if (!playerPtr) {
		throw std::runtime_error("Reporter not found!");
	}
	reporter = playerPtr;
}