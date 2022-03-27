#include "mainwindow.h"
#include <QApplication>
#include "dbmanager\dbmanager.cpp"
#include "dbmanager\Initial_Population.cpp"
#include "company.h"
#include "agency.h"
#include "rating.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    qDebug() << "Da";
    DbManager* dbManager = DbManager::getInstance();
    QVector<QVector<std::string>> companies = Generate("..\\data\\companies.csv");
    QVector<QVector<std::string>> providers = Generate("..\\data\\providers.csv");
    QVector<QVector<std::string>> scores = Generate("..\\data\\scores.csv");
    dbManager->addAll(companies, providers, scores);

    MainWindow w;
    w.show();
    Company comp = DbManager::getInstance()->getCompany("Lukoil");
        qDebug() << QString::fromStdString(comp.getName());
        qDebug() << comp.calculateScore(E_SCORE, 2018, false);
    return a.exec();
}
