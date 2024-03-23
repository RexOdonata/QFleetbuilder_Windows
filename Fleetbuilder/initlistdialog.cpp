#include "initlistdialog.h"
#include "ui_initlistdialog.h"

initListDialog::initListDialog(QWidget *parent, listInit * data) :
    QDialog(parent),
    ui(new Ui::initListDialog),
    dataPtr(data)
{
    ui->setupUi(this);


}

initListDialog::~initListDialog()
{
    delete ui;
}

void initListDialog::on_saveButton_clicked()
{
    bool valid = true;

    auto selRadio = ui->factionRadioGroup->checkedButton();

    // pointer addresses for the buttons are not compile time, cannot be switched on
    if (selRadio == ui->ucmRadio)
        dataPtr->listFaction = faction::UCM;
    else if (selRadio == ui->scourgeRadio)
        dataPtr->listFaction = faction::SCOURGE;
    else if (selRadio == ui->phrRadio)
        dataPtr->listFaction = faction::PHR;
    else if (selRadio == ui->shaltariRadio)
        dataPtr->listFaction = faction::SHALTARI;
    else if (selRadio == ui->resistanceRadio)
        dataPtr->listFaction = faction::RESISTANCE;
    else
        valid = false;

    if (ui->pointsLimitSpin->value() > 0)
        dataPtr->listPoints = ui->pointsLimitSpin->value();
    else
        valid = false;

    if (valid)
        this->done(QDialog::Accepted);
    else
        this->done(QDialog::Rejected);

}

