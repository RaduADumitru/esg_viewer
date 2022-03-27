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

private:
    Ui::GenerateGraph *ui;
};

#endif // GENERATEGRAPH_H
