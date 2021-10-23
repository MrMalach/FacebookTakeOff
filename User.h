#ifndef USER_H
#define USER_H

#include "Status.h"

class User
{
    std::string _name;
    std::string _bd;

    bool _canFriedsPost;

    std::vector<Status*> wall;
    
    std::vector<User*> friends;
public:
    User(const std::string&, const std::string&, const bool);
    ~User();

    void printWall() const;
    void printFrieds() const;

    void addStatus(Status*);
    void addFriend(User*);

    const std::string& getName() const;
    const bool checkIfAlreadyConnected(User*) const;
    const bool getCanFriedsPost() const;
    friend std::ostream& operator<<(std::ostream&, User*);
};

#endif