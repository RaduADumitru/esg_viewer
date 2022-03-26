#include "mainwindow.h"
#include <QApplication>
#include "dbmanager\dbmanager.cpp"
#include "dbmanager\Initial_Population.cpp"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qDebug() << "Da";
    DbManager* dbManager = DbManager::getInstance();
    dbManager->addCompanies(Generate("..\\data\\companies.csv"));
    dbManager->addAgencies(Generate("..\\data\\providers.csv"));
    MainWindow w;
    w.show();

    return a.exec();
}
