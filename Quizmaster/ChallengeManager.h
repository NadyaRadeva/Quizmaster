#ifndef _CHALLENGEMANAGER_H
#define _CHALLENGEMANAGER_H

#include "MyVector.hpp"
#include "ChallengeTemplate.h"

class ChallengeManager {
public:
	ChallengeManager(const MyVector<ChallengeTemplate>& templates);
	ChallengeManager();

	void setTemplates(const MyVector<ChallengeTemplate>& templates);

	void addTemplate(const ChallengeTemplate& tmpl);
	const ChallengeTemplate* getById(const MyString& id) const;
	const MyVector<ChallengeTemplate>& getAllTemplates() const;

private:
	MyVector<ChallengeTemplate> templates;
};

#endif // !_CHALLENGEMANAGER_H