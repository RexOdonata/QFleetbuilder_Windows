#ifndef SHIPVIEWDIALOG_H
#define SHIPVIEWDIALOG_H

#include "../ShipView/shipview.h"

#include <QDialog>

namespace Ui {
class shipViewDialog;
}

class shipViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit shipViewDialog(QWidget *parent = nullptr, std::optional<QFleet_Ship_Fleet> ship= {});
    ~shipViewDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::shipViewDialog *ui;

    shipView * shipviewWidget = NULL;
};

#endif // SHIPVIEWDIALOG_H
