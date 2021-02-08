#ifndef QSETTINGSOPTIONCNC2DPOINT_H
#define QSETTINGSOPTIONCNC2DPOINT_H
#include <QSettingsOptionBase.h>
#include <coord/CNC2DPoint.h>

class QSettingsOptionCNC2DPoint : public QSettingsOptionBase<CNC2DPoint>
{
public:
    QSettingsOptionCNC2DPoint(QSettings* settings,
                              const QString& name,
                              const CNC2DPoint& defaultValue)
        :QSettingsOptionBase(settings, name, defaultValue) {}

protected:
    virtual QString toString(const CNC2DPoint& value) const;
    virtual CNC2DPoint fromString(const QString& value) const;
};
#endif // QSETTINGSCNCOPTIONCNC2DPOINT_H
