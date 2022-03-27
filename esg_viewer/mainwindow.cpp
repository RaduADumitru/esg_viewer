#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager/dbmanager.h"

#include <QChart>
#include <QChartView>
#include <generategraph.h>
#include <QLineSeries>
#include <QLayoutItem>

#include <vector>
#include <utility>

using std::vector;
using std::pair;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    GenerateGraph w(this);
    w.exec();
}

void MainWindow::readyToGenerate(QString companyName, int startYear, int numYears)
{
    int year;
    vector<pair<int, double>> eVals, sVals, gVals;
    qDebug() << companyName << ": ";
    int iter = 0;
    for (year = startYear; numYears-- > 0; year++) {
        // to-do: add functionality for industry specific agency ratings
        eVals.emplace_back(year, DbManager::getInstance()->
                           getCompany(companyName.toStdString()).calculateScore(E_SCORE, year, 0));
        qDebug() << "E: " << eVals[iter].first << " - " << eVals[iter].second;
        sVals.emplace_back(year, DbManager::getInstance()->
                           getCompany(companyName.toStdString()).calculateScore(S_SCORE, year, 0));
        gVals.emplace_back(year, DbManager::getInstance()->
                           getCompany(companyName.toStdString()).calculateScore(G_SCORE, year, 0));
        iter++;
    }

    QLineSeries *eSeries = new QLineSeries();
    for (auto &p : eVals)
        eSeries->append(p.first, p.second);

    QLineSeries *sSeries = new QLineSeries();
    for (auto &p : sVals)
        sSeries->append(p.first, p.second);

    QLineSeries *gSeries = new QLineSeries();
    for (auto &p : gVals)
        gSeries->append(p.first, p.second);

    QLineSeries *esgSeries = new QLineSeries();
    double avgESG = 0;
    for (size_t i = 0; i < eVals.size(); i++) {
        double val = (eVals[i].second+sVals[i].second+gVals[i].second)/3;
        esgSeries->append(eVals[i].first, val);
        avgESG += val;
    }
    avgESG /= eVals.size(); //used for credit label
    std::vector<QString> ratings = {"D", "C", "CC", "CCC+", "B-", "B", "B+",
                                    "BB-", "BB", "BB+", "BBB-", "BBB", "BBB+",
                                   "A-", "A", "A+", "AA-", "AA", "AA+", "AAA"};
    QString ratingText = "Rating: " + ratings[avgESG / 0.05];
    ui->LetterRating->setText(ratingText);

    QLayoutItem *child;
    while ((child = ui->horizontalLayout->takeAt(0)) != 0) {
        delete child;
    }



    QChart *eChart = new QChart();
    QChart *sChart = new QChart();
    QChart *gChart = new QChart();
    QChart *esgChart = new QChart();

    eChart->legend()->hide();
    sChart->legend()->hide();
    gChart->legend()->hide();
    esgChart->legend()->hide();

    eChart->addSeries(eSeries);
    sChart->addSeries(sSeries);
    gChart->addSeries(gSeries);
    esgChart->addSeries(esgSeries);

    eChart->createDefaultAxes();
    sChart->createDefaultAxes();
    gChart->createDefaultAxes();
    esgChart->createDefaultAxes();

    eChart->setTitle("Environmental Evaluation");
    sChart->setTitle("Social Evaluation");
    gChart->setTitle("Governance Evaluation");
    esgChart->setTitle("Overall ESG Score");

    QChartView *eChartView = new QChartView(eChart);
    QChartView *sChartView = new QChartView(sChart);
    QChartView *gChartView = new QChartView(gChart);
    QChartView *esgChartView = new QChartView(esgChart);

    eChartView->setRenderHint(QPainter::Antialiasing);
    sChartView->setRenderHint(QPainter::Antialiasing);
    gChartView->setRenderHint(QPainter::Antialiasing);
    esgChartView->setRenderHint(QPainter::Antialiasing);

    ui->horizontalLayout->addWidget(eChartView, 1);
    ui->horizontalLayout->addWidget(sChartView, 1);
    ui->horizontalLayout->addWidget(gChartView, 1);
    ui->horizontalLayout->addWidget(esgChartView, 1);
//    ui->layoutESG->addWidget(esgChartView, 1);
}
