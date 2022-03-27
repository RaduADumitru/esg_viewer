#include "dbmanager.h"
#include "qdebug.h"
#include "..//..//utils//safeSQLexec.cpp"
#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlField>
#include <fstream>
#include <sstream>

DbManager *DbManager::s_instance = 0;

DbManager::DbManager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

bool DbManager::addCompanies(QVector<QVector<std::string>>& companies)
{
    bool success = false;
    QSqlQuery query;
    if(query.exec(QString::fromStdString("DELETE FROM COMPANIES;")))
    {
        success = true;
    }
    else
    {
         qDebug() << "addCompanies error:" << QString::fromStdString("DELETE FROM COMPANIES;")
                  << query.lastError();
         return false;
    }
    std::string text = "INSERT INTO COMPANIES (company_name, sector) VALUES ";
    companies.erase(companies.begin());
    for(const auto& row : companies)
    {
        text += "('";
        for(const auto& elem : row)
        {
            text = (text + elem + "', '");
        }

        text.pop_back();
        text.pop_back();
        text.pop_back();
        text += "), ";
    }
    text.pop_back();
    text.pop_back();
    text += ";";
    return success && safeSQLexec(text);
}

bool DbManager::addAgencies(QVector<QVector<std::string>>& agencies)
{
    bool success = false;
    QSqlQuery query;
    if(query.exec(QString::fromStdString("DELETE FROM RATING_AGENCIES;")))
    {
        success = true;
    }
    else
    {
         qDebug() << "addProviders error:" << QString::fromStdString("DELETE FROM RATING_AGENCIES;")
                  << query.lastError();
         return false;
    }
    std::string text = "INSERT INTO RATING_AGENCIES (agency_name, sector_specific) VALUES ";
    agencies.erase(agencies.begin());
    for(const auto& row : agencies)
    {
        text += "('";
        for(const auto& elem : row)
        {
            text = (text + elem + "', '");
        }
        text.pop_back();
        text.pop_back();
        text.pop_back();
        text += "), ";
    }
    text.pop_back();
    text.pop_back();
    text += ";";
    qDebug() << QString::fromStdString(text);
    success = success && safeSQLexec(text);
    //Now adds KPIs for each agency
    std::string kpi_filepath = "";
    std::string line, word, kpi_name, kpi_category;

    for(auto& row : agencies)
    {
        std::string agency_name = row[0];
        kpi_filepath = "..//data//kpis//" + agency_name + "_kpi.csv";
        std::fstream file (kpi_filepath);
        if(!file.is_open()) throw std::runtime_error("Could not open file: " + kpi_filepath);
        getline(file, line);
        while(getline(file, line))
        {
            std::stringstream str(line);
            getline(str, word, ',');
                kpi_name = word;
                // Adds KPI if it doesn't exist
                std::string kpi_check_text = "select ifnull((select count(1) from KPI where kpi_name like '" + word + "' limit 1), 0);";
                 qDebug() << QString::fromStdString(kpi_check_text) << " ";
                QSqlQuery query;
                if(query.exec(QString::fromStdString(kpi_check_text)))
                {
                    success = true;
                }
                else
                {
                     qDebug() << "kpi error:" << QString::fromStdString(kpi_check_text)
                              << query.lastError();
                     success = false;
                }
                query.next();
                int returnedValue = query.record().value(0).toInt(); //0 if kpi not found, 1 if it is
                if(returnedValue == 0)
                {
                    getline(str, word, '\r');
                    kpi_category = word;
                    std::string kpi_insert_text = "insert into KPI (kpi_name, category) values ('" + kpi_name + "', lower('" + kpi_category + "'));";
                    // qDebug() << QString::fromStdString(kpi_insert_text);
                    if(query.exec(QString::fromStdString(kpi_insert_text)))
                    {
                        success = true;
                    }
                    else
                    {
                         qDebug() << "kpi error:" << QString::fromStdString(kpi_insert_text)
                                  << query.lastError();
                         success = false;
                    }
                }
                //create INCLUDES entry
                //a)check if it already exists
                std::string includes_check_text = "select ifnull((select count(1) "
                                                  "from INCLUDES "
                                                  "where kpi_name like '" + kpi_name +
                        "' and agency_name like '" + agency_name + "' limit 1), 0);";
                QSqlQuery query2;
                if(query2.exec(QString::fromStdString(kpi_check_text)))
                {
                    success = true;
                }
                else
                {
                     qDebug() << "kpi error:" << QString::fromStdString(kpi_check_text)
                              << query.lastError();
                     success = false;
                }
                query.next();
                int includesFound = query2.record().value(0).toInt(); //0 if entry not found, 1 if it is
                if(includesFound == 0)
                {
                    std::string includes_insert_text = "insert into INCLUDES (agency_name, kpi_name) values ('" + agency_name + "', '" + kpi_name + "');";
                             qDebug() << QString::fromStdString(includes_insert_text);
                    QSqlQuery query3;
                    if(query3.exec(QString::fromStdString(includes_insert_text)))
                    {
                        success = true;
                    }
                    else
                    {
                         qDebug() << "includes error:" << QString::fromStdString(includes_insert_text)
                                  << query3.lastError();
                         success = false;
                    }
                }
                 //qDebug() << query.record().value(0).toInt();
        }
        // qDebug() << QString::fromStdString(kpi_filepath) << '\n';
    }
}

bool DbManager::addScores(QVector<QVector<std::string>>& scores)
{
    bool success = false;
    QSqlQuery query;
    if(query.exec(QString::fromStdString("DELETE FROM SCORES;")))
    {
        success = true;
    }
    else
    {
         qDebug() << "addScores error:" << QString::fromStdString("DELETE FROM COMPANIES;")
                  << query.lastError();
         return false;
    }
    std::string text = "INSERT INTO SCORES (year, company_name, agency_name, e_score, s_score, g_score) VALUES ";
    scores.erase(scores.begin());
    for(const auto& row : scores)
    {
        text += "('";
        for(const auto& elem : row)
        {
            text = (text + elem + "', '");
        }

        text.pop_back();
        text.pop_back();
        text.pop_back();
        text += "), ";
    }
    text.pop_back();
    text.pop_back();
    text += ";";
    qDebug() << QString::fromStdString(text);
    return success && safeSQLexec(text);
}
bool DbManager::addAll(QVector<QVector<std::string>>& companies,
                       QVector<QVector<std::string>>& providers,
                       QVector<QVector<std::string>>& scores)
{
    addCompanies(companies);
    addAgencies(providers);
    addScores(scores);
}
bool DbManager::taskExists(const int id){
    QSqlQuery query;
    query.prepare("SELECT * FROM Tasks WHERE id = (:id)");
    query.bindValue(":id", id);

    if (query.exec())
    {
       if (query.next())
       {
          //it exists
           return 1;
       }
    }
    return 0;
}
QVector<QVector<QString>> DbManager::getAll() {
    QSqlQuery query("SELECT id, name, description, isDone FROM Tasks");
    QVector<QVector<QString>> v;
    int row = 0;
    while (query.next())
    {
        v.push_back(QVector<QString>(4));
       for(int col = 0; col < 4; col++){
           v[row][col] = query.value(col).toString();
       }
       row++;
    }
    return v;
}
bool DbManager::deleteTask(const int id){
    bool success = false;
    if (taskExists(id))
    {
       QSqlQuery query;
       query.prepare("DELETE FROM Tasks WHERE id = (:id)");
       query.bindValue(":id", id);
       success = query.exec();

       if(!success)
       {
           qDebug() << "removeTask error:"
                    << query.lastError();
       }
    }

    return success;
}

DbManager* DbManager::getInstance() {
    if (!s_instance) {
        s_instance = new DbManager("..\\data\\esg_db.db");
    }
    return s_instance;
}
