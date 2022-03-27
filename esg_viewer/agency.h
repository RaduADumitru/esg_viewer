#ifndef AGENCY_H
#define AGENCY_H

#include "types.h"
#include <string>

using std::string;

class Agency
{
private:
    string name;
    bool sectorSpecific;
    int num_e_KPI;
    int num_s_KPI;
    int num_g_KPI;
public:
    Agency() {};
    Agency(string name, bool sectorSpecific,
           int num_e_KPI, int num_s_KPI, int num_g_KPI) :
            name(name), sectorSpecific(sectorSpecific),
            num_e_KPI(num_e_KPI), num_s_KPI(num_s_KPI), num_g_KPI(num_g_KPI) {};
    double getWeight(ScoreType type);
    bool isIndustrySpecific() { return sectorSpecific; }
};

#endif // AGENCY_H
