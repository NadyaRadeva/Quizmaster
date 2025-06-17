#ifndef _CHALLENGEPROGRESS_H
#define _CHALLENGEPROGRESS_H

#define _CRT_SECURE_NO_WARNINGS

#include "MyString.h"
#include<ctime>

class ChallengeProgress {
public:
	ChallengeProgress(const MyString& templateId, size_t progress, bool isCompleted, time_t timeCompleted);
	ChallengeProgress(const MyString& templateId);
	ChallengeProgress();

	void setTemplateId(const MyString& templateId);
	void setProgress(size_t progress);
	void setIsCompleted(bool isCompleted);
	void setTimeCompleted(time_t timeCompleted);

	const MyString& getTemplateId() const;
	size_t getProgress() const;
	bool getIsCompleted() const;
	time_t getTimeCompleted() const;

	void incrementProgress(size_t amount, size_t quizzesGoal);
	bool tryComplete(size_t goal);
	void markCompleted();

	void print(std::ostream& os) const;
	void load(std::istream& in);

private:
	MyString templateId;
	size_t progress;
	bool isCompleted;
	time_t timeCompleted;
};

#endif // !_CHALLENGEPROGRESS_H