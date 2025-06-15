#include "ReportManager.h"

void ReportManager::addReport(const Report& report) {
	allReports.pushBack(report);
}

const MyVector<Report>& ReportManager::getAllReports() const {
	return this->allReports;
}

void ReportManager::printAllReports(const QuizManager& quizManager, std::ostream& os) const {
	for (size_t i = 0; i < allReports.getVectorSize(); ++i) {
		allReports[i].printReportDetails(os, quizManager);
		os << std::endl;
	}
}

void ReportManager::removeReport(size_t index) {
	if (index >= this->allReports.getVectorSize()) {
		throw std::invalid_argument("Index out of range!");
	}

	this->allReports.removeAt(index);
}
