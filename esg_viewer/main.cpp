#include "mainwindow.h"
#include <QApplication>
#include "dbmanager\dbmanager.cpp"
#include "dbmanager\Initial_Population.cpp"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qDebug() << "Da";
    DbManager* dbManager = DbManager::getInstance();
    dbManager->addAgencies(Gen_Providers());
    MainWindow w;
    w.show();

    return a.exec();
}
