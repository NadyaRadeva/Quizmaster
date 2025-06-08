#ifndef _CHALLENGES_H
#define _CHALLENGES_H

#include "Quiz.h"
#include "MyString.h"
#include<stdexcept>
#include<ctime>

enum class ChallengeType {
	TestModeQuizzes,
	QuizModeQuizzes,
	CreatedQuizzes,
};

class Challenges {
public:
	Challenges(const MyString& challengeTitle, ChallengeType type, size_t quizzesGoal, size_t progress, bool isCompleted, time_t timeCompleted);
	Challenges();

	void setChallengeTitle(const MyString& challengeTitle);
	void setChallengeType(ChallengeType type);
	void setQuizzesGoal(size_t quizzesGoal);
	void setProgress(size_t progress);
	void setIsCompleted(bool isCompleted);
	void setTimeCompleted(time_t timeCompleted);

	const MyString& getChallengeTitle() const;
	ChallengeType getChallengeType() const;
	size_t getQuizzesGoal() const;
	size_t getProgress() const;
	bool getIsCompleted() const;
	time_t getTimeCompleted() const;

	size_t calculatePoints() const;

	bool tryComplete();
	void incrementProgress();
	void print(std::ostream& os) const;

private:
	MyString challengeTitle;
	ChallengeType type;
	size_t quizzesGoal;
	size_t progress;
	bool isCompleted;
	time_t timeCompleted;
};

#endif // !_CHALLENGES_H