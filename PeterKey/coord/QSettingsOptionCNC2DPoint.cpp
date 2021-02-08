#include "QSettingsOptionCNC2DPoint.h"

QString QSettingsOptionCNC2DPoint::toString(const CNC2DPoint& value) const
{
    return value.toString();
}

CNC2DPoint QSettingsOptionCNC2DPoint::fromString(const QString& value) const
{
    return CNC2DPoint(value);
}
