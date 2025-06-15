#ifndef _REPORTMANAGER_H
#define _REPORTMANAGER_H

#include "MyVector.hpp"
#include "Quiz.h"
#include "QuizManager.h"
#include "Report.h"

class ReportManager {
public:
    void addReport(const Report& report);

    const MyVector<Report>& getAllReports() const;

    void printAllReports(const QuizManager& quizManager, std::ostream& os) const;

    void removeReport(size_t index);

private:
	MyVector<Report> allReports;
};

#endif // !_REPORTMANAGER_H