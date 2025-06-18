#ifndef _PLAYER_H
#define _PLAYER_H

#define _CRT_SECURE_NO_WARNINGS

#include "User.h"
#include "MyString.h"
#include "MyVector.hpp"
#include "Quiz.h"
#include "ChallengeTemplate.h"
#include "ChallengeProgress.h"
#include "ChallengeManager.h"
#include "QuizManager.h"
#include "Message.h"
#include "UserManager.h"
#include "QuizTypes.h"
#include "TrueOrFalseQuestion.h"
#include "ShortAnswerQuestion.h"
#include "SingleChoiceQuestion.h"
#include "MultipleChoiceQuestion.h"
#include "MatchingPairsQuestion.h"

class Quiz;
class QuizManager;
class ChallengeProgress;
class ChallengeTemplate;
class ChallengeManager;
class Message;
class UserManager;
class ReportManager;

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>


const size_t MAX_LEVEL = 100;
const size_t MILESTONE1 = 10;
const size_t MILESTONE2 = 20;
const size_t MILESTONE3 = 30;
const size_t MILESTONE4 = 40;
const size_t REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE1 = 1000;
const size_t REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE2 = 2000;
const size_t REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE3 = 3000;
const size_t REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE4 = 4000;
const size_t MAX_BUFFER_SIZE_PLAYER_CLASS = 10000;

class Player : public User {
public:
    //Constructors and big four
    Player(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password);
    Player(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password, size_t points, size_t level, const MyVector<Quiz*>& createdQuizzes, const MyVector<Quiz*>& likedQuizzes, const MyVector<Quiz*>& favouriteQuizzes, const MyVector<ChallengeProgress>& challenges, const MyVector<Message>& messages, const QuizManager* quizManager);
    Player();
    Player(const Player& other);
	Player& operator=(const Player& other);
	~Player();

    //Setters
	void setPoints(size_t points);
	void setLevel(size_t level);
	void setCreatedQuizzes(const MyVector<Quiz*>& createdQuizzes);
	void setLikedQuizzes(const MyVector<Quiz*>& likedQuizzes);
	void setFavouriteQuizzes(const MyVector<Quiz*>& favouriteQuizzes);
	void setChallenges(const MyVector<ChallengeProgress>& challenges);
	void setMessages(const MyVector<Message>& messages);
	void setQuizManager(const QuizManager* quizManager);

    // Getters
    size_t getPoints() const;
    size_t getLevel() const;
    const MyVector<Quiz*>& getCreatedQuizzes() const;
    const MyVector<Quiz*>& getLikedQuizzes() const;
    const MyVector<Quiz*>& getFavouriteQuizzes() const;
	const MyVector<ChallengeProgress>& getChallenges() const;
    const MyVector<Message>& getMessages() const;
	const QuizManager* getQuizManager() const;

    // Quiz Management
	//void createQuiz();
   // Quiz* addCreatedQuiz();
    Quiz* addCreatedQuiz(const MyString& title);
    void addLikedQuiz(size_t quizId);
    void removeLikedQuiz(size_t quizId);
    void addFavouriteQuiz(size_t quizId);
    void removeFavouriteQuiz(size_t quizId);
    
    void saveLikedQuizzesToFile(const char* filename) const;
    void loadLikedQuizzesFromFile(const char* filename, QuizManager* quizManager);
    void saveFavouriteQuizzesToFile(const char* filename) const;
    void loadFavouriteQuizzesFromFile(const char* filename, QuizManager* quizManager);
    void saveCreatedQuizzesToFile(const char* filename) const;
    void loadCreatedQuizzesFromFile(const char* filename, QuizManager* quizManager);
    void saveMessagesToFile(const char* filename) const;
    void loadMessagesFromFile(const char* filename);


    // Challenge Management
    void updateChallengeProgress(const ChallengeTemplate& templateData, size_t increment = 1);
    void viewChallenges(const ChallengeManager& templateManager) const;
    void viewUnfinishedChallenges(const ChallengeManager& templateManager) const;
    void viewFinishedChallenges(const ChallengeManager& templateManager) const;

	void viewUser(const MyString& userName, const UserManager& userManager) const;
    void reportQuiz(size_t quizId, const MyString& reason, ReportManager& reportManager);
    void startQuiz(size_t quizId, const MyString& mode, bool shuffle);
    void saveQuizToFile(size_t quizId, const MyString& filepath) const;

    // Points & Level
    void addPoints(size_t points);

    // Messages
	void receiveMessage(const Message& message);
    void viewAllMessages() const;

    //Other functions
    User* clone() const override;
    void print(std::ostream& os) const override;
    bool isAdmin() const override;
    bool isPlayer() const override;

    void save() const;
    void load(std::ifstream& in, QuizManager& quizManager);

private:
    size_t points;
    size_t level;
    MyVector<Quiz*> createdQuizzes;
    MyVector<Quiz*> likedQuizzes;
    MyVector<Quiz*> favouriteQuizzes;
    MyVector<ChallengeProgress> challenges;
    MyVector<Message> messages;
    QuizManager* quizManager;


    Question* createTFQuestion();
    Question* createSCQuestion();
    Question* createMCQuestion();
    Question* createShAQuestion();
    Question* createMPQuestion();

    size_t cumulativePointsForLevel(size_t level);
    void checkLevelUp();

    //Big four helper functions
	void copyFrom(const Player& other);
    void freeCreatedQuizzes();
    void freeLikedQuizzes();
    void freeFavouriteQuizzes();
    void freeAll();
};

#endif // !_PLAYER_H