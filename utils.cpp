#include "utils.h"

char getChoice()
{
    std::cout << "***************** MENU ***********************" << std::endl;
    std::cout << "1. Add friend                                *" << std::endl;
    std::cout << "2. Add status                                *" << std::endl;
    std::cout << "3. Show wall                                 *" << std::endl;
    std::cout << "4. Connect frieds                            *" << std::endl;
    std::cout << "5. Show all users                            *" << std::endl;
    std::cout << "6. Show user's friends list                  *" << std::endl;
    std::cout << "7. Remove friend from page's friends list    *" << std::endl;
    std::cout << "8. Quit                                      *" << std::endl;
    std::cout << "**********************************************" << std::endl;

    char choice;
    std::cin >> choice;
    return choice;
}

int to_int(std::string s)
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

bool getBoolChoice(std::string msg)
{
    char b = '9';
    while(b != '1' && b != '2' && b != 'y' && b != 'n')
    {
        std::cout << msg << std::endl;
        std::cin >> b;
    }
    return (b == '1' || b == 'y') ? true : false;
}

std::string readString(std::string msg)
{
    std::cout << msg << std::endl;
    std::string s;
    std::cin >> s;
    return s;
}

std::string readStatus()
{
    std::cout << "Enter status: " << std::endl;
    std::string status;
    std::cin.ignore(); 
    std::getline(std::cin, status);
    return status;
}

bool isleapyear(unsigned short year){
	return ( ! (year %4) && (year %100) || !(year %400));
}

//1 valid, 0 invalid
bool valid_date(unsigned short year,unsigned short month,unsigned short day){
	unsigned short monthlen[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if (!year || !month || !day || month >12)
		return 0;
	if ( isleapyear(year) && month==2)
		monthlen[1]++;
	if (day > monthlen[month-1])
		return 0;
	return 1;
}

bool getUserDetails(std::string& name, std::string& bDay, bool& cws)
{
    /*  Get valid values for User type,
        If for User (page) or for Person.
        Construct one of the two and run 
        FB::addUser(...)                */
    try
    {
        bool isPerson = getBoolChoice("1. Person\n2. Page\n");

        name = readString("Enter name: ");
        
        if(isPerson)
        {
            std::cout << "Enter date of birth:" << std::endl;
            std::string db;

            db = readString("Day:");
            int d = to_int(db);
            db = readString("Month:");
            int m = to_int(db);
            db = readString("Year:");
            int y = to_int(db);


            if( ! valid_date(y, m, d) )
                 throw(std::invalid_argument("Bad input"));
             
            /* Check that the age is not greather 
                than 120 or not born yet.       */
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            time_t tt = std::chrono::system_clock::to_time_t(now);
            tm local_tm = *localtime(&tt);
            if(y < local_tm.tm_year + 1900 - 120 || y > local_tm.tm_year + 1900)
                throw(std::invalid_argument("Bad input"));
            bDay = std::to_string(d) + '/' + std::to_string(m) + '/' + std::to_string(y);

            cws = getBoolChoice("Can frieds write status? (y, n)");
        }
        return true;
    }
    catch(std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}


