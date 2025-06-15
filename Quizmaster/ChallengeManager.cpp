#include "ChallengeManager.h"

ChallengeManager::ChallengeManager(const MyVector<ChallengeTemplate>& templates) {
	setTemplates(templates);
}

ChallengeManager::ChallengeManager() {
	this->templates = MyVector<ChallengeTemplate>();
}

void ChallengeManager::setTemplates(const MyVector<ChallengeTemplate>& templates) {
	this->templates.clear();
	for (size_t i = 0; i < templates.getVectorSize(); ++i) {
		this->templates.pushBack(templates[i]);
	}
}

void ChallengeManager::addTemplate(const ChallengeTemplate& tmpl) {
    for (size_t i = 0; i < this->templates.getVectorSize(); i++) {
        if (this->templates[i].getId() == tmpl.getId()) {
            throw std::invalid_argument("Challenge template with this ID already exists!");
        }
    }

    templates.pushBack(tmpl);
}

const ChallengeTemplate* ChallengeManager::getById(const MyString& id) const {
    for (size_t i = 0; i < templates.getVectorSize(); i++) {
        if (templates[i].getId() == id) {
            return &templates[i];
        }
    }
    return nullptr;
}

const MyVector<ChallengeTemplate>& ChallengeManager::getAllTemplates() const {
	return this->templates;
}