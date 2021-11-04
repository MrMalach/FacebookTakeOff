#include "Status.h"


Status::Status(const std::string& status)
    :   _status(status)
    {
        _time1 = std::time(nullptr);
    }

Status::~Status(){std::cout << "in status d'tor\n";}

std::ostream& operator<<(std::ostream& o, const Status& status)
{
    o << "Date : " << std::asctime(std::localtime(&status._time1))
        << std::endl << status._status;
        return o;
}

bool operator!=(const Status& lhs, const Status& rhs)
{
    return lhs._status != rhs._status;
}

bool operator==(const Status& lhs, const Status& rhs)
{
    return lhs._status == rhs._status;
}