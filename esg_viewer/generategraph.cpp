#include "generategraph.h"
#include "ui_generategraph.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

GenerateGraph::GenerateGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateGraph)
{
    ui->setupUi(this);
    // 1. query care ia toate numele de companii din baza de date
    QSqlQuery graphQuery;
    std::string graphQueryText = "select company_name from COMPANIES;";
    graphQuery.exec(QString::fromStdString(graphQueryText));
    if(!graphQuery.exec(QString::fromStdString(graphQueryText)))
    {
         qDebug() << "generateGraph error:" << QString::fromStdString(graphQueryText)
                  << graphQuery.lastError();
    }
    // 2. pentru fiecare nume "name"
    while(graphQuery.next())
    {
        QString companyName = graphQuery.record().value(0).toString();
        qDebug() << companyName;
            ui->companyNames->addItem(companyName);
    }
}

GenerateGraph::~GenerateGraph()
{
    delete ui;
}
