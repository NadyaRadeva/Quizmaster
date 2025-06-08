#include "Quiz.h"

size_t Quiz::ID = 0;

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

const MyVector<const Player*> Quiz::getQuizLikedByList() const {
    return this->likedBy;
}

const MyVector<const Player*> Quiz::getQuizFavouriteByList() const {
	return this->favouriteBy;
}

size_t Quiz::getTimesAttempted() const {
	return this->timesAttempted;
}

void Quiz::saveToFile(const char* filename) const {
	std::ofstream file(filename);

	if (!file.is_open()) {
		throw std::invalid_argument("Failed to open file for writing!");
	}

	file << this->title << " - <" << this->questions.getVectorSize() << "> Questions" << std::endl;
	file << "By " << this->author->getUserFirstName() << " " << this->author->getUserLastName() << "  @" << this->author->getUserName() << std::endl;

	for (size_t i = 0; i < this->questions.getVectorSize(); ++i) {
		file << (i + 1) << ") ";
		questions[i]->saveToFile(file);
	}

	file.close();
}

void Quiz::addLike(const Player& player) {
	if (this->likedBy.contains(&player)) {
		throw std::invalid_argument("Player has already liked this quiz!");
	}

	this->likedBy.pushBack(&player);
}

void Quiz::addFavourite(const Player& player) {
	if (this->favouriteBy.contains(&player)) {
		throw std::invalid_argument("Player has already added this quiz to favourites!");
	}

	this->favouriteBy.pushBack(&player);
}

void Quiz::removeLike(const Player& player) {
	if (!this->likedBy.contains(&player)) {
		throw std::invalid_argument("Player has not liked this quiz!");
	}

	for (size_t i = 0; i < this->likedBy.getVectorSize(); ++i) {
		if (this->likedBy[i] == &player) {
			this->likedBy.remove(&player);
			return;
		}
	}
}

void Quiz::removeFavourite(const Player& player) {
	if (!this->favouriteBy.contains(&player)) {
		throw std::invalid_argument("Player has not added this quiz to favourites!");
	}

	for (size_t i = 0; i < this->favouriteBy.getVectorSize(); ++i) {
		if (this->favouriteBy[i] == &player) {
			this->favouriteBy.remove(&player);
			return;
		}
	}
}

Quiz::Quiz(const MyString& title, const Player* author, const MyVector<Question*> questions, bool isApproved, const MyVector<const Player*> likedBy, const MyVector<const Player*> favouriteBy, size_t timesAttempted) {
	++this->ID;
    setQuizTitle(title);
    setQuizAuthor(author);
    setQuestions(questions);
	setQuizApproved(isApproved);
	setQuizLikedByList(likedBy);
	setQuizFavouriteByList(favouriteBy);
	setTimesAttempted(timesAttempted);
}

Quiz::Quiz() {
	++this->ID;
	this->title = "Untitled Quiz";
	this->author = nullptr;
	this->isApproved = false;
	this->likedBy = MyVector<const Player*>();
	this->favouriteBy = MyVector<const Player*>();
}

void Quiz::setQuizTitle(const MyString& title) {
    if (title.getLength() == 0) {
        throw std::invalid_argument("Quiz title cannot be empty!");
    }

    this->title = title;
}

void Quiz::setQuizAuthor(const Player* author) {
	if (author == nullptr) {
		throw std::invalid_argument("Quiz author cannot be null!");
	}

	this->author = const_cast<Player*>(author);
}

void Quiz::setQuestions(const MyVector<Question*> questions) {
	if (questions.isEmpty()) {
		throw std::invalid_argument("Quiz must have at least one question!");
	}

	this->questions = questions;
}

void Quiz::setQuizApproved(bool isApproved) {
	this->isApproved = isApproved;
}

void Quiz::setQuizLikedByList(const MyVector<const Player*> likedBy) {
	this->likedBy = likedBy;
}

void Quiz::setQuizFavouriteByList(const MyVector<const Player*> favouriteBy) {
	this->favouriteBy = favouriteBy;
}

void Quiz::setTimesAttempted(size_t timesAttempted) {
	this->timesAttempted = timesAttempted;
}
