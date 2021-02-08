#include "CNCLocalCoordinateSystem.h"
#include <QVector>

CNCLocalCoordinateSystem::CNCLocalCoordinateSystem()
{
}

const CNC3DPoint& CNCLocalCoordinateSystem::globalOffset() const
{
    return m_globalOffset;
}

void CNCLocalCoordinateSystem::setGlobalOffset(const CNC3DPoint& zeroPoint)
{
    m_globalOffset = zeroPoint;
}

bool CNCLocalCoordinateSystem::isGlobalAxisReversed(
        CNC3DPoint::Axis axis) const
{
    return m_axisReversions.value(axis, false);
}

void CNCLocalCoordinateSystem::setGlobalAxisReversed(CNC3DPoint::Axis axis,
                                                     bool reversed)
{
    m_axisReversions.insert(axis, reversed);
}

double CNCLocalCoordinateSystem::rotationAngle(
        CNC3DPoint::Plane2D plane) const
{
    return m_rotations.value(plane, 0);
}

void CNCLocalCoordinateSystem::setRotationAngle(CNC3DPoint::Plane2D plane,
                                           double angleRadian)
{
    m_rotations.insert(plane, angleRadian);
}

//TODO: Это надо переписать с суровой математикой
CNC3DPoint& CNCLocalCoordinateSystem::mapPointToGlobal(
        CNC3DPoint &localPoint) const
{
    QVector<CNC3DPoint::Plane2D> plains;
    plains<<CNC3DPoint::XY<<CNC3DPoint::XZ<<CNC3DPoint::YZ;
    QVector<CNC3DPoint::Axis> axes;
    axes<<CNC3DPoint::X<<CNC3DPoint::Y<<CNC3DPoint::Z;

    //Разворачиваем точку к глобальной системе
    //Относительно своего нуля координат
    foreach(CNC3DPoint::Plane2D plane, plains)
        localPoint.rotate(rotationAngle(plane), plane);

    //Пересчитываем точку к глобальной
    foreach(CNC3DPoint::Axis axis, axes)
    {
        if(isGlobalAxisReversed(axis))
            localPoint.setCoordinate(axis, localPoint.coordinate(axis)*(-1));
        localPoint.setCoordinate(
                    axis,
                    localPoint.coordinate(axis) +
                    globalOffset().coordinate(axis));
    }

    return localPoint;
}

//TODO: Это мне не нравится
CNC3DPointVector& CNCLocalCoordinateSystem::mapPointsToGlobal(
        CNC3DPointVector& localPoints) const
{
    for(int i=0; i<localPoints.count(); i++)
        mapPointToGlobal(localPoints[i]);
    return localPoints;
}

CNC3DPoint& CNCLocalCoordinateSystem::mapPointFromGlobal(
        CNC3DPoint& globalPoint) const
{
    QVector<CNC3DPoint::Plane2D> plains;
    plains<<CNC3DPoint::XY<<CNC3DPoint::XZ<<CNC3DPoint::YZ;
    QVector<CNC3DPoint::Axis> axes;
    axes<<CNC3DPoint::X<<CNC3DPoint::Y<<CNC3DPoint::Z;

    //Пересчитываем точку от глобальной к локальной
    foreach(CNC3DPoint::Axis axis, axes)
    {
        globalPoint.setCoordinate(
                    axis,
                    globalPoint.coordinate(axis) -
                    globalOffset().coordinate(axis));
        if(isGlobalAxisReversed(axis))
            globalPoint.setCoordinate(axis, globalPoint.coordinate(axis)*(-1));
    }

    //Разворачиваем точку от глобальной системы
    //Относительно своего нуля координат
    foreach(CNC3DPoint::Plane2D plane, plains)
        globalPoint.rotate(rotationAngle(plane)*(-1), plane);
    return globalPoint;
}

CNC3DPointVector& CNCLocalCoordinateSystem::mapPointsFromGlobal(
        CNC3DPointVector& globalPoints) const
{
    for(int i=0; i<globalPoints.count(); i++)
        mapPointFromGlobal(globalPoints[i]);
    return globalPoints;
}



