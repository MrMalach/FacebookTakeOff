#include "User.h"



User::User(const std::string& name, const std::string& bd, const bool cws)
    : _name(name), _bd(bd), _canFriedsPost(cws){}

User::~User()
{
    std::cout << "in user d'tor\n";
    for(Status* status : wall)
        delete status;
}

void User::printWall() const
{
    std::cout << (_canFriedsPost ? "  Can " : "Cannot " ) << "post to wall" << std::endl;
    std::cout << "*******************************" << std::endl;
    for(Status* status : wall)
        std::cout << *status << std::endl;
    std::cout << "*******************************" << std::endl;
}

void User::printFrieds() const
{
    std::cout << "*******************************" << std::endl;
    for(User* friend_ : friends)
        std::cout << friend_ << std::endl;
    std::cout << "*******************************" << std::endl;
}

void User::addStatus(Status* status)
{
    wall.push_back(status);
}

void User::addFriend(User* user)
{
    friends.push_back(user);
}

const std::string& User::getName() const
{
    return _name;
}

const bool User::checkIfAlreadyConnected(User* otherUser) const
{
    for(User* user : friends)
    {
        if(otherUser == user)
            return true;
    }
    return false;
}

const bool User::getCanFriedsPost() const
{
    return _canFriedsPost;
}


std::ostream& operator<<(std::ostream& o, User* user)
{
    o << (*user)._name << " " << (*user)._bd;
    return o;
}
