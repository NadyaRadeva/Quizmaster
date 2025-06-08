#ifndef _PLAYER_H
#define _PLAYER_H

class Quiz;

#include "User.h"
#include "MyString.h"
#include "MyVector.hpp"
#include<iostream>

class Player : public User {
public:
	Player()

private:
	size_t points;
	size_t level;
	MyVector<Quiz*> quizzesCreated;
	MyVector<Quiz*> likedQuizzes;
	MyVector<Quiz*> favouriteQuizzes;

};

#endif // !_PLAYER_H