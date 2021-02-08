#include "KeyCutterAbstractDialog.h"
#include "ui_KeyCutterAbstractDialog.h"

KeyCutterAbstractDialog::KeyCutterAbstractDialog(ButtonFlags buttons):
    m_ui(new Ui::KeyCutterAbstractDialog)
{
    m_ui->setupUi(this);
    setButtons(buttons);
    m_buttonPressed = NoButton;

    m_localLoop = new QEventLoop(this);
}

KeyCutterAbstractDialog::~KeyCutterAbstractDialog()
{
    delete m_localLoop;
}

QWidget* KeyCutterAbstractDialog::actionWidget()
{
    return m_ui->wgActions;
}

void KeyCutterAbstractDialog::setButtons(ButtonFlags buttons)
{
    m_buttonConfig = buttons;

    m_ui->backPadder->setVisible(!buttons.testFlag(BackButton));
    m_ui->pbBack->setVisible(buttons.testFlag(BackButton));

    m_ui->forwardPadder->setVisible(!buttons.testFlag(ForwardButton));
    m_ui->pbForward->setVisible(buttons.testFlag(ForwardButton));
}

KeyCutterAbstractDialog::Button KeyCutterAbstractDialog::modalExec()
{
    if(!exec())
        return NoButton;
    m_localLoop->exec();
    return m_buttonPressed;
}

bool KeyCutterAbstractDialog::exec()
{
    return true;
}

KeyCutterAbstractDialog::ButtonFlags KeyCutterAbstractDialog::buttons()
{
    return m_buttonConfig;
}

void KeyCutterAbstractDialog::setButtonEnabled(Button button, bool enabled)
{
    switch(button)
    {
    case NoButton:
        break;
    case BackButton:
        m_ui->pbBack->setEnabled(enabled);
        break;
    case ForwardButton:
        m_ui->pbForward->setEnabled(enabled);
        break;
    }
}

bool KeyCutterAbstractDialog::isButtonEnabled(Button button)
{
    switch(button)
    {
    case BackButton:
        return m_ui->pbBack->isEnabled();
    case ForwardButton:
        return m_ui->pbForward->isEnabled();
    default:
        return NoButton;
    }
}

void KeyCutterAbstractDialog::on_pbBack_clicked()
{
    m_buttonPressed = BackButton;
    emit backButtonClicked();
    if(m_localLoop->isRunning())
        m_localLoop->quit();
}

void KeyCutterAbstractDialog::on_pbForward_clicked()
{
    m_buttonPressed = ForwardButton;
    emit forwardButtonClicked();
    if(m_localLoop->isRunning())
        m_localLoop->quit();
}
