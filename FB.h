#ifndef FB_H
#define FB_H

#include<map>
#include "User.h"

typedef std::map<std::string, std::vector<User*>*> UsersMapType;

class FB
{
    size_t _usersCnt;
    UsersMapType* Users;
    const size_t getId(std::string, size_t) const;

    bool addUser(User*);
    User* getUser(const std::string&) const;
public:

    FB();
    ~FB();
    
    const size_t getUserCount() const;
    void printAllUsers() const;

// Main menu functions:
    const bool addNewUser();
    const bool addStatus();
    void showWall() const;
    const bool connectFrieds();
    void showFriendFrieds() const;
};


#endif