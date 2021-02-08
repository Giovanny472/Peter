#ifndef KEYCUTTERCHARTBOX_H
#define KEYCUTTERCHARTBOX_H
#include <gui/KeyCutterAbstractDialog.h>
#include <QList>
#include <coord/CNC2DPointVector.h>
#include <coord/CNC3DPointVector.h>
#include <QtCharts>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
class QLineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

class KeyCutterChartBox : public KeyCutterAbstractDialog
{
    Q_OBJECT

public:
    KeyCutterChartBox(ButtonFlags buttons=NoButton);
    ~KeyCutterChartBox();

    void clearPoints();
    void appendPoint(const CNC2DPoint& point);
    void appendPoints(const CNC2DPointVector& points);
    void appendPoints(const CNC3DPointVector& points,
                      CNC3DPoint::Plane2D plane);
    void setPoints(const CNC2DPointVector& points);
    void setPoints(const CNC3DPointVector& points,
                   CNC3DPoint::Plane2D plane);

    virtual QWidget* toolWidget();

protected:
    void setXAxisMax(double max);
    void setYAxisMax(double max);
    void setXAxisMin(double min);
    void setYAxisMin(double min);

private:
    QChartView* m_chartView;
    QChart* m_chart;
    QValueAxis* m_xAxis;
    QValueAxis* m_yAxis;
    QLineSeries* m_pointSeries;

    void resetTicks();

private slots:
    void onSeriesClicked(const QPointF &point);
};

#endif // KEYCUTTERCHARTBOX_H
