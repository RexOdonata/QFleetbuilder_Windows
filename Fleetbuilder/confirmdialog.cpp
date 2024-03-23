#include "confirmdialog.h"
#include "ui_confirmdialog.h"

confirmDialog::confirmDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirmDialog)
{
    ui->setupUi(this);
}

confirmDialog::~confirmDialog()
{
    delete ui;
}

void confirmDialog::on_yesButton_clicked()
{
    this->done(QDialog::Accepted);
}


void confirmDialog::on_nobutton_clicked()
{
    this->done(QDialog::Rejected);
}

void confirmDialog::setMsg(const QString msg)
{
    ui->msgLabel->setText(msg);
}

