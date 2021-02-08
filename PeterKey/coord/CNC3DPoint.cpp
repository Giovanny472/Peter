#include "CNC3DPoint.h"
#include <QString>
#include <QStringList>
#include <QtMath>

CNC3DPoint::CNC3DPoint()
{
    initZeroes();
}

CNC3DPoint::CNC3DPoint(double xCoordinate,
                       double yCoordinate,
                       double zCoordinate)
{
    initZeroes();
    setPoint(xCoordinate, yCoordinate, zCoordinate);
}

CNC3DPoint::CNC3DPoint(const CNC3DPoint& copyFrom)
{
    initZeroes();
    *this = copyFrom;
}

CNC3DPoint::~CNC3DPoint()
{

}

CNC3DPoint::CNC3DPoint(const QString& str)
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
    setZ(strl[2].toDouble(&ok));
    if(!ok)
    {
        m_nullPoint = true;
        return;
    }
    m_nullPoint = false;
}

CNC3DPoint::CNC3DPoint(const CNC2DPoint& point,
                       Plane2D plane)
{
    initZeroes();
    set2DPoint(point, plane);
}

QString CNC3DPoint::toString() const
{
    return QString().asprintf("%.03f;%.03f;%.03f",
                             m_x, m_y, m_z);
}

CNC3DPoint& CNC3DPoint::rotate(double angleRadian,
                               Plane2D plane,
                               const CNC2DPoint &center
                               )
{
    CNC2DPoint outPoint = to2DPoint(plane);
    outPoint.rotate(angleRadian, center);
    set2DPoint(outPoint, plane);
    return *this;
}

CNC3DPoint& CNC3DPoint::set2DPoint(const CNC2DPoint& point,
                                   Plane2D plane)
{
    switch(plane)
    {
    case XY:
    {
        setX(point.x());
        setY(point.y());
        break;
    }
    case XZ:
    {
        setX(point.x());
        setZ(point.y());
        break;
    }
    case YZ:
    {
        setY(point.x());
        setZ(point.y());
        break;
    }
    }
    return *this;
}

CNC3DPoint& CNC3DPoint::setCoordinate(Axis axis, double value)
{
    switch(axis)
    {
    case X:
        return setX(value);
    case Y:
        return setY(value);
    case Z:
        return setZ(value);
    }
    //Тут мы никогда не окажемся
    return *this;
}

double CNC3DPoint::coordinate(Axis axis) const
{
    switch(axis)
    {
    case X:
        return x();
    case Y:
        return y();
    case Z:
        return z();
    }
    //Тут мы никогда не окажемся
    return 0.0;
}

CNC3DPoint& CNC3DPoint::setX(double xCoordinate)
{
    m_x = xCoordinate;
    m_nullPoint = false;
    return *this;
}

double CNC3DPoint::x() const
{
    return m_x;
}

CNC3DPoint& CNC3DPoint::setY(double yCoordinate)
{
    m_y = yCoordinate;
    m_nullPoint = false;
    return *this;
}

double CNC3DPoint::y() const
{
    return m_y;
}

CNC3DPoint& CNC3DPoint::setZ(double zCoordinate)
{
    m_z = zCoordinate;
    m_nullPoint = false;
    return *this;
}

double CNC3DPoint::z() const
{
    return m_z;
}

bool CNC3DPoint::isNull() const
{
    return m_nullPoint;
}

CNC3DPoint& CNC3DPoint::setPoint(double xCoordinate,
                          double yCoordinate,
                          double zCoordinate)
{
    setX(xCoordinate);
    setY(yCoordinate);
    setZ(zCoordinate);
    return *this;
}

CNC3DPoint& CNC3DPoint::operator=(const CNC3DPoint& assignFrom)
{
    setPoint(assignFrom.x(), assignFrom.y(), assignFrom.z());
    m_nullPoint = assignFrom.isNull();
    return *this;
}

void CNC3DPoint::initZeroes()
{
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_nullPoint = true;
}

CNC3DPoint CNC3DPoint::operator+(const CNC3DPoint& plus) const
{
    CNC3DPoint point(
                x()+plus.x(),
                y()+plus.y(),
                z()+plus.z());
    return point;
}

CNC3DPoint CNC3DPoint::operator-(const CNC3DPoint& minus) const
{
    CNC3DPoint point(
                x()-minus.x(),
                y()-minus.y(),
                z()-minus.z());
    return point;
}

CNC3DPoint& CNC3DPoint::operator+=(const CNC3DPoint& diff)
{
    setX(x()+diff.x());
    setY(y()+diff.y());
    setZ(z()+diff.z());
    return *this;
}

CNC3DPoint& CNC3DPoint::operator-=(const CNC3DPoint& diff)
{
    setX(x()-diff.x());
    setY(y()-diff.y());
    setZ(z()-diff.z());
    return *this;
}

CNC2DPoint CNC3DPoint::to2DPoint(Plane2D plane) const
{
    CNC2DPoint outPoint;
    switch(plane)
    {
    case XY:
    {
        outPoint.setX(x());
        outPoint.setY(y());
        break;
    }
    case XZ:
    {
        outPoint.setX(x());
        outPoint.setY(z());
        break;
    }
    case YZ:
    {
        outPoint.setX(y());
        outPoint.setY(z());
        break;
    }
    }
    return outPoint;
}



