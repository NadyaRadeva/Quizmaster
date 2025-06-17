#ifndef _ADMINISTRATOR_H
#define _ADMINISTRATOR_H

#include "User.h"
//#include "QuizManager.h"
#include "MyString.h"
#include "Report.h"
//#include "ReportManager.h"
//#include "UserManager.h"
#include<iostream>


class QuizManager;
class ReportManager;
class UserManager;
class Player;
class Report;

class Administrator : public User {
public:
	// Constructors
    Administrator(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password, QuizManager* quizManager, ReportManager* reportManager);
    Administrator();

    // Setters
    void setQuizManager(QuizManager* manager);
    void setReportManager(ReportManager* manager);

    // Core actions
    void approveQuiz(size_t quizId);
    void rejectQuiz(size_t quizId, const MyString& reason);
    void removeQuiz(size_t quizId);
    void reviewReport(const Report& report);
    void listPendingQuizzes() const;
    void viewAllReports() const;
    void banUser(const MyString& username, UserManager* userManager);
    void sendMessage(Player& player, const MyString& content);

    // Overrides
    bool isAdmin() const override;
    bool isPlayer() const override;
    User* clone() const override;
    void print(std::ostream& os) const override;

    void save(std::ostream& out) const;
    void load(std::istream& in, ReportManager* reportManager);

private:
    QuizManager* quizManager = nullptr;
    ReportManager* reportManager = nullptr;
};

#endif // !_ADMINISTRATOR_H