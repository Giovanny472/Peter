#include "QSettingsOptionCNC3DPoint.h"

QString QSettingsOptionCNC3DPoint::toString(const CNC3DPoint& value) const
{
    return value.toString();
}

CNC3DPoint QSettingsOptionCNC3DPoint::fromString(const QString& value) const
{
    return CNC3DPoint(value);
}
