#include "Person.h"


Person::Person(const std::string& name, const std::string& bday, const bool cws)
    : User{name}, _bday(bday), _canFriedsPost(cws){};

const bool Person::getCanFriedsPost() const
{
    return _canFriedsPost;
}

void Person::printWall() const
{
    std::cout << (_canFriedsPost ? "  Can " : "Cannot " ) << "post to wall" << std::endl;
    User::printWall();
}

const bool Person::isPerson() const
{
    return true;
}

void Person::print() const
{
    std::cout << _name << " " << _bday << std::endl;
}