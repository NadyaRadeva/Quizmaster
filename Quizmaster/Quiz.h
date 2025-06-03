#ifndef _QUIZ_H
#define _QUIZ_H

#include "MyString.h"
#include "MyVector.hpp"
#include "User.h"
#include "Player.h"
#include "User.h"
#include "Question.h"
#include "QuizTypes.h"
#include<iostream>
#include<fstream>

class User;

class Quiz {
public:
	Quiz(const MyString& title, const Player* author, const MyVector<Question*> questions, bool isApproved, const MyVector<const Player*> likedBy, const MyVector<const Player*> favouriteBy);
	Quiz();

	void setQuizTitle(const MyString& title);
	void setQuizAuthor(const Player* author);
	void setQuestions(const MyVector<Question*> questions);
	void setQuizApproved(bool isApproved);
	void setQuizLikedByList(const MyVector<const Player*> likedBy);
	void setQuizFavouriteByList(const MyVector<const Player*> favouriteBy);

	size_t getQuizId() const;
	const MyString& getQuizTitle() const;
	const Player* getQuizAuthor() const;
	const MyVector<Question*> getQuestiions() const;
	bool isQuizApproved() const;
	const MyVector<const Player*> getQuizLikedByList() const;
	const MyVector<const Player*> getQuizFavouriteByList() const;

	void saveToFile(const char* filename) const;

private:
	static size_t ID;
	MyString title;
	Player* author;
	MyVector<Question*> questions;
	bool isApproved;
	MyVector<const Player*> likedBy;
	MyVector<const Player*> favouriteBy;

	void addLike(const Player& player);
	void addFavourite(const Player& player);
	void removeLike(const Player& player);
	void removeFavourite(const Player& player);
};

#endif // !_QUIZ_H