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

const bool getBoolChoice(std::string msg)
{
    char b = '9';
    while(b != '1' && b != '2' && b != 'y' && b != 'n')
    {
        std::cout << msg << std::endl;
        std::cin >> b;
    }
    return (b == '1' || b == 'y') ? true : false;
}

const bool FB::addNewUser()
{
    /*  Get valid values for User type,
        If for User (page) or for Person.
        Construct one of the two and run 
        FB::addUser(...)                */
    try
    {
        User* user = nullptr;
        const bool isPerson = getBoolChoice("1. Person\n2. Page\n");

        std::cout << "Enter name: " << std::endl;
        std::string name;
        std::cin >> name;
        
        if(!isPerson)
        {
            user = new(std::nothrow) User(name);
        }
        else
        {
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
            if(y < local_tm.tm_year + 1900 - 120 || y > local_tm.tm_year + 1900)
                throw(std::invalid_argument("Bad input"));
            db = std::to_string(d) + '/' + std::to_string(m) + '/' + std::to_string(y);
            const bool cws = getBoolChoice("Can frieds write status? (y, n)");

            user = new(std::nothrow) Person(name, db, cws);
        }
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
    /*  Get valid User names, get the status content
        Construct and run User::addStatus(...)    */
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
        std::cout << "which user wall? " << std::endl;
        std::string n;
        std::cin >> n;
        
        User* user =  getUser(n);
        if(nullptr == user)
            throw(std::invalid_argument("No such user"));
        user->printWall();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
}

const bool FB::connectUsers()
{
    /*  Get names of User to connect, 
        Validate all constraints   */
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
        if(user1 == user2)
            throw(std::invalid_argument("Cant connect to yourself :)"));

        if(!user2->isPerson())
            throw(std::invalid_argument("Pages cannot connect"));

        if(user1->checkIfAlreadyConnected(user2))
        {
            throw(std::invalid_argument("Already connected"));
        }
        //user1->addFriend(user2);
        //user2->addFriend(user1);
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

const bool FB::removeFanFromPage()
{
    try
    {
        std::cout << "Who would you want to remove? " << std::endl;
        std::string n;
        std::cin >> n;
        User* person = getUser(n);
        std::cout << "which page? " << std::endl;
        std::cin >> n;
        User* page = getUser(n);
        if(nullptr == person || nullptr == page)
            throw(std::invalid_argument("No such user"));
        if(!person->isPerson() || page->isPerson())
            throw(std::invalid_argument("Choose a friend out of a page friend list"));
        if(!page->removeUserFromPageFriendsList(person))
            throw(std::invalid_argument("No such fan"));
        person->removeUserFromPageFriendsList(page);
        return true;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}

void FB::showUsersFriendsList() const
{
    try
    {
        std::cout << "which user friends list ? " << std::endl;
        std::string n;
        std::cin >> n;
        User* user = getUser(n);
        if(nullptr == user)
            throw(std::invalid_argument("No such user"));
        user->printFriends();
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
}