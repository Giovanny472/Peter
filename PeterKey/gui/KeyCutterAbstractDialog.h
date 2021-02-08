#ifndef KEYCUTTERABSTRACTDIALOG_H
#define KEYCUTTERABSTRACTDIALOG_H
#include <QObject>
#include "gui/KeyCutterAbstractForm.h"

namespace Ui {
class KeyCutterAbstractDialog;
}

class QEventLoop;

class KeyCutterAbstractDialog : public KeyCutterAbstractForm
{
    Q_OBJECT

public:
    enum Button
    {
        NoButton=0x00,
        BackButton=0x01,
        ForwardButton=0x02
    };

    Q_DECLARE_FLAGS(ButtonFlags, Button)

    KeyCutterAbstractDialog(ButtonFlags buttons=BackButton);
    ~KeyCutterAbstractDialog();

    virtual QWidget* toolWidget()=0;
    virtual QWidget* actionWidget();

    void setButtons(ButtonFlags buttons);
    ButtonFlags buttons();

    void setButtonEnabled(Button button, bool enabled);
    bool isButtonEnabled(Button button);

    Button modalExec();

protected:
    virtual bool exec();

private:
    Ui::KeyCutterAbstractDialog *m_ui;
    ButtonFlags m_buttonConfig;
    bool m_backIsShutdown;

    QEventLoop* m_localLoop;
    Button m_buttonPressed;

signals:
    void backButtonClicked();
    void forwardButtonClicked();

private slots:
    void on_pbBack_clicked();
    void on_pbForward_clicked();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(KeyCutterAbstractDialog::ButtonFlags)

#endif // KEYCUTTERABSTRACTDIALOG_H
