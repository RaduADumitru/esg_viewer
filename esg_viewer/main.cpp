#include "mainwindow.h"
#include <QApplication>
#include "dbmanager\dbmanager.cpp"
#include "dbmanager\Initial_Population.cpp"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qDebug() << "Da";
    DbManager* dbManager = DbManager::getInstance();
    QVector<QVector<std::string>> companies = Generate("..\\data\\companies.csv");
    dbManager->addCompanies(companies);
    QVector<QVector<std::string>> providers = Generate("..\\data\\providers.csv");
    dbManager->addAgencies(providers);
    QVector<QVector<std::string>> scores = Generate("..\\data\\scores.csv");
    dbManager->addScores(scores);

    MainWindow w;
    w.show();

    return a.exec();
}
