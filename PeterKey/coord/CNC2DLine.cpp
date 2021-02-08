#include "CNC2DLine.h"
#include <QtMath>

CNC2DLine::CNC2DLine()
{
    m_k=0;
    m_b=0;
}

CNC2DLine::CNC2DLine(const CNC2DPoint& first)
{
    setPoints(CNC2DPoint(0,0), first);
}

CNC2DLine::CNC2DLine(const CNC2DPoint& first, const CNC2DPoint& second)
{
    setPoints(first, second);
}

void CNC2DLine::setFirstPoint(const CNC2DPoint& first)
{
    m_firstPoint = first;
    findCoefficients();
}

const CNC2DPoint& CNC2DLine::constFirstPoint() const
{
    return m_firstPoint;
}

CNC2DPoint& CNC2DLine::firstPoint()
{
    return m_firstPoint;
}

void CNC2DLine::setSecondPoint(const CNC2DPoint& second)
{
    m_secondPoint = second;
    findCoefficients();
}

const CNC2DPoint& CNC2DLine::constSecondPoint() const
{
    return m_secondPoint;
}

CNC2DPoint CNC2DLine::secondPoint()
{
    return m_secondPoint;
}

void CNC2DLine::setPoints(const CNC2DPoint& first, const CNC2DPoint& second)
{
    setFirstPoint(first);
    setSecondPoint(second);
}

bool CNC2DLine::isNull() const
{
    return (constFirstPoint().isNull() || constSecondPoint().isNull());
}

void CNC2DLine::rotate(double radianAngle)
{
    firstPoint().rotate(radianAngle);
    secondPoint().rotate(radianAngle);
    findCoefficients();
}

double CNC2DLine::length()
{
    double xLength = constSecondPoint().x() - constFirstPoint().x();
    double yLength = constSecondPoint().y() - constFirstPoint().y();
    double value = xLength*xLength+yLength*yLength;
    if(value<0)
        value*=-1;
    return qSqrt(value);
}

double CNC2DLine::xAxisRadianAngle()
{
    if(constSecondPoint().x()==constFirstPoint().x())
        return qDegreesToRadians(90.0);
    return qAtan(m_k);
}

CNC2DPoint CNC2DLine::perpedicularFromPointIntersection(
        const CNC2DPoint& point) const
{
    //Найти k для нашей прямой second-third
    double k1 = cfK();
    //Найти b для прямой second-third
    double b1 = cfB();
    //Найти b для прямой, проходящей через first
    double k2 = (-1)/k1;
    double b2 = point.y()-k2*point.x();

    //Наконец точка
    CNC2DPoint intersectionPoint;
    intersectionPoint.setX((b2-b1)/(k1-k2));
    intersectionPoint.setY(k1*intersectionPoint.x()+b1);
    return intersectionPoint;
}

double CNC2DLine::cfK() const
{
    return m_k;
}

double CNC2DLine::cfB() const
{
    return m_b;
}

void CNC2DLine::findCoefficients()
{
    m_k = (constSecondPoint().y()-constFirstPoint().y())/
            (constSecondPoint().x()-constFirstPoint().x());
    m_b = constFirstPoint().y()-cfK()*constFirstPoint().x();
}

//TODO: dummy foo
CNC2DLine CNC2DLine::parralelTo(double distance)
{
    Q_UNUSED(distance)
    CNC2DLine newLine(*this);
    return newLine;
}

CNC2DPoint CNC2DLine::intersectionPoint(const CNC2DLine& line)
{
    CNC2DPoint intrscPoint;
    intrscPoint.setX((cfB()-line.cfB())/(cfK()-line.cfK()));
    intrscPoint.setY(cfK()*firstPoint().x()+cfB());
    return intrscPoint;
}

