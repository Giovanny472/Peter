#ifndef CNCLOCALCOORDINATESYSTEM_H
#define CNCLOCALCOORDINATESYSTEM_H
#include <coord/CNC3DPoint.h>
#include <coord/CNC3DPointVector.h>
#include <QHash>

class CNCLocalCoordinateSystem
{
public:
    typedef QHash<CNC3DPoint::Plane2D, double> PlaneRotations;
    typedef QHash<CNC3DPoint::Axis, bool> AxisReversions;

public:
    CNCLocalCoordinateSystem();

    //Описание глобальной системы, относительно которой строится эта
    const CNC3DPoint& globalOffset() const;
    void setGlobalOffset(const CNC3DPoint& globalOffset);
    bool isGlobalAxisReversed(CNC3DPoint::Axis axis) const;
    void setGlobalAxisReversed(CNC3DPoint::Axis axis, bool reversed);

    //Описание вращений этой системы, относительно глобальной
    //Исходим из того, что глобальная система поворота не имеет
    double rotationAngle(CNC3DPoint::Plane2D plane) const;
    void setRotationAngle(CNC3DPoint::Plane2D plane, double angleRadian);

    //Пересчитать точку в глобальную систему из локальной
    CNC3DPoint& mapPointToGlobal(CNC3DPoint& localPoint) const;
    CNC3DPointVector& mapPointsToGlobal(CNC3DPointVector& localPoints) const;

    //Пересчитать точку из глобальной системы в локальную
    CNC3DPoint& mapPointFromGlobal(CNC3DPoint& globalPoint) const;
    CNC3DPointVector& mapPointsFromGlobal(CNC3DPointVector& globalPoints) const;

private:
    CNC3DPoint m_globalOffset;
    PlaneRotations m_rotations;
    AxisReversions m_axisReversions;
};

#endif // CNCLOCALCOORDINATESYSTEM_H
