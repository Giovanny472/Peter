#include "gui/KeyCutterAbstractForm.h"
#include <QPushButton>
#include <QLabel>
#include "gui/KeyCutterFormEngine.h"

KeyCutterAbstractForm::KeyCutterAbstractForm()
    :QWidget(nullptr)
{
    qDebug("KeyCutterAbstractForm::KeyCutterAbstractForm()");
}

KeyCutterAbstractForm::~KeyCutterAbstractForm()
{
    qDebug("KeyCutterAbstractForm::~KeyCutterAbstractForm()");
}
