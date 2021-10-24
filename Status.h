#ifndef STATUS_H
#define STATUS_H


#include<vector>
#include<iostream>
#include<ctime>
#include<chrono>
#include<string>

class Status
{
    std::time_t _time1;
    std::string _status;

public:
    Status(const std::string&);
    ~Status();

    friend std::ostream& operator<<(std::ostream&, const Status&);
    friend const bool operator!=(const Status&, const Status&);
    friend const bool operator==(const Status&, const Status&);
};

#endif //STATUS_H