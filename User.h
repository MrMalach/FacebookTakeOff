#ifndef USER_H
#define USER_H

#include "Status.h"


class User
{
protected:
    std::string _name;
    
    std::vector<Status*>* wall;
    std::vector<User*>* friends;

public:
    User(const std::string&);
    ~User();

    virtual void printWall() const;
    void printFriends() const;

    void addStatus(Status*);
    void addFriend(User*);

    const std::string& getName() const;
    bool checkIfAlreadyConnected(User*) const;
    virtual bool getCanFriendsPost() const;
    virtual void print() const;
    virtual bool isPerson() const;
    bool removeUserFromPageFriendsList(const User* fan);
    friend const User& operator+=(User&, User&);
    friend bool operator>(const User&, const User&);
};

#endif //USER_H