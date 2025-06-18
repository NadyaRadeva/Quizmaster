#include "Quiz.h"

size_t Quiz::ID = 0;

size_t Quiz::getQuizId() const {
    return this->nextID;
}

const MyString& Quiz::getQuizTitle() const {
    return this->title;
}

const Player* Quiz::getQuizAuthor() const {
    return this->author;
}

Player* Quiz::getQuizAuthor() {
	return this->author;
}

const MyVector<Question*>& Quiz::getQuestions() const {
	return this->questions;
}

QuizStatus Quiz::getQuizStatus() const {
	return this->status;
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

void Quiz::addQuestion(Question* question) {
	if (question) {
		questions.pushBack(question);
	}
}

void Quiz::saveToFile(const MyString& filename) const {
	std::ofstream file(filename.toChar());

	if (!file.is_open()) {
		throw std::invalid_argument("Failed to open file for writing!");
	}

	file << this->title << " - " << this->questions.getVectorSize() << " Questions\n";
	file << "By: " << this->author->getUserFirstName() << " " << this->author->getUserLastName() << " @" << this->author->getUserName() << "\n\n";

	for (size_t i = 0; i < this->questions.getVectorSize(); ++i) {
		file << (i + 1) << ") ";
		questions[i]->saveToFile(file);
		file << '\n';
	}

	file.close();
}

void Quiz::loadFromFile(const MyString& filename) {
	std::ifstream file(filename.toChar());
	if (!file.is_open()) {
		return;
	}

	freeQuestions();

	char buffer[MAX_BUFFER_QUIZ_CLASS + 1];

	// Quiz Name - <Number> Questions
	if (!file.getline(buffer, MAX_BUFFER_QUIZ_CLASS)) return;
	MyString line(buffer);
	if (line.isEmpty()) {
		return;
	}

	// Parsing of title and number of questions
	int dashPos = -1;
	for (size_t i = 0; i < line.getLength(); ++i) {
		if (line[i] == '-') {
			dashPos = (int)i;
			break;
		}
	}
	if (dashPos == -1) {
		return;
	}

	int titleLen = dashPos;
	if (titleLen > 0 && line[titleLen - 1] == ' ') {
		titleLen--;
	}

	MyString titleStr = line.subStr(0, titleLen);
	this->title = titleStr;

	int numQuestions = 0;
	size_t i = dashPos + 1;
	while (i < line.getLength() && line[i] == ' ') i++;

	while (i < line.getLength() && line[i] >= '0' && line[i] <= '9') {
		numQuestions = numQuestions * 10 + (line[i] - '0');
		i++;
	}
	if (numQuestions <= 0) {
		return;
	}

	// By: FirstName LastName @username
	if (!file.getline(buffer, MAX_BUFFER_QUIZ_CLASS)) {
		return;
	}

	line = MyString(buffer);
	if (line.isEmpty()) return;

	int atPos = -1;
	for (size_t j = 0; j < line.getLength(); ++j) {
		if (line[j] == '@') {
			atPos = (int)j;
			break;
		}
	}
	if (atPos == -1) {
		return;
	}

	MyString username;
	size_t pos = atPos + 1;
	while (pos < line.getLength() && line[pos] != ' ') {
		username += line[pos];
		pos++;
	}

	// Skipping the empty line between author and first question
	if (!file.getline(buffer, MAX_BUFFER_QUIZ_CLASS)) {
		return;
	}

	// Reading each question
	for (int q = 0; q < numQuestions; ++q) {
		// Reading type line
		if (!file.getline(buffer, MAX_BUFFER_QUIZ_CLASS)) {
			return;
		}
		line = MyString(buffer);
		if (line.isEmpty()) {
			return;
		}

		int qType;
		file >> qType;
		file.ignore(MAX_BUFFER_QUIZ_CLASS, '\n');

		Question* question = Question::createFromType((QuestionTypes)qType);
		if (!question) {
			return;
		}

		question->loadFromFile(file);
		questions.pushBack(question);
	}

	file.close();
}

void Quiz::runNormalMode(Player& player, bool shuffle) {
	MyVector<Question*> questionsToAsk = questions;

	if (shuffle) {
		shuffleQuestionsUsingRand(questionsToAsk);
	}

	double totalScore = 0;

	for (size_t i = 0; i < questionsToAsk.getVectorSize(); ++i) {
		std::cout << "Question: " << questionsToAsk[i]->getQuestionText() << std::endl;
		double score = questionsToAsk[i]->answerEvaluation();
		std::cout << "You scored " << score << " points." << std::endl;
		totalScore += score;
	}

	player.addPoints(totalScore);
	timesAttempted++;

	std::cout << "Quiz finished! Your total score: " << totalScore << std::endl;
}

void Quiz::runTestMode(Player& player, bool shuffle) {
	MyVector<Question*> questionsToAsk = questions;

	if (shuffle) {
		shuffleQuestionsUsingRand(questionsToAsk);
	}

	std::cout << "Running quiz in TEST MODE." << std::endl;

	for (size_t i = 0; i < questionsToAsk.getVectorSize(); ++i) {
		std::cout << "Question " << (i + 1) << ": " << questionsToAsk[i]->getQuestionText() << std::endl;

		double score = questionsToAsk[i]->answerEvaluation();

		std::cout << "Correct answer: ";
		questionsToAsk[i]->printCorrectAnswer();
		std::cout << std::endl;
	}

	std::cout << "Test mode complete. No points were added."<<std::endl;
}

MyString Quiz::getQuizFilename(int quizId) {
	return "quiz_" + MyString::intToString(quizId) + ".txt";
}

void Quiz::addLike(const Player& player) {
	for (size_t i = 0; i < likedBy.getVectorSize(); ++i) {
		if (likedBy[i] == &player) {
			return;
		}
	}
	likedBy.pushBack(&player);
}

void Quiz::addFavourite(const Player& player) {
	for (size_t i = 0; i < favouriteBy.getVectorSize(); ++i) {
		if (favouriteBy[i] == &player) {
			return;
		}
	}
	favouriteBy.pushBack(&player);
}

void Quiz::removeLike(const Player& player) {
	for (size_t i = 0; i < likedBy.getVectorSize(); ++i) {
		if (likedBy[i] == &player) {
			likedBy.removeAt(i);
			break;
		}
	}
}

void Quiz::removeFavourite(const Player& player) {
	for (size_t i = 0; i < favouriteBy.getVectorSize(); ++i) {
		if (favouriteBy[i] == &player) {
			favouriteBy.removeAt(i);
			break;
		}
	}
}

void Quiz::shuffleQuestionsUsingRand(MyVector<Question*>& quiz) {
	size_t n = quiz.getVectorSize();
	for (size_t i = 0; i < n - 1; ++i) {
		size_t j = i + rand() % (n - i);
		Question* temp = quiz[i];
		quiz[i] = quiz[j];
		quiz[j] = temp;
	}
}

void Quiz::copyFrom(const Quiz& other) {
	this->nextID = other.nextID;
	this->title = other.title;
	this->author = other.author;
	questions.clear();
	for (size_t i = 0; i < other.questions.getVectorSize(); ++i) {
		questions.pushBack(other.questions[i]->clone());
	}
	this->status = other.status;
	this->likedBy = other.likedBy;
	this->favouriteBy = other.favouriteBy;
	this->timesAttempted = other.timesAttempted;
}

void Quiz::freeQuestions() {
	for (size_t i = 0; i < this->questions.getVectorSize(); ++i) {
		delete this->questions[i];
	}
	this->questions.clear();
}

void Quiz::freeLikedBy() {
	this->likedBy.clear();
}

void Quiz::freeFavouriteBy() {
	this->favouriteBy.clear();
}

void Quiz::freeQuiz() {
	freeQuestions();
	freeLikedBy();
	freeFavouriteBy();
	this->title = MyString();
	this->author = nullptr;
	this->status = QuizStatus::PENDING;
	this->timesAttempted = 0;
}

Quiz::Quiz(const MyString& title, const Player* author, const MyVector<Question*> questions, QuizStatus status, const MyVector<const Player*> likedBy, const MyVector<const Player*> favouriteBy, size_t timesAttempted) {
	this->nextID = ++this->ID;
    setQuizTitle(title);
    setQuizAuthor(author);
    setQuestions(questions);
	setQuizStatus(status);
	setQuizLikedByList(likedBy);
	setQuizFavouriteByList(favouriteBy);
	setTimesAttempted(timesAttempted);
}

Quiz::Quiz() {
	this->nextID = ++this->ID;
	this->title = "Untitled Quiz";
	this->author = nullptr;
	this->status = QuizStatus::PENDING;
	this->questions = MyVector<Question*>();
	this->likedBy = MyVector<const Player*>();
	this->favouriteBy = MyVector<const Player*>();
	this->timesAttempted = 0;
}

Quiz::Quiz(const Quiz& other) {
	this->copyFrom(other);
}

Quiz& Quiz::operator=(const Quiz& other) {
	if (this != &other) {
		this->freeQuiz();
		this->copyFrom(other);
	}

	return *this;
}

Quiz::~Quiz() {
	this->freeQuiz();
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

void Quiz::setQuestions(const MyVector<Question*>& questions) {
	if (questions.isEmpty()) {
		throw std::invalid_argument("Quiz must have at least one question!");
	}

	this->questions.clear();
	for (size_t i = 0; i < questions.getVectorSize(); i++) {
		this->questions.pushBack(questions[i]->clone());
	}
}

void Quiz::setQuizStatus(QuizStatus status) {
	this->status = status;
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