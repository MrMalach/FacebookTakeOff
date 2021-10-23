#include "FB.h" 
    
FB::FB() : _usersCnt(0)
{
    try
    {
        Users = new UsersMapType;
        if(nullptr == Users)
            throw(std::invalid_argument("Allocation error"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
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
        if(it == Users->end())
        {
            std::vector<User*>* v = new std::vector<User*>;
            if(nullptr == v)
                throw(std::invalid_argument("Allocation error"));
            v->push_back(user);
            (*Users)[user->getName()] = v;
            ++_usersCnt;
            return true;
        }
        it->second->push_back(user);
        ++_usersCnt;
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

const size_t FB::getId(std::string message, size_t vecSize) const
{
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
        
        for(int i = 0 ; i < it->second->size() ; ++i)
        {
            std::cout << "1. " << *(it->second->begin() + i) << std::endl;
        }
        return *(it->second->begin() + getId("Choose wich one", it->second->size()));
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
            std::cout << user << std::endl;
    std::cout << "*******************************" << std::endl;
}

const int to_int(std::string s)
{
    int n = 0;
    for(char c : s)
    {
        if(c < '0' || c > '9')
            throw(std::invalid_argument("Bad input"));
        n = n * 10 + c - '0';
    }
    return n;
}

const bool FB::addFriend()
{
    try
    {
        std::cout << "Enter name: " << std::endl;
        std::string name;
        std::cin >> name;

        std::cout << "Enter date of birth:" << std::endl;
        std::string db;

        std::cout << "Day:" << std::endl;
        std::cin >> db;
        int d = to_int(db);
        if(d < 1 || d > 31)
            throw(std::invalid_argument("Bad input"));
        
        std::cout << "Month:" << std::endl;
        std::cin >> db;
        int m = to_int(db);
        if(m < 1 || m > 12)
            throw(std::invalid_argument("Bad input"));
        
        std::cout << "Year:" << std::endl;
        std::cin >> db;
        int y = to_int(db);
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        time_t tt = std::chrono::system_clock::to_time_t(now);
        tm local_tm = *localtime(&tt);
        if(y < 1900 || y > local_tm.tm_year + 1900 - 18)
            throw(std::invalid_argument("Bad input"));
        db = std::to_string(d) + '/' + std::to_string(m) + '/' + std::to_string(y);
        char cws = '2';
        while(cws != '0' && cws != '1')
        {
            std::cout << "Can frieds write status? " << std::endl;
            std::cin >> cws;
        }
    
        User* user = new(std::nothrow) User(name, db, (cws == '1' ? true : false));
        if(nullptr == user)
            throw(std::invalid_argument("Allocation error"));
        addUser(user);
        return true;
    }
    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

const bool FB::addStatus()
{
    try
    {    
        std::cout << "To whom do you want to write status? " << std::endl;
        std::string n;
        std::cin >> n;
        User* user2 = getUser(n);
        if(nullptr == user2)
            throw(std::invalid_argument("No such user"));
        
        std::cout << "What is your name ? " << std::endl;
        std::cin >> n; 
        User* user1 = getUser(n);
        if(nullptr == user1)
            throw(std::invalid_argument("No such user"));
        if(user1 != user2 && !user2->getCanFriedsPost())
            throw(std::invalid_argument("Cant write to that wall"));
        std::cout << "Enter status: " << std::endl;
        std::string _status;
        std::cin.ignore(); 
        std::getline(std::cin, _status);
        
        Status* status = new(std::nothrow) Status(_status);
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

void FB::showWall() const
{   try
    {
        std::cout << "Wich user wall? " << std::endl;
        std::string n;
        std::cin >> n;
        
        User* user =  getUser(n);
        if(nullptr == user)
            throw(std::invalid_argument("No such user"));
        user->printWall();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

const bool FB::connectFrieds()
{
    try
    {
        std::cout << "Who would you want to connect to ? " << std::endl;
        std::string n;
        std::cin >> n;
        User* user1 = getUser(n);
        if(nullptr == user1)
            throw(std::invalid_argument("No such user"));
        
        std::cout << "What is your name? " << std::endl;
        std::cin >> n;
        User* user2 = getUser(n);
        if(nullptr == user2)
            throw(std::invalid_argument("No such user"));
        
        if(user1->checkIfAlreadyConnected(user2))
        {
            throw(std::invalid_argument("Already connected"));
        }
        user1->addFriend(user2);
        user2->addFriend(user1);
        return true;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
}

void FB::showFriendFrieds() const
{
    try
    {
        std::cout << "Wich user friends list ? " << std::endl;
        std::string n;
        std::cin >> n;
        User* user = getUser(n);
        if(nullptr == user)
            throw(std::invalid_argument("No such user"));
        user->printFrieds();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}