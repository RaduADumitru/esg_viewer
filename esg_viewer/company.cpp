#include "company.h"
#include "dbmanager\\dbmanager.h"
#include "rating.h"
#include "agency.h"

#include <vector>
#include <map>

using std::vector;
using std::map;


/* OBS: suppose that none of the companies are sector specific */
double Company::calculateScore(ScoreType type, year_t year, bool industry_specific) {
    double weightSum = 0;
    double sum = 0;

    vector<Rating> ratings = DbManager::getInstance()->getRatings();
    map<std::string, Agency> agencies = DbManager::getInstance()->getAgencies();

    for (auto& rating : ratings) {
        if (rating.getCompanyName() != company_name)
            continue;
        if (rating.getYear() != year)
            continue;

        Agency& agency = agencies[rating.getAgencyName()];
        if (agency.isIndustrySpecific() != industry_specific)
            continue;

        double agWeight = agency.getWeight(type);
        weightSum += agWeight;

        double score = rating.getScore(type);
        sum += agWeight*score;
    }

    return sum / weightSum;
}
