#ifndef COMPANY_H
#define COMPANY_H
#include "types.h"
#include <string>

using std::string;

class Company
{
    string company_name;
    string sector;
public:
    Company(string name, string sector) : company_name(name), sector(sector) {};
    string getName() { return company_name; }
    double calculateScore(ScoreType type, year_t year, bool industry_specific);
};

#endif // COMPANY_H
