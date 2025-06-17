#ifndef _QUIZ_H
#define _QUIZ_H

#include "MyString.h"
#include "MyVector.hpp"
#include "User.h"
#include "Player.h"
#include "User.h"
#include "Question.h"
#include "QuizTypes.h"
#include "QuizStatuses.h"
#include<iostream>
#include<fstream>

class User;
class Player;

class Quiz {
public:
	friend class Player;

	//Constructors
	Quiz(const MyString& title, const Player* author, const MyVector<Question*> questions, QuizStatus status, const MyVector<const Player*> likedBy, const MyVector<const Player*> favouriteBy, size_t timesAttempted);
	Quiz();
	Quiz(const Quiz& other);
	Quiz& operator=(const Quiz& other);
	~Quiz();

	//Setters
	void setQuizTitle(const MyString& title);
	void setQuizAuthor(const Player* author);
	void setQuestions(const MyVector<Question*>& questions);
	void setQuizStatus(QuizStatus status);
	void setQuizLikedByList(const MyVector<const Player*> likedBy);
	void setQuizFavouriteByList(const MyVector<const Player*> favouriteBy);
	void setTimesAttempted(size_t timesAttempted);

	//Getters
	size_t getQuizId() const;
	const MyString& getQuizTitle() const;
	const Player* getQuizAuthor() const;
	Player* getQuizAuthor();
	const MyVector<Question*>& getQuestions() const;
	QuizStatus getQuizStatus() const;
	const MyVector<const Player*> getQuizLikedByList() const;
	const MyVector<const Player*> getQuizFavouriteByList() const;
	size_t getTimesAttempted() const;

	void addQuestion(Question* question);

	//Save entire quiz in text file
	void saveToFile(const MyString& filename) const;
	void loadFromFile(const MyString& filename);

	//Quiz modes
	void runNormalMode(Player& player, bool shuffle);
	void runTestMode(Player& player, bool shuffle);

	static MyString getQuizFilename(int quizId);

private:
	static size_t ID;
	size_t nextID;
	MyString title;
	Player* author;
	MyVector<Question*> questions;
	QuizStatus status;
	MyVector<const Player*> likedBy;
	MyVector<const Player*> favouriteBy;
	size_t timesAttempted;

	//Handles user interactions with the quiz
	void addLike(const Player& player);
	void addFavourite(const Player& player);
	void removeLike(const Player& player);
	void removeFavourite(const Player& player);

	void shuffleQuestionsUsingRand(MyVector<Question*>& quiz);

	void copyFrom(const Quiz& other);
	void freeQuestions();
	void freeLikedBy();
	void freeFavouriteBy();
	void freeQuiz();
};

#endif // !_QUIZ_H