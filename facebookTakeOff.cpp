#include "FB.h"


int main()
{
    try
    {
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        FB* fb = FB::getInstance();
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
        if(nullptr == fb)
            throw(std::invalid_argument("Allocation error"));
        
        while(true)
        {
            switch(getChoice())
            {
                case '1':
                    {
                        std::string name, bDay;
                        bool cws;
                        getUserDetails(name, bDay, cws);
                        fb->newUser(name, bDay, cws);
                    }
                break;
                case '2':
                    {
                        std::string user2 = readString("To whom do you want to write status? ");
                        std::string user1 = readString("What is your name ? ");
                        fb->addStatus(user1, user2);
                    }
                break;
                case '3':
                    {
                        std::string name = readString("which user wall? ");
                        fb->showWall(name);
                    }
                break;
                case '4':
                    {
                        std::string user2 = readString("which user wall? ");
                        std::string user1 = readString("which user wall? ");
                        fb->connectUsers(user1, user2);
                    }
                    
                break;
                case '5':
                        fb->printAllUsers();
                break;
                case '6':
                    {
                        std::string name = readString("which user friends list ? ");
                        fb->showUsersFriendsList(name);
                    }
                break;
                case '7':
                    {
                        std::string name2 = readString("Who would you want to remove? ");
                        std::string name1 = readString("which page? ");
                        fb->removeFanFromPage(name1, name2);
                    }
                break;
                case '8':
                        delete fb;
                        return 0;
                break;
                default:
                break;
            }
        }
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
    }
    return -1;
}



