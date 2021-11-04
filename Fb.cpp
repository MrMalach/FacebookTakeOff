#include "FB.h" 
    
FB::FB() : _usersCnt(0)
{
    try
    {
        Users = new(std::nothrow) UsersMapType;
        if(nullptr == Users)
            throw(std::invalid_argument("Allocation error"));
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
}

FB* FB::pFB{nullptr};

FB* FB::getInstance()
{
    if(nullptr == pFB)
        pFB = new (std::nothrow) FB();
    return pFB;
}

FB::~FB()
{
    for(auto& user : *Users)
    {
        for(User* u : *user.second)
            delete u;
        delete user.second;
    }   
}
    
bool FB::addUser(User* user)
{
    try
    {
        UsersMapType::const_iterator it = Users->find(user->getName());
        /*  Its possible that Users will shre a name.
            A vector will be created for a new name  */
        if(it == Users->end())
        {
            std::vector<User*>* v = new(std::nothrow) std::vector<User*>;
            if(nullptr == v)
                throw(std::invalid_argument("Allocation error"));
            v->push_back(user);
            // Store it in the Map (UsersMapType)
            (*Users)[user->getName()] = v;
            ++_usersCnt;
            return true;
        }
        it->second->push_back(user);
        ++_usersCnt;
        return true;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        delete user;
        return false;
    }
}

const size_t FB::getId(std::string message, size_t vecSize) const
{
    // For getting the index for the names vector.
    size_t id;
    do
    {
        std::cout << message << std::endl;
        id = 0;
        std::string _id;
        std::cin >> _id;
        for(int i = 0 ; i < _id.size() ; ++i)
            id = id * 10 + (size_t)(_id[i] - '0');

    } while (id >= vecSize || id < 0);

    return id;
}

User* FB::getUser(const std::string& name) const
{
    try
    {
        UsersMapType::const_iterator it = Users->find(name);
        if(it == Users->end())
        {
            throw(std::invalid_argument("No such user"));
        }
        
        if(it->second->size() == 1)
            return *(it->second->begin());

        /*  If there is more than one name
            show all users of same name and 
            let the user choose one     */
        for(int i = 0 ; i < it->second->size() ; ++i)
        {
            std::cout << i << ". ";
            (*(it->second->begin() + i))->print();
        }
        return *(it->second->begin() + getId("Choose which one", it->second->size()));
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return nullptr;
    }
}

const size_t FB::getUserCount() const
{
    return _usersCnt;
}

void FB::printAllUsers() const
{
    std::cout << "*******************************" << std::endl;
    for(auto& userNode : *Users)
        for(auto& user : *userNode.second)
            user->print();
    std::cout << "*******************************" << std::endl;
}

bool FB::newUser(std::string& name, std::string& bDay, bool& cws)
{
    
    User *user = nullptr;
    if(bDay == "")
    {
        user = new(std::nothrow) User(name);
    }
    else
    {
        user = new(std::nothrow) Person(name, bDay, cws);
    }
    if(nullptr == user)
            throw(std::invalid_argument("Allocation error"));

    return addUser(user);
}

bool FB::addStatus(std::string& name1, std::string& name2)
{
    /*  Get valid User names, get the status content
        Construct and run User::addStatus(...)    */
    try
    {    
        
        User* user2 = getUser(name2);
        if(nullptr == user2)
            throw(std::invalid_argument("No such user"));
        
        User* user1 = getUser(name1);
        if(nullptr == user1)
            throw(std::invalid_argument("No such user"));

        if(user1 != user2 && !user2->getCanFriendsPost())
            throw(std::invalid_argument("Cant write to that wall"));
            
        Status* status = new(std::nothrow) Status(readStatus());
        if(nullptr == status)
            throw(std::invalid_argument("Allocation error"));

        user2->addStatus(status);
        return true;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }   
}

void FB::showWall(std::string& name) const
{   try
    {
        User* user =  getUser(name);
        if(nullptr == user)
            throw(std::invalid_argument("No such user"));
        user->printWall();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool FB::connectUsers(std::string& name1, std::string& name2)
{
    /*  Get names of User to connect, 
        Validate all constraints   */
    try
    {
        User* user1 = getUser(name1);
        if(nullptr == user1)
            throw(std::invalid_argument("No such user"));
        
        User* user2 = getUser(name2);
        if(nullptr == user2)
            throw(std::invalid_argument("No such user"));

        if(user1 == user2)
            throw(std::invalid_argument("Cant connect to yourself :)"));

        if(!user2->isPerson())
            throw(std::invalid_argument("Pages cannot connect"));

        if(user1->checkIfAlreadyConnected(user2))
        {
            throw(std::invalid_argument("Already connected"));
        }

        *user1 += *user2;
        *user2 += *user1;
        return true;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

bool FB::removeFanFromPage(std::string& name1, std::string& name2)
{
    try
    {
        User* person = getUser(name2);
        User* page = getUser(name1);
        if(nullptr == person || nullptr == page)
            throw(std::invalid_argument("No such user"));

        if(!person->isPerson() || page->isPerson())
            throw(std::invalid_argument("Choose a friend out of a page friend list"));

        if(!page->removeUserFromPageFriendsList(person))
            throw(std::invalid_argument("No such fan"));

        return person->removeUserFromPageFriendsList(page);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}

void FB::showUsersFriendsList(std::string& name) const
{
    try
    {
        User* user = getUser(name);
        if(nullptr == user)
            throw(std::invalid_argument("No such user"));
        user->printFriends();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
}