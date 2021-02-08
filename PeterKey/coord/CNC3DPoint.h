#ifndef CNC3DPOINT_H
#define CNC3DPOINT_H
#include <key-cutter-cnc-engine_global.h>
#include <QMetaType>
#include <QFlags>
#include <coord/CNC2DPoint.h>

class KEYCUTTERCNCENGINE_EXPORT CNC3DPoint
{
public:
    enum Axis
    {
        X,
        Y,
        Z
    };

    enum Plane2D
    {
        XY,
        XZ,
        YZ
    };

    CNC3DPoint();
    CNC3DPoint(double xCoordinate, double yCoordinate, double zCoordinate);
    CNC3DPoint(const CNC3DPoint& copyFrom);
    CNC3DPoint(const QString& str);
    CNC3DPoint(const CNC2DPoint& point, Plane2D plane);
    ~CNC3DPoint();

    CNC3DPoint& setX(double xCoordinate);
    double x() const;
    CNC3DPoint& setY(double yCoordinate);
    double y() const;
    CNC3DPoint& setZ(double zCoordinate);
    double z() const;
    CNC3DPoint& setPoint(double xCoordinate,
                         double yCoordinate,
                         double zCoordinate);
    CNC3DPoint& set2DPoint(const CNC2DPoint& point,
                           Plane2D plane);
    CNC3DPoint& setCoordinate(Axis axis, double value);
    double coordinate(Axis axis) const;

    QString toString() const;
    CNC2DPoint to2DPoint(Plane2D plane) const;

    bool isNull() const;
    CNC3DPoint& rotate(double angleRadian,
                       Plane2D plane,
                       const CNC2DPoint& center=CNC2DPoint(0,0));

    CNC3DPoint& operator=(const CNC3DPoint& assignFrom);
    CNC3DPoint operator+(const CNC3DPoint& diff) const;
    CNC3DPoint operator-(const CNC3DPoint& diff) const;
    CNC3DPoint& operator+=(const CNC3DPoint& diff);
    CNC3DPoint& operator-=(const CNC3DPoint& diff);

private:
    bool m_nullPoint;
    double m_x;
    double m_y;
    double m_z;

    void initZeroes();
};

Q_DECLARE_METATYPE(CNC3DPoint)

#endif // CNC3DPOINT_H
