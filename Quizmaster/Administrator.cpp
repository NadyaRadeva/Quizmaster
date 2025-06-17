#include "Administrator.h"

#include "QuizManager.h"
#include "ReportManager.h"
#include "UserManager.h"
#include "Player.h"
#include "Report.h"


Administrator::Administrator(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password, QuizManager* quizManager, ReportManager* reportManager) : User(firstName, lastName, userName, password) {
	setQuizManager(quizManager);
	setReportManager(reportManager);
}

Administrator::Administrator(): User() {
}

void Administrator::setQuizManager(QuizManager* manager) {
	this->quizManager = manager;
}

void Administrator::setReportManager(ReportManager* manager) {
	this->reportManager = manager;
}

User* Administrator::clone() const {
	return new Administrator(*this);
}

void Administrator::print(std::ostream& os) const {
	os << this->getUserFirstName() << " " << this->getUserLastName() << " " << "@" << this->getUserName() << std::endl;
	os << "Administrator privileges granted." << std::endl;
	os << "Quiz Manager: " << (quizManager ? "Set" : "Not Set") << std::endl;
	os << "Report Manager: " << (reportManager ? "Set" : "Not Set") << std::endl;
}

void Administrator::save(std::ostream& out) const {
	if (!out) {
		throw std::runtime_error("Failed to open output stream for saving administrator data.");
	}

    out << getUserName() << std::endl;
    out << getUserPassword() << std::endl;
    out << getUserFirstName() << std::endl;
    out << getUserLastName() << std::endl;
}

void Administrator::load(std::istream& in, ReportManager* reportManager) {
    MyString username; username.readLine(in);
    this->setUserName(username);

    MyString password; password.readLine(in);
    this->setUserPassword(password);

    MyString firstName; firstName.readLine(in);
    this->setUserFirstName(firstName);

    MyString lastName; lastName.readLine(in);
    this->setUserLastName(lastName);

    this->reportManager = reportManager;
}

void Administrator::approveQuiz(size_t quizId) {
    if (!quizManager) {
        std::cout << "Quiz manager is not set!" << std::endl;
        return;
    }

    Quiz* quiz = quizManager->getQuizById(quizId);
    if (!quiz) {
        std::cout << "Quiz with ID " << quizId << " not found!" << std::endl;
        return;
    }

    if (quiz->getQuizStatus() == QuizStatus::APPROVED) {
        std::cout << "Quiz is already approved!" << std::endl;
        return;
    }

    quiz->setQuizStatus(QuizStatus::APPROVED);
    std::cout << "Quiz with ID " << quizId << " has been approved!" << std::endl;
}

void Administrator::rejectQuiz(size_t quizId, const MyString& reason) {
    if (!quizManager) {
        std::cout << "Quiz manager is not set!" << std::endl;
        return;
    }

    Quiz* quiz = quizManager->getQuizById(quizId);
    if (!quiz) {
        std::cout << "Quiz with ID " << quizId << " not found!" << std::endl;
        return;
    }

    Player* author = quiz->getQuizAuthor();
    if (author) {
        MyString message = "Your quiz \"" + quiz->getQuizTitle() + "\" was rejected. Reason: " + reason;
        sendMessage(*author, message);
    }

    quizManager->removeQuizById(quizId);
    std::cout << "Quiz with ID " << quizId << " has been rejected and removed!" << std::endl;
}

void Administrator::removeQuiz(size_t quizId) {
    if (!quizManager) {
        return;
    }

    Quiz* quiz = quizManager->getQuizById(quizId);
    if (!quiz) {
        std::cout << "Quiz with ID " << quizId << " not found!" << std::endl;
        return;
    }

    quizManager->removeQuizById(quizId);
    std::cout << "Quiz with ID " << quizId << " removed successfully!" << std::endl;
}

void Administrator::reviewReport(const Report& report) {
    if (!reportManager) {
        std::cout << "Report manager not set!" << std::endl;
        return;
    }

    const MyVector<Report>& reports = reportManager->getAllReports();
    if (reports.isEmpty()) {
        std::cout << "No pending reports!" << std::endl;
        return;
    }

	for (size_t i = 0; i < reports.getVectorSize(); ++i) {
		reports[i].printReportDetails(std::cout, *quizManager);
	}
}

void Administrator::listPendingQuizzes() const {
    if (!this->quizManager) {
        std::cout << "Quiz manager not set!" << std::endl;
        return;
    }

    bool found = false;
    const MyVector<Quiz*>& quizzes = quizManager->getAllQuizzes();

    for (size_t i = 0; i < quizzes.getVectorSize(); ++i) {
        if (quizzes[i]->getQuizStatus() == QuizStatus::PENDING) {
            found = true;
            std::cout << quizzes[i]->getQuizId() << std::endl;
        }
    }

    if (!found) {
        std::cout << "No pending quizzes found!";
    }
}

void Administrator::viewAllReports() const {
    if (!reportManager || !quizManager) {
        std::cout << "ReportManager or QuizManager not set!" << std::endl;
        return;
    }

    std::cout << "=== All Reports ===" << std::endl;
    reportManager->printAllReports(*quizManager, std::cout);
}

void Administrator::banUser(const MyString& username, UserManager* userManager) {
    if (!userManager) {
        std::cout << "User manager not available!";
        return;
    }

    if (username.getLength() == 0) {
        throw std::invalid_argument("Username cannot be empty!");
    }

    userManager->banUser(username);
    std::cout << "User " << username << " has been banned!";
}

void Administrator::sendMessage(Player& player, const MyString& content) {
    Message message(content, this, &player);
    player.receiveMessage(message);
    std::cout << "Message sent to player " << player.getUserName() << std::endl;
}

bool Administrator::isAdmin() const {
	return true;
}

bool Administrator::isPlayer() const {
    return false;
}