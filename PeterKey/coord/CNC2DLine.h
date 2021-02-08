#ifndef CNC2DLINE_H
#define CNC2DLINE_H
#include <coord/CNC2DPoint.h>

class CNC2DLine
{
public:
    CNC2DLine();
    CNC2DLine(const CNC2DPoint& first);
    CNC2DLine(const CNC2DPoint& first, const CNC2DPoint& second);

    void setFirstPoint(const CNC2DPoint &first);
    const CNC2DPoint& constFirstPoint() const;
    CNC2DPoint& firstPoint();
    void setSecondPoint(const CNC2DPoint &second);
    const CNC2DPoint& constSecondPoint() const;
    CNC2DPoint secondPoint();
    void setPoints(const CNC2DPoint &first, const CNC2DPoint &second);

    bool isNull() const;

    void rotate(double radianAngle);
    double length();
    double xAxisRadianAngle();
    CNC2DPoint perpedicularFromPointIntersection(
            const CNC2DPoint& point) const;
    CNC2DLine parralelTo(double distance);
    CNC2DPoint intersectionPoint(const CNC2DLine& line);

    double cfK() const;
    double cfB() const;

private:
    CNC2DPoint m_firstPoint;
    CNC2DPoint m_secondPoint;

    double m_k;
    double m_b;
    void findCoefficients();
};

#endif // CNC2DLINE_H
