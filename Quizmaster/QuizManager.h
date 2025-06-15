#ifndef _QUIZMANAGER_H
#define _QUIZMANAGER_H

#include "MyVector.hpp"
#include "Quiz.h"
#include<stdexcept>

class QuizManager {
public:
	QuizManager(const MyVector<Quiz*>& allQuizzes);
	QuizManager();
	QuizManager(const QuizManager& other);
	QuizManager& operator=(const QuizManager& other);
	QuizManager(QuizManager&& other) noexcept;
	QuizManager& operator=(QuizManager&& other) noexcept;
	~QuizManager();

	void setAllQuizzes(const MyVector<Quiz*>& allQuizzes);

	Quiz* getQuizById(size_t quizId) const;
	const MyVector<Quiz*>& getAllQuizzes() const;

	void addQuiz(Quiz* quiz);
	void removeQuizById(size_t quizId);

	void clear();

private:
	MyVector<Quiz*> allQuizzes;


	void copyFrom(const QuizManager& other);
	void moveFrom(QuizManager&& other) noexcept;
	void freeQuizzes();
};

#endif // !_QUIZMANAGER_H