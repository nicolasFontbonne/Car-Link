#ifndef CAMPLOT_H
#define CAMPLOT_H

#include <QWidget>
#include <QImage>
#include "qcustomplot.h"

class camPlot : public QCustomPlot
{
public:
    camPlot(QWidget *parent = 0);
    void update(QVector<double> Linescan);
    void updatePic(unsigned int leftPic, unsigned int rightPic);


public slots:
    void resetRange();
private:
    QVector<double> x;
    QImage image;
};

#endif // CAMPLOT_H
