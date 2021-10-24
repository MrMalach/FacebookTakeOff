#include "FB.h"

const char getChoice();

int main()
{
    try
    {
        FB* fb = new(std::nothrow) FB;
        if(nullptr == fb)
            throw(std::invalid_argument("Allocation error"));
    
        while(true)
        {
            switch(getChoice())
            {
                case '1':
                    fb->addNewUser();
                break;
                case '2':
                    fb->addStatus();
                break;
                case '3':
                    fb->showWall();
                break;
                case '4':
                    fb->connectFrieds();
                break;
                case '5':
                    fb->printAllUsers();
                break;
                case '6':
                    fb->showFriendFrieds();
                break;
                case '7':
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
    return 0;
}

const char getChoice()
{
    std::cout << "*********** MENU **************" << std::endl;
    std::cout << "1. Add friend                 *" << std::endl;
    std::cout << "2. Add status                 *" << std::endl;
    std::cout << "3. Show wall                  *" << std::endl;
    std::cout << "4. Connect frieds             *" << std::endl;
    std::cout << "5. Show all users             *" << std::endl;
    std::cout << "6. Show user's friends list   *" << std::endl;
    std::cout << "7. Quit                       *" << std::endl;
    std::cout << "*******************************" << std::endl;

    char choice;
    std::cin >> choice;
    return choice;
}

