#ifndef _REPORT_H
#define _REPORT_H

#include "User.h"
#include "Player.h"
#include "Administrator.h"
#include "MyString.h"
#include "QuizManager.h"

#include<ctime>
#include<stdexcept>

class Player;
class QuizManager;

class Report {
public:
	// Constructors
	Report(time_t dateReported, const Player* reporter, size_t quizID, const MyString& reason);
	Report();

	// Setters
	void setDateReported(time_t dateReported);
	void setReporter(const Player* reporter);
	void setQuizID(size_t quizID);
	void setReason(const MyString& reason);

	// Getters
	time_t getDateReported() const;
	const Player* getReporter() const;
	size_t getQuizID() const;
	const MyString& getReason() const;

	// Print report details
	void printReportDetails(std::ostream& os, const QuizManager& quizManager) const;

	void save(std::ofstream& out) const;
	void load(std::ifstream& in, const UserManager& userManager);

private:
	time_t dateReported;
	const Player* reporter;
	size_t quizID;
	MyString reason;
};

#endif // !_REPORT_H