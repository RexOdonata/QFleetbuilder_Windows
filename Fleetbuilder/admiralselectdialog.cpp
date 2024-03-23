#include "admiralselectdialog.h"
#include "ui_admiralselectdialog.h"

admiralSelectDialog::admiralSelectDialog(QWidget *parent, const QFleet_Ship_Fleet * ship) :
    QDialog(parent),
    ui(new Ui::admiralSelectDialog)
{
    ui->setupUi(this);

    for (int lvl = 2; lvl <= 5; lvl++)
    {
        auto val = ship->admiralCost(lvl);
        if (val)
            costs[lvl-2] = *val;
    }

    ui->radioButtonGroup->setId(ui->l2Radio, 0);
    ui->radioButtonGroup->setId(ui->l3Radio, 1);
    ui->radioButtonGroup->setId(ui->l4Radio, 2);
    ui->radioButtonGroup->setId(ui->l5Radio, 3);
    ui->radioButtonGroup->setId(ui->l0Radio, 4);

    ui->l2CostLabel->setText(QString::number(costs[0]));
    ui->l3CostLabel->setText(QString::number(costs[1]));
    ui->l4CostLabel->setText(QString::number(costs[2]));
    ui->l5CostLabel->setText(QString::number(costs[3]));
}

admiralSelectDialog::~admiralSelectDialog()
{
    delete ui;
}

void admiralSelectDialog::on_l2Radio_clicked()
{
    lvl = 2;
    cost = costs[0];

}


void admiralSelectDialog::on_l3Radio_clicked()
{
    lvl = 3;
    cost = costs[1];
}


void admiralSelectDialog::on_l4Radio_clicked()
{
    lvl = 4;
    cost = costs[2];
}


void admiralSelectDialog::on_l5Radio_clicked()
{
    lvl = 5;
    cost = costs[3];
}


void admiralSelectDialog::on_doneButton_clicked()
{
    auto checked = ui->radioButtonGroup->checkedId();
    if ( checked != -1)
    {
        admiralVals newAdmiralVals;
        newAdmiralVals.cost = cost;
        newAdmiralVals.level=lvl;

        emit signalAdmiralValue(newAdmiralVals);

        this->done(QDialog::Accepted);
    }
    else
        this->done(QDialog::Rejected);
}


void admiralSelectDialog::on_l0Radio_clicked()
{
    lvl = 0;
    cost = 0;
}

