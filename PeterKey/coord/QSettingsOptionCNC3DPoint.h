#ifndef QSETTINGSOPTIONCNC3DPOINT_H
#define QSETTINGSOPTIONCNC3DPOINT_H
#include <QSettingsOptionBase.h>
#include <coord/CNC3DPoint.h>

class QSettingsOptionCNC3DPoint : public QSettingsOptionBase<CNC3DPoint>
{
public:
    QSettingsOptionCNC3DPoint(QSettings* settings,
                              const QString& name,
                              const CNC3DPoint& defaultValue)
        :QSettingsOptionBase(settings, name, defaultValue) {}

protected:
    virtual QString toString(const CNC3DPoint& value) const;
    virtual CNC3DPoint fromString(const QString& value) const;
};

#endif // QSETTINGSOPTIONCNC3DPOINT_H
