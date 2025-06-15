#ifndef _QUIZSTATUSES_H
#define _QUIZSTATUSES_H

enum class QuizStatus {
	PENDING,  // Quiz has not started yet
	APPROVED,  // Quiz is currently in progress
	REJECTED,    // Quiz has been completed
};

#endif // !_QUIZSTATUSES_H