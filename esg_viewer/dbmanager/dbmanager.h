#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSql>
#include <QSqlDatabase>
#include <map>
#include <vector>
#include "agency.h"
#include "rating.h"
#include "company.h"
class DbManager
{
public:
    bool addCompanies(QVector<QVector<std::string>>& v);
    bool addAgencies(QVector<QVector<std::string>>& v);
    bool addScores(QVector<QVector<std::string> > &scores);
    bool addAll(QVector<QVector<std::string>>& companies,
                           QVector<QVector<std::string>>& agencies,
                           QVector<QVector<std::string>>& scores);
    bool taskExists(const int id);
    bool deleteTask(const int id);
    QVector<QVector<QString>> getAll();
    static DbManager* getInstance();
    /* ------------ Fetch data from database ----------------*/
    std::map<std::string, Agency> getAgencies();
    std::vector<Rating> getRatings();
    Company getCompany(const std::string& name);
//    int getSectorKPI();
    int getTotalKPI();
    /* ------------------------------------------------------*/
private:
    QSqlDatabase m_db;
    static DbManager* s_instance;
    DbManager(const QString& path);
};

#endif // DBMANAGER_H
