#include "Quiz.h"

size_t Quiz::getQuizId() const {
    return this->ID;
}

const MyString& Quiz::getQuizTitle() const {
    return this->title;
}

const Player* Quiz::getQuizAuthor() const {
    return this->author;
}

const MyVector<Question*> Quiz::getQuestiions() const {
    return this->questions;
}

bool Quiz::isQuizApproved() const {
    return this->isApproved;
}
