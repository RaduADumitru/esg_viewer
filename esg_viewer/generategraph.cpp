#include "generategraph.h"
#include "mainwindow.h"
#include "ui_generategraph.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QString>

GenerateGraph::GenerateGraph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateGraph)
{
    ui->setupUi(this);

    MainWindow *mw = qobject_cast<MainWindow *>(parent);
    connect(this, &GenerateGraph::readyToGenerate,
            mw, &MainWindow::readyToGenerate);

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
    ui->startYear->setMinimum(2000);
    ui->startYear->setMaximum(2020);
    ui->numYears->setMinimum(2);
    ui->numYears->setMaximum(30);
}

GenerateGraph::~GenerateGraph()
{
    delete ui;
}

void GenerateGraph::on_doneButton_clicked()
{
    QString company_name = ui->companyNames->currentText();
    qDebug() << "Company name: " << company_name;
    int startYear = ui->startYear->value();
    int numYears = ui->numYears->value();
    numYears = std::min(2020 - startYear + 1, numYears);

    emit readyToGenerate(company_name, startYear, numYears);
}

