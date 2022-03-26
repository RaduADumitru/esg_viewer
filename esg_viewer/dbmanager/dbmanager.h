#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSql>
#include <QSqlDatabase>

class DbManager
{
public:
    bool addCompanies(const QVector<QVector<QString>>& v);
    bool addProviders(const QVector<QVector<QString>>& v);
    bool addScores(const QVector<QVector<QString>>& scores);
    bool addAll(const QVector<QVector<QString>>& companies,
                           const QVector<QVector<QString>>& providers,
                           const QVector<QVector<QString>>& scores);
    bool taskExists(const int id);
    bool deleteTask(const int id);
    QVector<QVector<QString>> getAll();
    static DbManager* getInstance();
private:
    QSqlDatabase m_db;
    static DbManager* s_instance;
    DbManager(const QString& path);
};

#endif // DBMANAGER_H
