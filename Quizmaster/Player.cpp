#include "Player.h"

#include "Report.h"
#include "ReportManager.h"

size_t Player::getPoints() const {
	return this->points;
}

size_t Player::getLevel() const {
	return this->level;
}

const MyVector<Quiz*>& Player::getCreatedQuizzes() const {
	return this->createdQuizzes;
}

const MyVector<Quiz*>& Player::getLikedQuizzes() const {
	return this->likedQuizzes;
}

const MyVector<Quiz*>& Player::getFavouriteQuizzes() const {
	return this->favouriteQuizzes;
}

const MyVector<ChallengeProgress>& Player::getChallenges() const {
	return this->challenges;
}

const MyVector<Message>& Player::getMessages() const {
	return this->messages;
}

const QuizManager* Player::getQuizManager() const {
	return this->quizManager;
}

Quiz* Player::addCreatedQuiz(const MyString& title) {
	if (!quizManager) {
		throw std::runtime_error("QuizManager is not set!");
	}

	std::cout << "Enter number of questions: ";
	int n;
	std::cin >> n;
	if (n <= 0 || !std::cin) {
		throw std::invalid_argument("Number of questions must be greater than 0.");
	}
	std::cin.ignore();

	MyVector<Question*> questions;

	for (int i = 0; i < n; ++i) {
		std::cout << "Enter question " << (i + 1) << " type (T/F, SC, MC, ShA, MP): ";
		char typeBuffer[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
		std::cin.getline(typeBuffer, MAX_BUFFER_SIZE_PLAYER_CLASS);
		MyString type(typeBuffer);

		Question* q = nullptr;
		if (type == "T/F") {
			q = createTFQuestion();
		}
		else if (type == "SC") {
			q = createSCQuestion();
		}
		else if (type == "MC") {
			q = createMCQuestion();
		}
		else if (type == "ShA") {
			q = createShAQuestion();
		}
		else if (type == "MP") {
			q = createMPQuestion();
		}
		else {
			std::cout << "Unknown question type! Try again!\n";
			--i;
			continue;
		}

		questions.pushBack(q);
	}

	Quiz* newQuiz = new Quiz(title, this, questions, QuizStatus::PENDING, MyVector<const Player*>(), MyVector<const Player*>(), 0);

	createdQuizzes.pushBack(newQuiz);

	if (quizManager) {
		const_cast<QuizManager*>(quizManager)->addQuiz(newQuiz);
	}

	std::cout << "Quiz created and pending approval!";
	return newQuiz;
}

void Player::addLikedQuiz(size_t quizId) {
	Quiz* quiz = quizManager->getQuizById(quizId);
	if (!quiz)
		throw std::runtime_error("Quiz with given ID not found.");

	for (size_t i = 0; i < likedQuizzes.getVectorSize(); ++i) {
		if (likedQuizzes[i]->getQuizId() == quizId)
			return;
	}

	likedQuizzes.pushBack(quiz);
	quiz->addLike(*this);
}

void Player::removeLikedQuiz(size_t quizId) {
	for (size_t i = 0; i < this->likedQuizzes.getVectorSize(); ++i) {
		if (this->likedQuizzes[i]->getQuizId() == quizId) {
			Quiz* quizToRemove = this->likedQuizzes[i];
			this->likedQuizzes.remove(quizToRemove);
			return;
		}
	}

	throw std::invalid_argument("Quiz with the given ID not found in liked quizzes!");
}

void Player::addFavouriteQuiz(size_t quizId) {
	Quiz* quiz = quizManager->getQuizById(quizId);
	if (!quiz)
		throw std::runtime_error("Quiz with given ID not found.");

	for (size_t i = 0; i < favouriteQuizzes.getVectorSize(); ++i) {
		if (favouriteQuizzes[i]->getQuizId() == quizId)
			return;
	}

	favouriteQuizzes.pushBack(quiz);
	quiz->addFavourite(*this);
}

void Player::removeFavouriteQuiz(size_t quizId) {
	for (size_t i = 0; i < this->favouriteQuizzes.getVectorSize(); ++i) {
		if (this->favouriteQuizzes[i]->getQuizId() == quizId) {
			Quiz* quizToRemove = this->favouriteQuizzes[i];
			this->favouriteQuizzes.remove(quizToRemove);
			return;
		}
	}

	throw std::invalid_argument("Quiz with the given ID not found in favourite quizzes!");
}

void Player::saveLikedQuizzesToFile(const char* filename) const {
	std::ofstream out(filename);
	if (!out.is_open()) {
		return;
	}

	for (size_t i = 0; i < this->likedQuizzes.getVectorSize(); ++i) {
		if (likedQuizzes[i]) {
			out << likedQuizzes[i]->getQuizId() << "\n";
		}
	}

	out.close();
}

void Player::loadLikedQuizzesFromFile(const char* filename, QuizManager* quizManager) {
	std::ifstream in(filename);
	if (!in.is_open() || !quizManager) {
		return;
	}

	size_t id = 0;
	while (in >> id) {
		Quiz* quiz = quizManager->getQuizById(id);
		if (quiz) {
			likedQuizzes.pushBack(quiz);
		}
	}

	in.close();
}

void Player::saveFavouriteQuizzesToFile(const char* filename) const {
	std::ofstream out(filename);
	if (!out.is_open()) {
		return;
	}

	for (size_t i = 0; i < this->favouriteQuizzes.getVectorSize(); ++i) {
		if (favouriteQuizzes[i]) {
			out << favouriteQuizzes[i]->getQuizId() << '\n';
		}
	}

	out.close();
}

void Player::loadFavouriteQuizzesFromFile(const char* filename, QuizManager* quizManager) {
	std::ifstream in(filename);
	if (!in.is_open() || quizManager == nullptr) {
		return;
	}

	favouriteQuizzes.clear();

	size_t id;
	while (in >> id) {
		Quiz* quiz = quizManager->getQuizById(id);
		if (quiz != nullptr) {
			favouriteQuizzes.pushBack(quiz);
		}
	}

	in.close();
}

void Player::saveCreatedQuizzesToFile(const char* filename) const {
	std::ofstream out(filename);
	if (!out.is_open()) return;

	for (size_t i = 0; i < this->createdQuizzes.getVectorSize(); ++i) {
		if (createdQuizzes[i] != nullptr) {
			out << createdQuizzes[i]->getQuizId() << '\n';
		}
	}

	out.close();
}

void Player::loadCreatedQuizzesFromFile(const char* filename, QuizManager* quizManager) {
	std::ifstream in(filename);
	if (!in.is_open() || quizManager == nullptr) {
		return;
	}

	createdQuizzes.clear();

	size_t id;
	while (in >> id) {
		Quiz* quiz = quizManager->getQuizById(id);
		if (quiz != nullptr) {
			createdQuizzes.pushBack(quiz);
		}
	}

	in.close();
}

void Player::saveMessagesToFile(const char* filename) const {
	std::ofstream out(filename);
	if (!out.is_open()) return;

	for (size_t i = 0; i < this->messages.getVectorSize(); ++i) {
		out << messages[i].getContent() << '\n';
	}

	out.close();
}

void Player::loadMessagesFromFile(const char* filename) {
	std::ifstream in(filename);
	if (!in.is_open()) {
		return;
	}

	messages.clear();

	char ch;
	MyString currentLine;

	while (in.get(ch)) {
		if (ch == '\n') {
			if (!currentLine.isEmpty()) {
				messages.pushBack(Message(currentLine, nullptr, nullptr));
				currentLine.clear();
			}
		}
		else {
			currentLine += ch;
		}
	}

	if (!currentLine.isEmpty()) {
		messages.pushBack(Message(currentLine, nullptr, nullptr));
	}

	in.close();
}

void Player::updateChallengeProgress(const ChallengeTemplate& templateData, size_t increment) {
	for (size_t i = 0; i < challenges.getVectorSize(); ++i) {
		if (challenges[i].getTemplateId() == templateData.getId()) {
			challenges[i].incrementProgress(increment, templateData.getQuizzesGoal());
			return;
		}
	}

	ChallengeProgress newProgress(templateData.getId());
	newProgress.incrementProgress(increment, templateData.getQuizzesGoal());
	challenges.pushBack(newProgress);
}

void Player::viewChallenges(const ChallengeManager& templateManager) const {
	for (size_t i = 0; i < challenges.getVectorSize(); ++i) {
		const ChallengeProgress& progress = challenges[i];
		const ChallengeTemplate* tmpl = templateManager.getById(progress.getTemplateId());

		if (!tmpl) {
			std::cout << "Template not found for ID: " << progress.getTemplateId() << std::endl;
			continue;
		}

		std::cout << "Challenge: " << tmpl->getTitle() << std::endl;
		std::cout << "Type: " << static_cast<int>(tmpl->getType()) << std::endl;
		std::cout << "Progress: " << progress.getProgress() << " / " << tmpl->getQuizzesGoal() << std::endl;
		std::cout << "Completed: " << (progress.getIsCompleted() ? "Yes" : "No") << "\n";
		if (progress.getIsCompleted()) {
			time_t completedTime = progress.getTimeCompleted();
			char* timeStr = std::ctime(&completedTime);
			if (timeStr) {
				std::cout << "Completed on: " << timeStr;
			}
			else {
				std::cout << "Completed on: [unknown time]" << std::endl;
			}
		}
		std::cout << "--------------------------" << std::endl;
	}
}

void Player::viewUnfinishedChallenges(const ChallengeManager& templateManager) const {
	bool hasAny = false;
	for (size_t i = 0; i < challenges.getVectorSize(); ++i) {
		const ChallengeProgress& progress = challenges[i];
		if (progress.getIsCompleted()) {
			continue;
		}

		const ChallengeTemplate* tmpl = templateManager.getById(progress.getTemplateId());
		if (!tmpl) {
			continue;
		}

		hasAny = true;
		std::cout << "Challenge: " << tmpl->getTitle() << std::endl;
		std::cout << "Type: " << static_cast<int>(tmpl->getType()) << std::endl;
		std::cout << "Progress: " << progress.getProgress() << " / " << tmpl->getQuizzesGoal() << std::endl;
		std::cout << "--------------------------" << std::endl;
	}

	if (!hasAny) {
		std::cout << "No unfinished challenges." << std::endl;
	}
}

void Player::viewFinishedChallenges(const ChallengeManager& templateManager) const {
	bool hasAny = false;
	for (size_t i = 0; i < challenges.getVectorSize(); ++i) {
		const ChallengeProgress& progress = challenges[i];
		if (!progress.getIsCompleted()) {
			continue;
		}

		const ChallengeTemplate* tmpl = templateManager.getById(progress.getTemplateId());
		if (!tmpl) {
			continue;
		}

		hasAny = true;
		std::cout << "Challenge: " << tmpl->getTitle() << std::endl;
		std::cout << "Type: " << static_cast<int>(tmpl->getType()) << std::endl;
		std::cout << "Progress: " << progress.getProgress() << " / " << tmpl->getQuizzesGoal() << std::endl;

		time_t completionTime = progress.getTimeCompleted();
		std::cout << "Completed on: " << std::ctime(&completionTime);

		std::cout << "--------------------------" << std::endl;
	}

	if (!hasAny) {
		std::cout << "No finished challenges." << std::endl;
	}
}


void Player::viewUser(const MyString& userName, const UserManager& userManager) const {
	const User* user = userManager.findPlayerByUserName(userName);
	if (!user) {
		std::cout << userName << " not found.!";
		return;
	}

	std::cout << "User profile:" << std::endl;
	user->print(std::cout);
}

void Player::reportQuiz(size_t quizId, const MyString& reason, ReportManager& reportManager) {
	if (!quizManager) {
		std::cout << "Quiz manager is not available!" << std::endl;
		return;
	}

	Quiz* quiz = quizManager->getQuizById(quizId);
	if (!quiz) {
		std::cout << "Quiz not found!" << std::endl;
		return;
	}

	time_t now = time(nullptr);
	Report report(now, this, quizId, reason);
	reportManager.addReport(report);

	std::cout << "Report submitted successfully!" << std::endl;
}

void Player::startQuiz(size_t quizId, const MyString& mode, bool shuffle) {
	if (!quizManager) {
		std::cout << "QuizManager is not set!" << std::endl;
		return;
	}

	Quiz* quiz = quizManager->getQuizById(quizId);
	if (!quiz) {
		std::cout << "Quiz with ID [" << quizId << "] not found!" << std::endl;
		return;
	}

	if (quiz->getQuizStatus() == QuizStatus::PENDING) {
		std::cout << "Quiz is not approved yet!" << std::endl;
		return;
	}

	QuizTypes quizMode;
	MyString modeLower = mode.toLower();
	if (modeLower == "test") {
		quizMode = QuizTypes::TEST;
	}
	else if (modeLower == "normal") {
		quizMode = QuizTypes::NORMAL;
	}
	else {
		std::cout << "Invalid quiz mode: " << mode << std::endl;
		return;
	}

	switch (quizMode) {
	case QuizTypes::NORMAL:
		quiz->runNormalMode(*this, shuffle);
		break;
	case QuizTypes::TEST:
		quiz->runTestMode(*this, shuffle);
		break;
	}
}

void Player::saveQuizToFile(size_t quizId, const MyString& filepath) const {
	if (!quizManager) {
		std::cout << "QuizManager is not set!" << std::endl;
		return;
	}

	const Quiz* quiz = quizManager->getQuizById(quizId);
	if (!quiz) {
		std::cout << "Quiz with ID [" << quizId << "] not found!" << std::endl;
		return;
	}

	if (quiz->getQuizStatus() == QuizStatus::PENDING) {
		std::cout << "Quiz is not approved yet!" << std::endl;
		return;
	}

	if (filepath.getLength() == 0) {
		std::cout << "Filepath cannot be empty!" << std::endl;
		return;
	}

	try {
		quiz->saveToFile(filepath);
		std::cout << "Quiz saved to file successfully!" << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "Error saving quiz to file: " << e.what() << std::endl;
	}
}

Player::Player(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password) {
	setUserFirstName(firstName);
	setUserLastName(lastName);
	setUserName(userName);
	setUserPassword(password);
	this->points = 0;
	this->level = 1;
	this->createdQuizzes = MyVector<Quiz*>();
	this->likedQuizzes = MyVector<Quiz*>();
	this->favouriteQuizzes = MyVector<Quiz*>();
	this->challenges = MyVector<ChallengeProgress>();
	this->messages = MyVector<Message>();
	this->quizManager = nullptr;
}

Player::Player(const MyString& firstName, const MyString& lastName, const MyString& userName, const MyString& password, size_t points, size_t level, const MyVector<Quiz*>& createdQuizzes, const MyVector<Quiz*>& likedQuizzes, const MyVector<Quiz*>& favouriteQuizzes, const MyVector<ChallengeProgress>& challenges, const MyVector<Message>& messages, const QuizManager* quizManager) : User(firstName, lastName, userName, password) {
	setPoints(points);
	setLevel(level);
	setCreatedQuizzes(createdQuizzes);
	setLikedQuizzes(likedQuizzes);
	setFavouriteQuizzes(favouriteQuizzes);
	setChallenges(challenges);
	setMessages(messages);
	setQuizManager(quizManager);
}

Player::Player() : User() {
	this->points = 0;
	this->level = 1;
	this->createdQuizzes = MyVector<Quiz*>();
	this->likedQuizzes = MyVector<Quiz*>();
	this->favouriteQuizzes = MyVector<Quiz*>();
	this->challenges = MyVector<ChallengeProgress>();
	this->messages = MyVector<Message>();
	this->quizManager = nullptr;
}

Player::Player(const Player& other) {
	this->copyFrom(other);
}

Player& Player::operator=(const Player& other) {
	if (this != &other) {
		this->freeAll();
		this->copyFrom(other);
	}
	
	return *this;
}

Player::~Player() {
	this->freeAll();
}

User* Player::clone() const {
	return new Player(*this);
}

void Player::print(std::ostream& os) const {
	os << this->getUserFirstName() << " " << this->getUserLastName() << " " << "@" << this->getUserName() << std::endl;

	size_t requiredPoints = 0;
	if (level <= MILESTONE1) {
		requiredPoints = REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE1;
	}
	else if (level <= MILESTONE2) {
		requiredPoints = REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE2;
	}
	else if (level <= MILESTONE3) {
		requiredPoints = REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE3;
	}
	else {
		requiredPoints = REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE4;
	}

	os << "Level: " << this->getLevel() << "     " << this->points << "/" << requiredPoints << " points to next level!" << std::endl;

	os << "Created quizzes: " << std::endl;
	for (size_t i = 0; i < this->createdQuizzes.getVectorSize(); ++i) {
		os << "[" << this->createdQuizzes[i]->getQuizId() << "] " << this->createdQuizzes[i]->getQuizTitle() << std::endl;
	}

	os << "Liked quizzes: " << std::endl;
	for (size_t i = 0; i < this->likedQuizzes.getVectorSize(); ++i) {
		os << "[" << this->likedQuizzes[i]->getQuizId() << "] " << this->likedQuizzes[i]->getQuizTitle() << std::endl;
	}

	os << "Favourite quizzes: " << std::endl;
	for (size_t i = 0; i < this->favouriteQuizzes.getVectorSize(); ++i) {
		os << "[" << this->favouriteQuizzes[i]->getQuizId() << "] " << this->favouriteQuizzes[i]->getQuizTitle() << std::endl;
	}
}

bool Player::isAdmin() const {
	return false;
}

bool Player::isPlayer() const {
	return true;
}

void Player::save() const {
	MyString filename = "player_" + this->getUserName() + ".txt";
	std::ofstream out(filename.toChar());

	if (!out.is_open()) {
		std::cerr << "Error opening file for saving player " << this->getUserName() << "!" << std::endl;
		return;
	}

	out << this->getUserName() << std::endl;
	out << this->getUserPassword() << std::endl;
	out << this->getUserFirstName() << std::endl;
	out << this->getUserLastName() << std::endl;
	out << this->getPoints() << std::endl;
	out << this->getLevel() << std::endl;

	out << "Created Quiz Ids: " << this->createdQuizzes.getVectorSize() << std::endl;
	for (size_t i = 0; i < this->createdQuizzes.getVectorSize(); ++i) {
		out << createdQuizzes[i]->getQuizId() << std::endl;
	}

	out << "Liked Quiz Ids: " << this->likedQuizzes.getVectorSize() << std::endl;
	for (size_t i = 0; i < this->likedQuizzes.getVectorSize(); ++i) {
		out << likedQuizzes[i]->getQuizId() << std::endl;
	}

	out << "Favourite Quiz Ids: " << this->favouriteQuizzes.getVectorSize() << std::endl;
	for (size_t i = 0; i < this->favouriteQuizzes.getVectorSize(); ++i) {
		out << favouriteQuizzes[i]->getQuizId() << std::endl;
	}

	size_t unfinishedCount = 0;
	for (size_t i = 0; i < this->challenges.getVectorSize(); ++i) {
		if (!this->challenges[i].getIsCompleted()) {
			++unfinishedCount;
		}
	}

	out << "Unfinished Challenges: " << unfinishedCount << std::endl;
	for (size_t i = 0; i < this->challenges.getVectorSize(); ++i) {
		if (!this->challenges[i].getIsCompleted()) {
			this->challenges[i].print(out);

		}
	}

	size_t finishedCount = 0;
	for (size_t i = 0; i < this->challenges.getVectorSize(); ++i) {
		if (this->challenges[i].getIsCompleted()) {
			++finishedCount;
		}
	}

	out << "Finished Challenges: " << finishedCount << std::endl;
	for (size_t i = 0; i < this->challenges.getVectorSize(); ++i)
		if (challenges[i].getIsCompleted()) {
			challenges[i].print(out);
		}

	const MyVector<Message>& messages = getMessages();
	out << messages.getVectorSize() << std::endl;
	for (size_t i = 0; i < messages.getVectorSize(); i++) {
		out << messages[i].getContent();
	}

	out.close();
}

void Player::load(std::ifstream& in, QuizManager& quizManager) {
	if (!in.is_open()) {
		throw std::invalid_argument("Cannot open file!");
	}

	MyString username = MyString().readLine(in).trim();
	this->setUserName(username);

	MyString password = MyString().readLine(in).trim();
	this->setUserPassword(password);

	MyString firstName = MyString().readLine(in).trim();
	this->setUserFirstName(firstName);

	MyString lastName = MyString().readLine(in).trim();
	this->setUserLastName(lastName);

	int points = 0;
	in >> points;
	this->setPoints(points);

	int level = 0;
	in >> level;
	this->setLevel(level);

	in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');

	int createdCount = 0;
	in >> createdCount;
	in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');
	this->createdQuizzes.clear();
	for (int i = 0; i < createdCount; ++i) {
		int quizId;
		in >> quizId;
		in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');

		Quiz* quizPtr = quizManager.getQuizById(quizId);
		if (quizPtr != nullptr) {
			this->createdQuizzes.pushBack(quizPtr);
		}
	}

	int likedCount = 0;
	in >> likedCount;
	in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');
	this->likedQuizzes.clear();
	for (int i = 0; i < likedCount; ++i) {
		int quizId;
		in >> quizId;
		in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');

		Quiz* quizPtr = quizManager.getQuizById(quizId);
		if (quizPtr != nullptr) {
			this->likedQuizzes.pushBack(quizPtr);
		}
	}

	int favouriteCount = 0;
	in >> favouriteCount;
	in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');
	this->favouriteQuizzes.clear();
	for (int i = 0; i < favouriteCount; ++i) {
		int quizId;
		in >> quizId;
		in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');

		Quiz* quizPtr = quizManager.getQuizById(quizId);
		if (quizPtr != nullptr) {
			this->favouriteQuizzes.pushBack(quizPtr);
		}
	}

	size_t challengesCount = 0;
	in >> challengesCount;
	in.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');
	this->challenges.clear();
	for (size_t i = 0; i < challengesCount; ++i) {
		ChallengeProgress cp;
		cp.load(in);
		this->challenges.pushBack(cp);
	}
}

Question* Player::createTFQuestion() {
	std::cout << "Enter the question text:" << std::endl;
	char questionTextBufferTF[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');
	std::cin.getline(questionTextBufferTF, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString questionText(questionTextBufferTF);

	std::cout << "Enter total points for this question: " << std::endl;
	size_t totalPoints;
	std::cin >> totalPoints;
	std::cin.ignore(MAX_BUFFER_SIZE_PLAYER_CLASS, '\n');

	std::cout << "Enter the correct answer (true/false):" << std::endl;
	char correctAnswerBufferTF[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.getline(correctAnswerBufferTF, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString correctAnswerStr(correctAnswerBufferTF);

	bool correctAnswerBool = false;
	if (correctAnswerStr == "true" || correctAnswerStr == "True" || correctAnswerStr == "TRUE") {
		correctAnswerBool = true;
	}
	else if (correctAnswerStr == "false" || correctAnswerStr == "False" || correctAnswerStr == "FALSE") {
		correctAnswerBool = false;
	}
	else {
		std::cout << "Invalid input for correct answer, defaulting to false." << std::endl;
	}

	return new TrueOrFalseQuestion(questionText, totalPoints, correctAnswerBool);
}

Question* Player::createSCQuestion() {
	std::cout << "Enter the question text:" << std::endl;
	char questionTextBufferSC[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.getline(questionTextBufferSC, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString questionText(questionTextBufferSC);

	std::cout << "Enter total points for this question: " << std::endl;
	size_t totalPoints;
	std::cin >> totalPoints;
	std::cin.ignore();

	char bufferAnswerA[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	char bufferAnswerB[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	char bufferAnswerC[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	char bufferAnswerD[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];

	std::cout << "Enter answer A:" << std::endl;
	std::cin.getline(bufferAnswerA, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString answerA(bufferAnswerA);

	std::cout << "Enter answer B:" << std::endl;
	std::cin.getline(bufferAnswerB, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString answerB(bufferAnswerB);

	std::cout << "Enter answer C:" << std::endl;
	std::cin.getline(bufferAnswerC, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString answerC(bufferAnswerC);

	std::cout << "Enter answer D:" << std::endl;
	std::cin.getline(bufferAnswerD, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString answerD(bufferAnswerD);

	std::cout << "Enter the correct answer (A/B/C/D):" << std::endl;
	char correctAnswerLetter;
	std::cin >> correctAnswerLetter;
	std::cin.ignore();

	correctAnswerLetter += TO_UPPER_CASE_CHANGE;
	if (correctAnswerLetter != 'A' && correctAnswerLetter != 'B' &&
		correctAnswerLetter != 'C' && correctAnswerLetter != 'D') {
		std::cout << "Invalid correct answer letter. Defaulting to A." << std::endl;
		correctAnswerLetter = 'A';
	}

	SingleChoiceQuestion* question = new SingleChoiceQuestion(questionText, totalPoints, answerA, answerB, answerC, answerD, correctAnswerLetter);

	return question;
}

Question* Player::createMCQuestion() {
	std::cout << "Enter the question text:" << std::endl;
	char questionTextBufferMC[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.getline(questionTextBufferMC, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString questionText(questionTextBufferMC);

	std::cout << "Enter total points for this question:" << std::endl;
	size_t totalPoints;
	std::cin >> totalPoints;
	std::cin.ignore();

	MyVector<MyString> options;
	const char optionLabels[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
	size_t numOptions;

	std::cout << "Enter number of options (2-6):" << std::endl;
	std::cin >> numOptions;
	std::cin.ignore();

	if (numOptions < 2 || numOptions > 6) {
		std::cout << "Invalid number of options. Defaulting to 4." << std::endl;
		numOptions = 4;
	}

	char buffer[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	for (size_t i = 0; i < numOptions; ++i) {
		std::cout << "Enter option " << optionLabels[i] << ":" << std::endl;
		std::cin.getline(buffer, MAX_BUFFER_SIZE_PLAYER_CLASS);
		options.pushBack(MyString(buffer));
	}

	std::cout << "Enter the correct answer letters (e.g., AC for options A and C):" << std::endl;
	char correctAnswersBuffer[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.getline(correctAnswersBuffer, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString correctAnswersStr(correctAnswersBuffer);

	MyVector<char> correctAnswers;
	for (size_t i = 0; i < correctAnswersStr.getLength(); ++i) {
		correctAnswersStr[i] += TO_UPPER_CASE_CHANGE;
		if (correctAnswersStr[i] >= 'A' && correctAnswersStr[i] < 'A' + (char)(numOptions)) {
			correctAnswers.pushBack(correctAnswersStr[i]);
		}
	}

	if (correctAnswers.isEmpty()) {
		std::cout << "No valid correct answers provided. Defaulting to option A." << std::endl;
		correctAnswers.pushBack('A');
	}

	return new MultipleChoiceQuestion(questionText, totalPoints, options, correctAnswers);
}

Question* Player::createShAQuestion() {
	std::cout << "Enter the question text:" << std::endl;
	char questionTextBufferShA[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.ignore();
	std::cin.getline(questionTextBufferShA, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString questionText(questionTextBufferShA);

	std::cout << "Enter total points for this question:" << std::endl;
	size_t totalPoints;
	std::cin >> totalPoints;
	std::cin.ignore();

	std::cout << "Enter the correct short answer:" << std::endl;
	char correctAnswerBufferShA[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.getline(correctAnswerBufferShA, MAX_BUFFER_SIZE_PLAYER_CLASS + 1);
	MyString correctAnswer(correctAnswerBufferShA);

	return new ShortAnswerQuestion(questionText, totalPoints, correctAnswer);
}

Question* Player::createMPQuestion() {
	std::cout << "Enter the question text:" << std::endl;
	char questionTextBufferMP[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.ignore();
	std::cin.getline(questionTextBufferMP, MAX_BUFFER_SIZE_PLAYER_CLASS + 1);
	MyString questionText(questionTextBufferMP);

	std::cout << "Enter total points for this question:" << std::endl;
	size_t totalPoints;
	std::cin >> totalPoints;
	std::cin.ignore();

	size_t pairCount;
	std::cout << "Enter number of matching pairs:" << std::endl;
	std::cin >> pairCount;
	std::cin.ignore();

	MyVector<MyString> leftColumn, rightColumn;
	std::cout << "Enter items for the LEFT column:" << std::endl;
	for (size_t i = 0; i < pairCount; ++i) {
		std::cout << "Left[" << i + 1 << "]: ";
		char buffer[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
		std::cin.getline(buffer, MAX_BUFFER_SIZE_PLAYER_CLASS);
		leftColumn.pushBack(MyString(buffer));
	}

	std::cout << "Enter items for the RIGHT column:" << std::endl;
	for (size_t i = 0; i < pairCount; ++i) {
		std::cout << "Right[" << i + 1 << "]: ";
		char buffer[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
		std::cin.getline(buffer, MAX_BUFFER_SIZE_PLAYER_CLASS);
		rightColumn.pushBack(MyString(buffer));
	}

	std::cout << "Enter the correct answers as a sequence of matching positions (e.g. 1-3 2-1 3-2):" << std::endl;
	char answerBufferMP[MAX_BUFFER_SIZE_PLAYER_CLASS + 1];
	std::cin.getline(answerBufferMP, MAX_BUFFER_SIZE_PLAYER_CLASS);
	MyString correctAnswers(answerBufferMP);

	return new MatchingPairsQuestion(questionText, totalPoints, rightColumn, leftColumn, correctAnswers);
}

size_t Player::cumulativePointsForLevel(size_t level) {
	size_t points = 0;
	for (size_t i = 1; i < level; ++i) {
		if (i <= MILESTONE1) {
			points += REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE1;
		}
		else if (i <= MILESTONE2) {
			points += REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE2;
		}
		else if (i <= MILESTONE3) {
			points += REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE3;
		}
		else {
			points += REQUIRED_POINTS_LEVEL_TO_LEVEL_MILESTONE4;
		}
	}
	return points;
}

void Player::checkLevelUp() {
	while (level < MAX_LEVEL && points >= cumulativePointsForLevel(level + 1)) {
		level++;
		MyString msg = MyString("Congratulations! You have reached level ") + MyString::toStr(level) + MyString("!");
		receiveMessage(Message(msg, nullptr, nullptr));
	}
}

void Player::copyFrom(const Player& other) {
	this->setUserFirstName(other.getUserFirstName());
	this->setUserLastName(other.getUserLastName());
	this->setUserName(other.getUserName());
	this->setUserPassword(other.getUserPassword());

	this->points = other.points;
	this->level = other.level;

	this->createdQuizzes = other.createdQuizzes;
	this->likedQuizzes = other.likedQuizzes;
	this->favouriteQuizzes = other.favouriteQuizzes;

	this->challenges = other.challenges;
	this->messages = other.messages;
	this->quizManager = other.quizManager;
}

void Player::freeCreatedQuizzes() {
	this->createdQuizzes.clear();
}

void Player::freeLikedQuizzes() {
	this->likedQuizzes.clear();
}

void Player::freeFavouriteQuizzes() {
	this->favouriteQuizzes.clear();
}

void Player::freeAll() {
	this->freeCreatedQuizzes();
	this->freeFavouriteQuizzes();
	this->freeLikedQuizzes();
}

void Player::setPoints(size_t points) {
	this->points = points;
}

void Player::setLevel(size_t level) {
	this->level = level;
}

void Player::setCreatedQuizzes(const MyVector<Quiz*>& createdQuizzes) {
	this->createdQuizzes = createdQuizzes;
}

void Player::setLikedQuizzes(const MyVector<Quiz*>& likedQuizzes) {
	this->likedQuizzes = likedQuizzes;
}

void Player::setFavouriteQuizzes(const MyVector<Quiz*>& favouriteQuizzes) {
	this->favouriteQuizzes = favouriteQuizzes;
}

void Player::setChallenges(const MyVector<ChallengeProgress>& challenges) {
	this->challenges = challenges;
}

void Player::setMessages(const MyVector<Message>& messages) {
	this->messages = messages;
}

void Player::setQuizManager(const QuizManager* quizManager) {
	if (this->quizManager == nullptr) {
		throw std::invalid_argument("QuizManager is not set!");
	}

	this->quizManager = new QuizManager(*quizManager);
}

void Player::addPoints(size_t points) {
	this->points += points;
	this->checkLevelUp();
}

void Player::receiveMessage(const Message& message) {
	this->messages.pushBack(message);
}

void Player::viewAllMessages() const {
	for (size_t i = 0; i < this->messages.getVectorSize(); ++i) {
		std::cout << this->messages[i].getContent() << std::endl;
	}
}