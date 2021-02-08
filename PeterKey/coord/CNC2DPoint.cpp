#include "CNC2DPoint.h"
#include <QString>
#include <QStringList>
#include <QtMath>

CNC2DPoint::CNC2DPoint()
{
    initZeroes();
}

CNC2DPoint::CNC2DPoint(double xCoordinate,
                       double yCoordinate)
{
    initZeroes();
    setPoint(xCoordinate, yCoordinate);
}

CNC2DPoint::CNC2DPoint(const CNC2DPoint& copyFrom)
{
    initZeroes();
    *this = copyFrom;
}

CNC2DPoint::~CNC2DPoint()
{

}

CNC2DPoint::CNC2DPoint(const QString& str)
{
    QStringList strl = str.split(';');
    if(strl.count()<3)
    {
        m_nullPoint = true;
        return;
    }

    bool ok;
    setX(strl[0].toDouble(&ok));
    if(!ok)
    {
        m_nullPoint = true;
        return;
    }
    setY(strl[1].toDouble(&ok));
    if(!ok)
    {
        m_nullPoint = true;
        return;
    }
    m_nullPoint = false;
}

QString CNC2DPoint::toString() const
{
    return QString().asprintf("%.03f;%.03f", m_x, m_y);
}

CNC2DPoint& CNC2DPoint::rotate(double angleRadian,
                               const CNC2DPoint& center)
{
    if(isNull())
        return *this;

    CNC2DPoint outPoint(*this);
    outPoint-=center;

    double angle;
    if(outPoint.x())
        angle = qAtan2(outPoint.y(), outPoint.x());
    else
    {
        if(outPoint.y()>=0)
            angle = qDegreesToRadians(90.0);
        else
            angle = qDegreesToRadians(270.0);
    }
    angle+=angleRadian;
    double length = qSqrt(outPoint.x()*outPoint.x()+
                          outPoint.y()*outPoint.y());
    outPoint.setX(length*qCos(angle));
    outPoint.setY(length*qSin(angle));

    *this=(outPoint+=center);
    return *this;
}

CNC2DPoint& CNC2DPoint::setX(double xCoordinate)
{
    m_x = xCoordinate;
    m_nullPoint = false;
    return *this;
}

double CNC2DPoint::x() const
{
    return m_x;
}

CNC2DPoint& CNC2DPoint::setY(double yCoordinate)
{
    m_y = yCoordinate;
    m_nullPoint = false;
    return *this;
}

double CNC2DPoint::y() const
{
    return m_y;
}

bool CNC2DPoint::isNull() const
{
    return m_nullPoint;
}

CNC2DPoint& CNC2DPoint::setPoint(double xCoordinate,
                          double yCoordinate)
{
    setX(xCoordinate);
    setY(yCoordinate);
    return *this;
}

CNC2DPoint& CNC2DPoint::operator=(const CNC2DPoint& assignFrom)
{
    setPoint(assignFrom.x(), assignFrom.y());
    m_nullPoint = assignFrom.isNull();
    return *this;
}

void CNC2DPoint::initZeroes()
{
    m_x = 0;
    m_y = 0;
    m_nullPoint = true;
}

CNC2DPoint CNC2DPoint::operator+(const CNC2DPoint& plus) const
{
    CNC2DPoint point(
                x()+plus.x(),
                y()+plus.y());
    return point;
}

CNC2DPoint CNC2DPoint::operator-(const CNC2DPoint& minus) const
{
    CNC2DPoint point(
                x()-minus.x(),
                y()-minus.y());
    return point;
}

CNC2DPoint& CNC2DPoint::operator+=(const CNC2DPoint& diff)
{
    setX(x()+diff.x());
    setY(y()+diff.y());
    return *this;
}

CNC2DPoint& CNC2DPoint::operator-=(const CNC2DPoint& diff)
{
    setX(x()-diff.x());
    setY(y()-diff.y());
    return *this;
}

CNC2DPoint CNC2DPoint::operator*(const CNC2DPoint& diff) const
{
    return CNC2DPoint(x()*diff.x(), y()*diff.y());
}

CNC2DPoint& CNC2DPoint::operator*=(const CNC2DPoint& diff)
{
    setX(x()*diff.x());
    setY(y()*diff.y());
    return *this;
}

CNC2DPoint& CNC2DPoint::invertPointCoordinates()
{
    *this*=CNC2DPoint(-1,-1);
    return *this;
}
