#include "agency.h"
#include "dbmanager\\dbmanager.h"

double Agency::getWeight(ScoreType type)
{
    int totalKPI = DbManager::getInstance()->getTotalKPI();
    if (type == E_SCORE)
        return ((double)num_e_KPI)/totalKPI;
    if (type == S_SCORE)
        return ((double)num_s_KPI)/totalKPI;
    if (type == G_SCORE)
        return ((double)num_g_KPI)/totalKPI;

    return -1;
}
