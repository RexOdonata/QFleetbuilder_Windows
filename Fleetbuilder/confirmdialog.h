#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

namespace Ui {
class confirmDialog;
}

class confirmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit confirmDialog(QWidget *parent = nullptr);
    ~confirmDialog();

    void setMsg(const QString);

private slots:
    void on_yesButton_clicked();

    void on_nobutton_clicked();

private:
    Ui::confirmDialog *ui;
};

#endif // CONFIRMDIALOG_H
