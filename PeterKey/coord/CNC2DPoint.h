#ifndef CNC2DPOINT_H
#define CNC2DPOINT_H
//#include <key-cutter-cnc-engine_global.h>
#include <QFlags>
#include <QMetaType>

class CNC2DPoint
{
public:
    CNC2DPoint();
    CNC2DPoint(double xCoordinate, double yCoordinate);
    CNC2DPoint(const CNC2DPoint& copyFrom);
    CNC2DPoint(const QString& str);
    ~CNC2DPoint();

    CNC2DPoint& setX(double xCoordinate);
    double x() const;
    CNC2DPoint& setY(double yCoordinate);
    double y() const;
    CNC2DPoint& setPoint(double xCoordinate, double yCoordinate);

    QString toString() const;

    bool isNull() const;
    CNC2DPoint& rotate(double angleRadian,
                       const CNC2DPoint& center=CNC2DPoint(0,0));

    CNC2DPoint& operator=(const CNC2DPoint& assignFrom);

    CNC2DPoint operator+(const CNC2DPoint& diff) const;
    CNC2DPoint& operator+=(const CNC2DPoint& diff);

    CNC2DPoint operator-(const CNC2DPoint& diff) const;
    CNC2DPoint& operator-=(const CNC2DPoint& diff);

    CNC2DPoint operator*(const CNC2DPoint& diff) const;
    CNC2DPoint& operator*=(const CNC2DPoint& diff);

    CNC2DPoint& invertPointCoordinates();

private:
    bool m_nullPoint;
    double m_x;
    double m_y;

    void initZeroes();
};

Q_DECLARE_METATYPE(CNC2DPoint)

#endif // CNC2DPOINT_H
