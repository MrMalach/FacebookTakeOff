#ifndef FB_H
#define FB_H

#include<map>
#include "utils.h"


// **** For search and insertion in logarithmic complexity *********

typedef std::map<std::string, std::vector<User*>*> UsersMapType;//**

// *****************************************************************
class FB
{
    size_t _usersCnt;
    UsersMapType* Users;
    
    FB();
    static FB* pFB;

    const size_t getId(std::string, size_t) const;
    bool addUser(User*);
    User* getUser(const std::string&) const;

public:
    static FB* getInstance();
    ~FB();

    const size_t getUserCount() const;
    void printAllUsers() const;
    bool newUser(std::string&, std::string&, bool&);
    bool addStatus(std::string&, std::string&);
    void showWall(std::string&) const;
    bool connectUsers(std::string&, std::string&);
    bool removeFanFromPage(std::string&, std::string&);
    void showUsersFriendsList(std::string&) const;
};

#endif