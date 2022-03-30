#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager/dbmanager.h"

#include <QChart>
#include <QChartView>
#include <generategraph.h>
#include <QLineSeries>
#include <QLayoutItem>
#include <QValueAxis>

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

//    eChart->createDefaultAxes();
//    sChart->createDefaultAxes();
//    gChart->createDefaultAxes();
//    esgChart->createDefaultAxes();

    QValueAxis *eXAxis = new QValueAxis();
    eXAxis -> setRange(startYear, startYear + numYears);
    eXAxis -> setTickCount(numYears);
    eXAxis -> setLabelFormat("%d");
    QValueAxis *eYAxis = new QValueAxis();
    eYAxis -> setLabelFormat("%.2f");
    eChart->setAxisX(eXAxis, eSeries);
    eChart->setAxisY(eYAxis, eSeries);

    QValueAxis *sXAxis = new QValueAxis();
    sXAxis -> setRange(startYear, startYear + numYears);
    sXAxis -> setTickCount(numYears);
    sXAxis -> setLabelFormat("%d");
    QValueAxis *sYAxis = new QValueAxis();
    sYAxis -> setLabelFormat("%.2f");
    sChart->setAxisX(sXAxis, sSeries);
    sChart->setAxisY(sYAxis, sSeries);

    QValueAxis *gXAxis = new QValueAxis();
    gXAxis -> setRange(startYear, startYear + numYears);
    gXAxis -> setTickCount(numYears);
    gXAxis -> setLabelFormat("%d");
    QValueAxis *gYAxis = new QValueAxis();
    gYAxis -> setLabelFormat("%.2f");
    gChart->setAxisX(gXAxis, gSeries);
    gChart->setAxisY(gYAxis, gSeries);

    QValueAxis *esgXAxis = new QValueAxis();
    esgXAxis -> setRange(startYear, startYear + numYears);
    esgXAxis -> setTickCount(numYears);
    esgXAxis -> setLabelFormat("%d");
    QValueAxis *esgYAxis = new QValueAxis();
    esgYAxis -> setLabelFormat("%.2f");
    esgChart->setAxisX(esgXAxis, esgSeries);
    esgChart->setAxisY(esgYAxis, esgSeries);


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
