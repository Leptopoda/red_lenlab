#ifndef GUI_SIGNALFORM_H
#define GUI_SIGNALFORM_H

#include <QWidget>

namespace gui {

namespace Ui {
class SignalForm;
}

class SignalForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignalForm(QWidget *parent = 0);
    ~SignalForm();

private:
    Ui::SignalForm *ui;
};


} // namespace gui
#endif // GUI_SIGNALFORM_H
