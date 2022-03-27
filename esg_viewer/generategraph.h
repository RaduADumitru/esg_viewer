#ifndef GENERATEGRAPH_H
#define GENERATEGRAPH_H

#include <QDialog>

namespace Ui {
class GenerateGraph;
}

class GenerateGraph : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateGraph(QWidget *parent = nullptr);
    ~GenerateGraph();

private slots:
    void on_doneButton_clicked();

signals:
    void readyToGenerate(QString, int, int);

private:
    Ui::GenerateGraph *ui;
};

#endif // GENERATEGRAPH_H
