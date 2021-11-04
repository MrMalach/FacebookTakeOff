#ifndef PERSON_H
#define PERSON_H

#include "User.h"


class Person : public User
{
    std::string _bday;
    bool _canFriedsPost;

public:
    Person(const std::string&, const std::string&, const bool);

    void printWall() const;
    bool getCanFriendsPost() const;
    bool isPerson() const;
    void print() const;
};


#endif // PERSON_H