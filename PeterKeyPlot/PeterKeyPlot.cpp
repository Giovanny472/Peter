#include "PeterKeyPlot.h"

PeterKeyPlot::PeterKeyPlot(QWidget* AParent): FParent(AParent)
{
  FSeries = new QLineSeries();
  FChart  = new QChart();
  FChartView = new QChartView(FChart);
}

PeterKeyPlot::~PeterKeyPlot()
{
  delete FSeries;
  delete FChart;
  delete FChartView;
}

void PeterKeyPlot::addPoint(int x, int y)
{
  FSeries->append(x,y);
}

void PeterKeyPlot::setTitle(const QString&ATitle)
{
  FChart->setTitle(ATitle);
}

void PeterKeyPlot::Show()
{

  //FChart.setra
  FChart->legend()->hide();
  FChart->addSeries(FSeries);
  FChart->createDefaultAxes();
  FChartView->setRenderHint(QPainter::Antialiasing);
  FChartView->show();
}



