#ifndef UTILS_H
#define UTILS_H

#include "Person.h"
#include "User.h"


char getChoice();
int to_int(std::string);
bool getBoolChoice(std::string);
std::string readString(std::string);
std::string readStatus();
bool getUserDetails(std::string&, std::string&, bool&);

#endif // UTILS_H