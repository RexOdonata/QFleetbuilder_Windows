#ifndef ADMIRALSELECTDIALOG_H
#define ADMIRALSELECTDIALOG_H

#include <QDialog>
#include <optional>

#include "../Components/qfleet_ship_fleet.h"

#include "qflw_group.h"

namespace Ui {
class admiralSelectDialog;
}

class admiralSelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit admiralSelectDialog(QWidget *parent = nullptr, const QFleet_Ship_Fleet * ship = NULL);
    ~admiralSelectDialog();

signals:

    void signalAdmiralValue(admiralVals);


private slots:
    void on_l2Radio_clicked();

    void on_l3Radio_clicked();

    void on_l4Radio_clicked();

    void on_l5Radio_clicked();

    void on_doneButton_clicked();

    void on_l0Radio_clicked();

private:
    Ui::admiralSelectDialog *ui;

    unsigned int lvl = 0;

    unsigned int cost = 0;

    std::array<unsigned int, 4> costs = {0,0,0,0};
};

#endif // ADMIRALSELECTDIALOG_H
