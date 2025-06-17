#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "MyString.h"
#include "User.h"
#include<stdexcept>

class User;

class Message {
public:
    Message(const MyString& content, User* sender, User* receiver);
    Message();

    void setContent(const MyString& content);
    void setSender(User* sender);
    void setReceiver(User* receiver);

    const MyString& getContent() const;
    User* getSender() const;
    User* getReceiver() const;

    void save(std::ofstream& out) const;
    void load(std::ifstream& in);

private:
    MyString content;
    User* sender = nullptr;
    User* receiver = nullptr;
};

#endif // !_MESSAGE_H