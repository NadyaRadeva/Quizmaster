#include <iostream>
#include <stdexcept>

#include "MyString.h"
#include "MyVector.hpp"
#include "Question.h"
#include "TrueOrFalseQuestion.h"
#include "ShortAnswerQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "MatchingPairsQuestion.h"
#include "Quiz.h"
#include "Message.h"
#include "ChallengeProgress.h"
#include "ChallengeManager.h"
#include "ChallengeTemplate.h"
#include "User.h"
#include "Player.h"
#include "Administrator.h"
#include "QuizManager.h"
#include "UserManager.h"
#include "Report.h"
#include "QuizTypes.h"
#include "QuizStatuses.h"

void showMainMenu() {
    std::cout << "\n=== QUIZ PLATFORM MENU ===\n"
        << "1. Signup\n"
        << "2. Login\n"
        << "0. Exit\n"
        << "Choose option: ";
}

void showPlayerMenu() {
    std::cout << "\n=== PLAYER MENU ===\n"
        << "1. View Profile\n"
        << "2. Create Quiz\n"
        << "3. Start Quiz\n"
        << "4. Like Quiz\n"
        << "5. Report Quiz\n"
        << "6. View Messages\n"
        << "7. Logout\n"
        << "Choose option: ";
}

void showAdminMenu() {
    std::cout << "\n=== ADMIN MENU ===\n"
        << "1. Approve Quiz\n"
        << "2. View Reports\n"
        << "3. Block User\n"
        << "4. Send Message\n"
        << "5. Logout\n"
        << "Choose option: ";
}


int main() {
    //UserManager userManager;
    //QuizManager quizManager;
    //ReportManager reportManager;
    //ChallengeManager challengeManager;

    //// Предварително създаден админ
    //Admin* defaultAdmin = new Admin("admin", "admin", &userManager, &quizManager, &reportManager);
    //userManager.addUser(defaultAdmin);

    //bool running = true;
    //while (running) {
    //    showMainMenu();
    //    int choice;
    //    std::cin >> choice;
    //    std::cin.ignore();

    //    try {
    //        if (choice == 1) {
    //            std::string username, password, role;
    //            std::cout << "Enter username: ";
    //            std::getline(std::cin, username);
    //            std::cout << "Enter password: ";
    //            std::getline(std::cin, password);
    //            std::cout << "Role (player/admin): ";
    //            std::getline(std::cin, role);

    //            if (role == "player") {
    //                Player* p = new Player(username, password, &quizManager);
    //                userManager.addUser(p);
    //                std::cout << "Player registered!\n";
    //            }
    //            else if (role == "admin") {
    //                Admin* a = new Admin(username, password, &userManager, &quizManager, &reportManager);
    //                userManager.addUser(a);
    //                std::cout << "Admin registered!\n";
    //            }
    //            else {
    //                std::cout << "Invalid role!\n";
    //            }
    //        }
    //        else if (choice == 2) {
    //            std::string username, password;
    //            std::cout << "Username: ";
    //            std::getline(std::cin, username);
    //            std::cout << "Password: ";
    //            std::getline(std::cin, password);

    //            User* user = userManager.login(username, password);
    //            if (user == nullptr) {
    //                std::cout << "Login failed!\n";
    //                continue;
    //            }

    //            if (user->isBlocked()) {
    //                std::cout << "Your account is blocked!\n";
    //                continue;
    //            }

    //            if (Player* p = dynamic_cast<Player*>(user)) {
    //                bool loggedIn = true;
    //                while (loggedIn) {
    //                    showPlayerMenu();
    //                    int cmd;
    //                    std::cin >> cmd;
    //                    std::cin.ignore();

    //                    try {
    //                        switch (cmd) {
    //                        case 1:
    //                            p->viewProfile();
    //                            break;
    //                        case 2: {
    //                            std::string title;
    //                            std::cout << "Enter quiz title: ";
    //                            std::getline(std::cin, title);
    //                            p->createQuiz(title);
    //                            break;
    //                        }
    //                        case 3: {
    //                            std::string id;
    //                            std::cout << "Quiz ID: ";
    //                            std::getline(std::cin, id);
    //                            p->startQuiz(id, false, false);
    //                            break;
    //                        }
    //                        case 4: {
    //                            std::string id;
    //                            std::cout << "Quiz ID to like: ";
    //                            std::getline(std::cin, id);
    //                            p->likeQuiz(id);
    //                            break;
    //                        }
    //                        case 5: {
    //                            std::string id, reason;
    //                            std::cout << "Quiz ID: ";
    //                            std::getline(std::cin, id);
    //                            std::cout << "Reason: ";
    //                            std::getline(std::cin, reason);
    //                            p->reportQuiz(id, reason, reportManager);
    //                            break;
    //                        }
    //                        case 6:
    //                            p->viewMessages();
    //                            break;
    //                        case 7:
    //                            loggedIn = false;
    //                            break;
    //                        default:
    //                            std::cout << "Invalid option.\n";
    //                        }
    //                    }
    //                    catch (const std::exception& e) {
    //                        std::cerr << "Error: " << e.what() << "\n";
    //                    }
    //                }

    //            }
    //            else if (Administrator* a = dynamic_cast<Administrator*>(user)) {
    //                bool loggedIn = true;
    //                while (loggedIn) {
    //                    showAdminMenu();
    //                    int cmd;
    //                    std::cin >> cmd;
    //                    std::cin.ignore();

    //                    try {
    //                        switch (cmd) {
    //                        case 1: {
    //                            std::string id;
    //                            std::cout << "Quiz ID to approve: ";
    //                            std::getline(std::cin, id);
    //                            a->approveQuiz(id);
    //                            break;
    //                        }
    //                        case 2:
    //                            a->viewReports();
    //                            break;
    //                        case 3: {
    //                            std::string uname;
    //                            std::cout << "Username to block: ";
    //                            std::getline(std::cin, uname);
    //                            a->blockUser(uname);
    //                            break;
    //                        }
    //                        case 4: {
    //                            std::string to, msg;
    //                            std::cout << "Send to: ";
    //                            std::getline(std::cin, to);
    //                            std::cout << "Message: ";
    //                            std::getline(std::cin, msg);
    //                            a->sendMessage(to, msg);
    //                            break;
    //                        }
    //                        case 5:
    //                            loggedIn = false;
    //                            break;
    //                        default:
    //                            std::cout << "Invalid option.\n";
    //                        }
    //                    }
    //                    catch (const std::exception& e) {
    //                        std::cerr << "Error: " << e.what() << "\n";
    //                    }
    //                }
    //            }
    //        }
    //        else if (choice == 0) {
    //            running = false;
    //        }
    //        else {
    //            std::cout << "Invalid option.\n";
    //        }
    //    }
    //    catch (const std::exception& e) {
    //        std::cerr << "Exception caught: " << e.what() << "\n";
    //    }
    //}


    return 0;
}
