#ifndef _REPORTMANAGER_H
#define _REPORTMANAGER_H

#include "MyVector.hpp"
#include "Quiz.h"
#include "QuizManager.h"
//#include "UserManager.h"
#include "Report.h"
#include<iostream>

class QuizManager;
class UserManager;

class ReportManager {
public:
    void addReport(const Report& report);

    const MyVector<Report>& getAllReports() const;

    void printAllReports(const QuizManager& quizManager, std::ostream& os) const;

    void removeReport(size_t index);

    void saveReports(const MyString& filepath) const;
    void loadReports(const MyString& filepath, const UserManager& userManager);

private:
	MyVector<Report> allReports;
};

#endif // !_REPORTMANAGER_H