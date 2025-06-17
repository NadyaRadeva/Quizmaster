#ifndef _CHALLENGETEMPLATE_H
#define _CHALLENGETEMPLATE_H

#include "MyString.h"

enum class ChallengeType {
	TestModeQuizzes,
	QuizModeQuizzes,
	CreatedQuizzes
};

class ChallengeTemplate {
public:
	ChallengeTemplate(const MyString& id, const MyString& title, ChallengeType type, size_t quizzesGoal);
	ChallengeTemplate();

	void setId(const MyString& id);
	void setTitle(const MyString& title);
	void setType(ChallengeType type);
	void setQuizzesGoal(size_t quizzesGoal);

	const MyString& getId() const;
	const MyString& getTitle() const;
	ChallengeType getType() const;
	size_t getQuizzesGoal() const;

private:
	MyString id;
	MyString title;
	ChallengeType type;
	size_t quizzesGoal;
};

#endif // !_CHALLENGETEMPLATE_H