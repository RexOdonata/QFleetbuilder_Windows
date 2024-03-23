#include "shipviewdialog.h"
#include "ui_shipviewdialog.h"

shipViewDialog::shipViewDialog(QWidget *parent, std::optional<QFleet_Ship_Fleet> ship) :
    QDialog(parent),
    ui(new Ui::shipViewDialog)

{
    ui->setupUi(this);

    shipviewWidget = new shipView(this);

    ui->shipviewLayout->addWidget(shipviewWidget);

    shipviewWidget->loadShip(*ship);
}

shipViewDialog::~shipViewDialog()
{
    delete shipviewWidget;

    delete ui;
}

void shipViewDialog::on_pushButton_clicked()
{
    this->done(QDialog::Accepted);
}

