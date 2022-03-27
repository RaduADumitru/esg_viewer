#ifndef RATING_H
#define RATING_H

#include <string>
#include "types.h"

using std::string;

class Rating
{
private:
    string companyName;
    string agencyName;
    year_t year;
    double e_score;
    double s_score;
    double g_score;
public:
    Rating(string companyName, string agencyName, year_t year,
           double e_score, double s_score, double g_score) :
            companyName(companyName), agencyName(agencyName),
            year(year), e_score(e_score), s_score(s_score), g_score(g_score) {};

    string getCompanyName() { return companyName; }
    string getAgencyName() { return agencyName; }
    year_t getYear() { return year; }
    double getScore(ScoreType type) {
        if (type == E_SCORE)
            return e_score;
        if (type == S_SCORE)
            return s_score;
        if (type == G_SCORE)
            return g_score;
        return -1;
    }
};

#endif // RATING_H
