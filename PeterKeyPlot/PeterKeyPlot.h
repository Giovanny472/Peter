#ifndef PETERKEYPLOT_H
#define PETERKEYPLOT_H

#include <QWidget>
#include <QtCharts>

class PeterKeyPlot
{
  private:
    QWidget *FParent;
    QLineSeries *FSeries;
    QChartView *FChartView;
    QChart *FChart;
    QValueAxis* FAxis_X;
    QValueAxis* FAxis_Y;
  public:
    // добавление точки
    void addPoint(int x, int y);
    // заголовок
    void setTitle(const QString& ATitle);
    //
    void Show();
  public:
    //конструктор
    PeterKeyPlot(QWidget* AParent = nullptr);
    //денструктор
    ~PeterKeyPlot();
};

#endif // PETERKEYPLOT_H
