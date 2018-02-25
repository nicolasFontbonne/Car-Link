#include "camplot.h"

camPlot::camPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    QVector<double> Linescan(128);
    x.resize(128);

    for (int i=0; i<128; i++)
    {
      x[i] = i;
      Linescan[i] = 1000 + 100*sin(100*i);
    }

    setMinimumSize(512, 128);
    addGraph();
    graph(0)->setPen(QPen(Qt::blue));
    graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
    graph(0)->setData(x, Linescan);

    xAxis->setRange(0, 127);
    yAxis->setRange(0, 4095);
    xAxis2->setVisible(true);
    yAxis2->setVisible(true);
    xAxis2->setTickLabels(false);
    yAxis2->setTickLabels(false);
    xAxis2->setRange(0, 127);
    yAxis2->setRange(0, 4095);
    connect(xAxis, SIGNAL(rangeChanged(QCPRange)), xAxis2, SLOT(setRange(QCPRange)));
    connect(yAxis, SIGNAL(rangeChanged(QCPRange)), yAxis2, SLOT(setRange(QCPRange)));
    connect(this, &QCustomPlot::mouseDoubleClick, this, &camPlot::resetRange);
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void camPlot::update(QVector<double> Linescan)
{
    graph(0)->setData(x, Linescan);
    replot();
}

void camPlot::resetRange()
{
    xAxis2->setRange(0, 127);
    yAxis2->setRange(0, 4095);
    xAxis->setRange(0, 127);
    yAxis->setRange(0, 4095);
    replot();
}
