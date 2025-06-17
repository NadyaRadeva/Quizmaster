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

void ReportManager::saveReports(const MyString& filepath) const {
	std::ofstream out(filepath.toChar());
	if (!out.is_open()) {
		throw std::runtime_error("Could not open report file for saving.");
	}

	out << this->allReports.getVectorSize() << std::endl;
	for (size_t i = 0; i < this->allReports.getVectorSize(); ++i) {
		this->allReports[i].save(out);
	}

	out.close();
}

void ReportManager::loadReports(const MyString& filepath, const UserManager& userManager) {
	std::ifstream in(filepath.toChar());
	if (!in.is_open()) {
		throw std::runtime_error("Could not open report file for loading.");
	}

	size_t count;
	in >> count;
	in.ignore();

	this->allReports.clear();

	for (size_t i = 0; i < count; ++i) {
		Report r;
		r.load(in, userManager);
		this->allReports.pushBack(r);
	}

	in.close();
}