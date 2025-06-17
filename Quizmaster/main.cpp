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
#include "ReportManager.h"
#include "QuizTypes.h"
#include "QuizStatuses.h"

const size_t MAX_STR_BUFFER_SIZE = 3000;

void showMainMenu() {
    std::cout << std::endl;

    std::cout << "=== QUIZ PLATFORM MENU ===" << std::endl;
    std::cout << "1. Signup" << std::endl;
    std::cout << "2. Login" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Choose option: ";
}

void showPlayerMenu() {
    std::cout << std::endl;
    std::cout << "=== PLAYER MENU ===" << std::endl;
    std::cout << "1. View Profile" << std::endl;
    std::cout << "2. Create Quiz" << std::endl;
    std::cout << "3. Start Quiz" << std::endl;
    std::cout << "4. Like Quiz" << std::endl;
    std::cout << "5. Report Quiz" << std::endl;
    std::cout << "6. View Messages" << std::endl;
    std::cout << "7. Logout" << std::endl;
    std::cout << "Choose option: ";
}

void showAdminMenu() {
    std::cout << std::endl;
    std::cout << "=== ADMIN MENU ===" << std::endl;
    std::cout << "1. Approve Quiz" << std::endl;
    std::cout << "2. View Reports" << std::endl;
    std::cout << "3. Block User" << std::endl;
    std::cout << "4. Send Message" << std::endl;
    std::cout << "5. Logout" << std::endl;
    std::cout << "Choose option: ";
}


int main() {
	std::cout << "Welcome to \" Quizmaster \"!" << std::endl;

    UserManager userManager;
    QuizManager quizManager;
    ReportManager reportManager;
    ChallengeManager challengeManager;

    Administrator* defaultAdmin = new Administrator(MyString("admin"), MyString("admin"), MyString("admin"), MyString("admin"), &quizManager, &reportManager);
    userManager.addAdministrator(defaultAdmin);

    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        try {
            if (choice == 1) {
                std::cout << "Enter first name: ";
				char firstNameBuffer[MAX_STR_BUFFER_SIZE + 1];
				std::cin.getline(firstNameBuffer, MAX_BUFFER_SIZE);
				MyString firstName(firstNameBuffer);

				std::cout << "Enter last name: ";
				char lastNameBuffer[MAX_STR_BUFFER_SIZE + 1];
				std::cin.getline(lastNameBuffer, MAX_BUFFER_SIZE);
				MyString lastName(lastNameBuffer);

                std::cout << "Enter username: ";
                char userNameBuffer[MAX_STR_BUFFER_SIZE+1];
                std::cin.getline(userNameBuffer, MAX_BUFFER_SIZE);
                MyString userName(userNameBuffer);
                
                std::cout << "Enter password: ";
				char passwordBuffer[MAX_STR_BUFFER_SIZE + 1];
				std::cin.getline(passwordBuffer, MAX_BUFFER_SIZE);
				MyString password(passwordBuffer);
                

                userManager.signupPlayer(firstName, lastName, userName, password);
                std::cout << "Player registered!" << std::endl;
            }
            else if (choice == 2) {
                std::cout << "Enter username: ";
                char userNameBuffer[MAX_STR_BUFFER_SIZE + 1];
                std::cin.getline(userNameBuffer, MAX_BUFFER_SIZE);
                MyString userName(userNameBuffer);

                std::cout << "Enter password: ";
                char passwordBuffer[MAX_STR_BUFFER_SIZE + 1];
                std::cin.getline(passwordBuffer, MAX_BUFFER_SIZE);
                MyString password(passwordBuffer);

                User* user = userManager.login(userName, password);
                if (!user) {
                    std::cout << "Login failed!" << std::endl;
                    continue;
                }

                if (user->getIsBanned()) {
                    std::cout << "Your account is banned!" << std::endl;
                    continue;
                }

                if (Player* p = dynamic_cast<Player*>(user)) {
                    bool loggedIn = true;
                    while (loggedIn) {
                        showPlayerMenu();
                        int cmd;
                        std::cin >> cmd;
                        std::cin.ignore();

                        try {
                            switch (cmd) {
                            case 1:
                                p->viewUser(userName, userManager);
                                break;
                            case 2: {
                                std::cout << "Enter quiz title: ";
                                char quizTitleBuffer[MAX_STR_BUFFER_SIZE + 1];
                                std::cin.getline(quizTitleBuffer, MAX_BUFFER_SIZE);
                                MyString quizTitle(quizTitleBuffer);

                                Quiz* q = p->addCreatedQuiz(quizTitle);
                                break;
                            }
                            case 3: {
                                size_t id;
                                std::cout << "Quiz ID: ";
                                std::cin >> id;
                                if (id < 0 || !std::cin) {
                                    std::cout << "Invalid quiz ID! Try again!" << std::endl;
                                    continue;
                                }

                                MyString mode;
                                std::cout << "Choose mode (normal/test): ";
                                std::cin >> mode;

                                MyString lowerMode = mode.toLower();
                                while (lowerMode != "normal" && lowerMode != "test") {
                                    std::cout << "Invalid mode! Please choose 'normal' or 'test': ";
                                    std::cin >> mode;
                                    lowerMode = mode.toLower();
                                }

                                MyString shuffleInput;
                                std::cout << "Shuffle questions? (yes/no): ";
                                std::cin >> shuffleInput;

                                MyString lowerShuffle = shuffleInput.toLower();
                                while (lowerShuffle != "yes" && lowerShuffle != "no") {
                                    std::cout << "Invalid input! Please enter 'yes' or 'no': ";
                                    std::cin >> shuffleInput;
                                    lowerShuffle = shuffleInput.toLower();
                                }

                                bool shuffle = (lowerShuffle == "yes");

                                p->startQuiz(id, lowerMode, shuffle);
                                break;
                            }
                            case 4: {
                                size_t id;
                                std::cout << "Quiz ID to like: ";
                                std::cin >> id;
                                if (id < 0 || !std::cin) {
                                    std::cout << "Invalid quiz ID! Try again!" << std::endl;
                                    continue;
                                }
                                p->addLikedQuiz(id);
                                break;
                            }
                            case 5: {
                                size_t id;
								std::cout << "Quiz ID to report: ";
								std::cin >> id;
								if (id < 0 || !std::cin) {
									std::cout << "Invalid quiz ID! Try again!" << std::endl;
									continue;
								}
                                std::cin.ignore();
                                char reasonBuffer[MAX_STR_BUFFER_SIZE + 1];
								std::cout << "Reason for reporting: ";
								std::cin.getline(reasonBuffer, MAX_BUFFER_SIZE);
                                MyString reason(reasonBuffer);
                                p->reportQuiz(id, reason, reportManager);
                                break;
                            }
                            case 6:
                                p->viewAllMessages();
                                break;
                            case 7:
                                loggedIn = false;
                                break;
                            default:
                                std::cout << "Invalid option." << std::endl;
                            }
                        }
                        catch (const std::exception& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }
                    }

                }
                else if (Administrator* a = dynamic_cast<Administrator*>(user)) {
                    bool loggedIn = true;
                    while (loggedIn) {
                        showAdminMenu();
                        int cmd;
                        std::cin >> cmd;
                        std::cin.ignore();

                        try {
                            switch (cmd) {
                            case 1: {
                                size_t id;
                                std::cout << "Quiz ID to approve: ";
                                std::cin >> id;
                                if (id || !std::cin) {
									std::cout << "Invalid quiz ID! Try again!" << std::endl;
                                    continue;
                                }
                                a->approveQuiz(id);
                                std::cin.ignore();
                                break;
                            }
                            case 2:
                                a->viewAllReports();
                                break;
                            case 3: {
                                std::cout << "Enter username to ban: ";
                                char userNameToBanBuffer[MAX_STR_BUFFER_SIZE + 1];
                                std::cin.getline(userNameToBanBuffer, MAX_BUFFER_SIZE);
                                MyString userToBan(userNameToBanBuffer);
                                a->banUser(userToBan, &userManager);
                                break;
                            }
                            case 4: {
                                std::cout << "Enter username to send message to: ";
                                char userNameToSendMsgBuffer[MAX_STR_BUFFER_SIZE + 1];
                                std::cin.getline(userNameToSendMsgBuffer, MAX_BUFFER_SIZE);
                                MyString userToSendMsgTo(userNameToSendMsgBuffer);
                                Player* receiver = userManager.findPlayerByUserName(userToSendMsgTo);
                                if (!receiver) {
                                    std::cout << "User not found or not a player!" << std::endl;
                                    break;
                                }
                                std::cout << "Enter message to send: ";
                                char messageToSendBuffer[MAX_STR_BUFFER_SIZE + 1];
                                std::cin.getline(messageToSendBuffer, MAX_BUFFER_SIZE);
								MyString msg(messageToSendBuffer);
                                a->sendMessage(*receiver, msg);
                                break;
                            }
                            case 5:
                                loggedIn = false;
                                break;
                            default:
                                std::cout << "Invalid option." << std::endl;
                            }
                        }
                        catch (const std::exception& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }
                    }
                }

            }
            else if (choice == 0) {
                std::cout << "Exiting program. Goodbye!" << std::endl;
                running = false;
            }
            else {
                std::cout << "Invalid option." << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }

    }

    return 0;
}
