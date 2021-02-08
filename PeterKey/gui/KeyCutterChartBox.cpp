#include "KeyCutterChartBox.h"
#include <QChartView>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
QT_CHARTS_USE_NAMESPACE

KeyCutterChartBox::KeyCutterChartBox(ButtonFlags buttons)
    :KeyCutterAbstractDialog(buttons)
{
    m_chart = new QChart();
    m_chart->legend()->hide();
    m_pointSeries = new QLineSeries(m_chart);
    m_chart->addSeries(m_pointSeries);
    connect(m_pointSeries, &QLineSeries::clicked,
            this, &KeyCutterChartBox::onSeriesClicked);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    m_xAxis = new QValueAxis();
    m_yAxis = new QValueAxis();
    m_xAxis->setRange(0, 1);
    m_yAxis->setRange(0, 1);

    m_chart->addAxis(m_xAxis, Qt::AlignBottom);
    m_chart->addAxis(m_yAxis, Qt::AlignLeft);

    m_pointSeries->attachAxis(m_xAxis);
    m_pointSeries->attachAxis(m_yAxis);

    m_xAxis->setMinorTickCount(5);
    m_yAxis->setMinorTickCount(5);
}

KeyCutterChartBox::~KeyCutterChartBox()
{
    delete m_chartView;
}

QWidget* KeyCutterChartBox::toolWidget()
{
    return m_chartView;
}

void KeyCutterChartBox::clearPoints()
{
    m_pointSeries->clear();
}

void KeyCutterChartBox::appendPoint(const CNC2DPoint& point)
{
    m_pointSeries->append(point.x(), point.y());
    if(point.x()>m_xAxis->max())
        setXAxisMax(qRound(point.x())+1);
    if(point.x()<m_xAxis->min())
        setXAxisMin(qRound(point.x())-1);
    if(point.y()>m_yAxis->max())
        setYAxisMax(qRound(point.y())+1);
    if(point.y()<m_yAxis->min())
        setYAxisMin(qRound(point.y())-1);
}

void KeyCutterChartBox::appendPoints(const CNC2DPointVector& points)
{
    foreach(CNC2DPoint point, points)
        appendPoint(point);
}

void KeyCutterChartBox::appendPoints(const CNC3DPointVector& points,
                                     CNC3DPoint::Plane2D plane)
{
    foreach(CNC3DPoint point, points)
        appendPoint(point.to2DPoint(plane));
}

void KeyCutterChartBox::setPoints(const CNC2DPointVector& points)
{
    clearPoints();
    appendPoints(points);
}

void KeyCutterChartBox::setPoints(const CNC3DPointVector& points,
                                  CNC3DPoint::Plane2D plane)
{
    clearPoints();
    appendPoints(points, plane);
}

void KeyCutterChartBox::setXAxisMax(double max)
{
    m_xAxis->setMax(max);
    resetTicks();
}

void KeyCutterChartBox::setYAxisMax(double max)
{
    m_yAxis->setMax(max);
    resetTicks();
}

void KeyCutterChartBox::setXAxisMin(double min)
{
    m_xAxis->setMin(min);
    resetTicks();
}

void KeyCutterChartBox::setYAxisMin(double min)
{
    m_yAxis->setMin(min);
    resetTicks();
}

void KeyCutterChartBox::resetTicks()
{
    //TODO: не очень красиво
    quint32 xTicks = m_xAxis->max()-m_xAxis->min();
    if(xTicks%2) xTicks++;
    m_xAxis->setTickCount(xTicks/2+1);
    m_yAxis->setTickCount(m_yAxis->max()-m_yAxis->min()+1);
}

void KeyCutterChartBox::onSeriesClicked(const QPointF &point)
{
    qDebug("%f, %f", point.x(), point.y());
}
