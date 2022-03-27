#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChart>
#include <QChartView>
#include <QLineSeries>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLineSeries *series = new QLineSeries();
        series->append(0, 6);
        series->append(2, 4);
        series->append(3, 8);
        series->append(7, 4);
        series->append(10, 5);

        // *series << QPointF(11, 1)
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Simple line chart ex");

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        ui->layoutE->addWidget(chartView, 1);


    // pentru fiecare dintre graficele E S si G

}

MainWindow::~MainWindow()
{
    delete ui;
}

