#include "dbmanager.h"
#include "qdebug.h"
#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>

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

bool DbManager::addCompanies(const QVector<QVector<QString>>& companies)
{
   bool success = false;
   QSqlQuery query;
   QString text = "DELETE FROM COMPANIES; INSERT INTO COMPANIES (name, sector) VALUES ";
   for(const auto& row : companies)
   {
       text += "(";
       for(const auto& elem : row)
       {
           text += elem + ",";
           text.chop(1);
       }
       text += "), ";
   }
   text.chop(2);
   text += ";";
   query.prepare(text);
   if(query.exec())
   {
       success = true;
   }
   else
   {
        qDebug() << "addCompanies error:" << text
                 << query.lastError();
   }
   return success;
}

bool DbManager::addProviders(const QVector<QVector<QString>>& providers)
{
    bool success = false;
    QSqlQuery query;
    QString text = "DELETE FROM PROVIDERS; INSERT INTO PROVIDERS (name) VALUES ";
    for(const auto& row : providers)
    {
        text += "(";
        for(const auto& elem : row)
        {
            text += elem + ",";
            text.chop(1);
        }
        text += "), ";
    }
    text.chop(2);
    text += ";";
    query.prepare(text);
    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addProviders error:" << text
                  << query.lastError();
    }
    return success;
}

bool DbManager::addScores(const QVector<QVector<QString>>& scores)
{
    bool success = false;
    QSqlQuery query;
    QString text = "DELETE FROM SCORES; INSERT INTO SCORES (date, e_score, s_score, g_score, company_id, provider_id) VALUES ";
    for(const auto& row : scores)
    {
        text += "(";
        for(const auto& elem : row)
        {
            text += elem + ",";
            text.chop(1);
        }
        text += "), ";
    }
    text.chop(2);
    text += ";";
    query.prepare(text);
    if(query.exec())
    {
        success = true;
    }
    else
    {
         qDebug() << "addScores error:" << text
                  << query.lastError();
    }
    return success;
}

bool DbManager::addAll(const QVector<QVector<QString>>& companies,
                       const QVector<QVector<QString>>& providers,
                       const QVector<QVector<QString>>& scores)
{
    if(addCompanies(companies))
    {
        if(addProviders(providers))
                return addScores(scores);
    };
    return 0;
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
        s_instance = new DbManager("../data/to-do_db.db");
    }
    return s_instance;
}
