#include "User.h"


User::User(const std::string& name)
    : _name(name)
    {
        try
        {
            wall = new(std::nothrow) std::vector<Status*>;
            friends = new(std::nothrow) std::vector<User*>;
            if(nullptr == wall || nullptr == friends)
                throw(std::invalid_argument("Allocation error"));
        }
        catch(const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
            if(wall)
                delete wall;
            if(friends)
                delete friends;
        }
    }
    
User::~User()
{
    std::cout << "in user d'tor\n";
    for(Status* status : *wall)
    {
        delete status;
    }
    delete wall;
    delete friends;   
}

void User::printWall() const
{
    std::cout << "*******************************" << std::endl;
    for(int i = 0 ; i < wall->size() ; ++i)
        std::cout << *(*wall)[i] << std::endl;
    std::cout << "*******************************" << std::endl;
}

void User::printFriends() const
{
    std::cout << "*******************************" << std::endl;
    for(int i = 0 ; i < friends->size() ; ++i)
        (*friends)[i]->print();
    std::cout << "*******************************" << std::endl;
}

void User::addStatus(Status* status)
{
    wall->push_back(status);
}

void User::addFriend(User* user)
{
    friends->push_back(user);
}

const User& operator+=(User& lhs, User& rhs)
{
    lhs.friends->push_back(&rhs);
    return lhs;
}

const std::string& User::getName() const
{
    return _name;
}

const bool User::checkIfAlreadyConnected(User* otherUser) const
{
    for(User* user : *friends)
    {
        if(otherUser == user)
            return true;
    }
    return false;
}

const bool User::getCanFriedsPost() const
{
    return false;
}

const bool User::isPerson() const
{
    return false;
}

const bool User::removeUserFromPageFriendsList(const User* other)
{
    for(int i = 0 ; i < friends->size() ; ++i)
    {
        if((*friends->begin() + i) == other)
            friends->erase(friends->begin() + i);
        return true;
    }
    return false;
}

void User::print() const
{
    std::cout << _name << std::endl;
}

const bool operator>(const User& lhs, const User& rhs)
{
    return lhs.friends->size() > rhs.friends->size();
}

