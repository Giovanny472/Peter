#ifndef KEYCUTTERABSTRACTFORM_H
#define KEYCUTTERABSTRACTFORM_H
#include <QWidget>

class KeyCutterAbstractForm : public QWidget
{
    Q_OBJECT
public:
    explicit KeyCutterAbstractForm();
    ~KeyCutterAbstractForm();

    virtual QWidget* toolWidget()=0;
    virtual QWidget* actionWidget()=0;
};

#endif // KEYCUTTERABSTRACTFORM_H
