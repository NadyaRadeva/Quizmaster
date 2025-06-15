#ifndef _ADMINISTRATOR_H
#define _ADMINISTRATOR_H

#include "User.h"
#include "QuizManager.h"
#include "MyString.h"
#include "Report.h"
#include "ReportManager.h"
#include<iostream>

class ReportManager;

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

    // Overrides
    bool isAdmin() const override;
    bool isPlayer() const override;
    User* clone() const override;
    void print(std::ostream& os) const override;

private:
    QuizManager* quizManager = nullptr;
    ReportManager* reportManager = nullptr;

    void sendMessage(const Player& player, const MyString& content);
};

#endif // !_ADMINISTRATOR_H