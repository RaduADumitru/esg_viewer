#include <QString>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>

bool safeSQLexec(std::string queryText)
{
    bool success;
    QSqlQuery query;
    if(query.exec(QString::fromStdString(queryText)))
    {
        success = true;
    }
    else
    {
         qDebug() << "addCompanies error:" << QString::fromStdString(queryText)
                  << query.lastError();
         success = false;
    }
    return success;
}
