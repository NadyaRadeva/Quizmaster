#ifndef _ADMINISTRATOR_H
#define _ADMINISTRATOR_H

#include "User.h"
#include<iostream>

class Administrator : public User {
public:
	Administrator(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password);
	Administrator();

	User* clone() const override;

	void approveQuiz(size_t quizId);
	void rejectQuiz(size_t quizId, const MyString& reason);
	void removeQuiz(size_t quizId, const MyString& reason);
	void banUser(const MyString& username);
	void viewReports() const;

	void print(std::ostream& os) const override;

	bool isAdmin() const override;

private:
};
#endif // !_ADMINISTRATOR_H
