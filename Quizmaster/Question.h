#ifndef _QUESTION_H
#define _QUESTION_H

#include <iostream>
#include<cstring>
#include<stdexcept>

class Question {
public:
	Question(const char* questionText, size_t points);
	Question();
	Question(const Question& other);
	Question& operator=(const Question& other);
	Question(Question&& other) noexcept;
	Question& operator=(Question&& other) noexcept;
	~Question();

private:
	char* questionText;
	size_t points;

	void copyFrom(const Question& other);
	void moveFrom(Question&& other) noexcept;
	void freeQuestionText();
	void free();
};

#endif // !_QUESTION_H
