#include "shipselect.h"
#include "ui_shipselect.h"

#include "optselect.h"

#include <QMessageBox>

shipSelect::shipSelect(QWidget *parent, const QMap<QString,QFleet_Ship_Shipyard> * setShipData) :
    QDialog(parent),
    ui(new Ui::shipSelect),
    shipData(setShipData),
    ship(QFleet_Ship_Fleet("Placeholder"))

{
    ui->setupUi(this);

    shipTreeModel = new QStandardItemModel(0,1);

    shipViewWidget = new shipView(this);

    ui->shipViewLayout->addWidget(shipViewWidget);

    // setup the tree view

    ui->treeView->setHeaderHidden(true);

    std::array<QStandardItem *, 5> categories;
    categories[0] = new QStandardItem(QString("Lights"));
    categories[1] = new QStandardItem(QString("Destroyers"));
    categories[2] = new QStandardItem(QString("Cruisers"));
    categories[3] = new QStandardItem(QString("Heavies"));
    categories[4] = new QStandardItem(QString("Flagships"));

    QStringList strList;

    // insert ships items into the category items they belong in
    for (auto& shipName : shipData->keys())
    {
        insertShip(categories, shipName);
        strList.append(shipName);
    }

    // insert the categories
    for (auto& item : categories)
    {
        auto index = shipTreeModel->rowCount();

        shipTreeModel->insertRow(index);

        shipTreeModel->setItem(index, item);
    }

    strModel = new QStringListModel(this);
    strModel->setStringList(strList);

    completer = new QCompleter(strModel, this);

    completer->setCaseSensitivity(Qt::CaseInsensitive);

    ui->shipSearchEdit->setCompleter(completer);

    ui->treeView->setModel(shipTreeModel);

    ui->validCheck->setEnabled(false);

    this->setAttribute(Qt::WA_DeleteOnClose);
}

void shipSelect::insertShip(std::array<QStandardItem *,5> models, const QString shipName)
{

    QStandardItem * shipItem = new QStandardItem(shipName);

    auto val = shipData->value(shipName).tonnage.getIntValue();

    switch (val)
    {
        case 1:
            models[0]->appendRow(shipItem);
            break;

        case 2:
            models[1]->appendRow(shipItem);
            break;

        case 5:
            models[2]->appendRow(shipItem);
            break;

        case 10:
            models[3]->appendRow(shipItem);
            break;

        case 15:
            models[4]->appendRow(shipItem);
            break;

        case 30:
            models[4]->appendRow(shipItem);
            break;

        default:
            // this should NEVER happen, but it handles a possible memory leak
            delete shipItem;
            break;
    }
}

shipSelect::~shipSelect()
{
    delete shipViewWidget;
    delete shipTreeModel;
    delete completer;
    delete strModel;
    delete ui;
}

// given the selected ship, load the ship view andset that ship to be selected

void shipSelect::selectShip(QString shipName)
{
    if (shipData->contains(shipName))
    {
        QFleet_Ship_Shipyard indexShip = shipData->value(shipName);

        QVector<QFleet_Option> blank;

        QFleet_Ship_Fleet fleetShip = createShip(indexShip,blank,"");

        this->ship = fleetShip;
        // check if the selected ship has mandatory options which won't have been selected at this point
        if (checkMinOpts(indexShip))
        {
            this->valid = true;
            ui->validCheck->setChecked(Qt::Checked);
            emit signalSendShip(fleetShip);
            ui->selectOptionsButton->setEnabled(false);
        }
        else
        {
            this->valid = false;
            ui->validCheck->setChecked(Qt::Unchecked);
            emit signalResetShip(selectMinOptionsMsg);
            ui->selectOptionsButton->setEnabled(true);
        }


        shipViewWidget->loadShip(fleetShip);
        selectedName = shipName;
    }
}

QFleet_Ship_Fleet shipSelect::createShip(const QFleet_Ship_Shipyard& shipSrc, QVector<QFleet_Option>& opts, const QString customName)
{
    QString newName = shipSrc.name;

    if (!customName.isEmpty())
        newName.append(QString(" (%1)").arg(customName));

    QFleet_Ship_Fleet newShip(newName);

    newShip.points = shipSrc.points;
    newShip.scan = shipSrc.scan;
    newShip.signature = shipSrc.signature;
    newShip.altSig = shipSrc.altSig;
    newShip.thrust = shipSrc.thrust;
    newShip.hull = shipSrc.hull;
    newShip.armor = shipSrc.armor;
    newShip.passive = shipSrc.passive;
    newShip.PD = shipSrc.PD;
    newShip.groupL = shipSrc.groupL;
    newShip.groupH = shipSrc.groupH;
    newShip.tonnage = shipSrc.tonnage;
    newShip.specialRules = shipSrc.specialRules;
    newShip.weapons = shipSrc.weapons;
    newShip.launch = shipSrc.launch;
    newShip.admiralDiscount = shipSrc.admiralDiscount;
    newShip.uniqueSpecial = shipSrc.uniqueSpecial;

    // extract options into the ship
    for (auto& opt : opts)
    {
        newShip.points += opt.points;

            switch(opt.type.getVal())
            {
                case optType::WEAPONS:
                for (auto& weapon : *opt.weaponVecPtr)
                    {
                        newShip.weapons.push_back(weapon);
                    }
                    break;

                case optType::LAUNCH:
                    newShip.launch.push_back(*opt.launchProfilePtr);
                    break;

                case optType::STAT:
                    switch(opt.statTypePtr->getVal())
                    {

                    case statID::scan:
                        newShip.scan += *opt.statBonusPtr;
                        break;
                    case statID::sig:
                        newShip.signature += *opt.statBonusPtr;
                        break;
                    case statID::thrust:
                        newShip.thrust += *opt.statBonusPtr;
                        break;
                    case statID::hull:
                        newShip.hull += *opt.statBonusPtr;
                        break;
                    case statID::PD:
                        newShip.PD += *opt.statBonusPtr;
                        break;
                    }

                    break;

                case optType::SPECIAL:
                    for (auto& optSpec : *opt.specialPtr)
                    {
                        newShip.specialRules.push_back(optSpec);
                    }
                    break;
            }
    }

    return newShip;
}


void shipSelect::on_treeView_clicked(const QModelIndex &index)
{
    QString shipName = shipTreeModel->itemFromIndex(index)->text();

    ui->shipSearchEdit->clear();

    selectShip(shipName);
}

bool shipSelect::checkMinOpts(const QFleet_Ship_Shipyard& ship)
{
    if (ship.minOptions > 0)
            return false;
    else
            return true;
}

void shipSelect::slotGetCustomName(QString set)
{
    customNameRx = set;
}

void shipSelect::on_selectOptionsButton_clicked()
{
    auto selectionIndex = ui->treeView->selectionModel()->selectedIndexes();

    if (selectionIndex.size()>0 && !selectedName.isEmpty())
    {
            auto selection = selectionIndex[0];;

            QFleet_Ship_Shipyard indexShip = shipData->value(selectedName);

            QVector<QFleet_Option> options;

            optSelect * dialog = new optSelect(this, &indexShip, &options);

            connect(dialog, &optSelect::signalCustomName, this, &shipSelect::slotGetCustomName);

            dialog->setAttribute(Qt::WA_DeleteOnClose);

            int r = dialog->exec();

            if (r == QDialog::Accepted)
            {
                QFleet_Ship_Fleet fleetShip = createShip(indexShip, options,customNameRx);

                shipViewWidget->loadShip(fleetShip);

                this->ship = fleetShip;
                this->valid = true;
                ui->validCheck->setChecked(Qt::Checked);

                emit signalSendShip(fleetShip);

            }
            else
            {
                this->valid = false;
                ui->validCheck->setChecked(Qt::Unchecked);
                emit signalResetShip("selectMinOptionsMsg");
            }
    }
}


void shipSelect::on_getSearchButton_clicked()
{
    if (completer != NULL && ui->shipSearchEdit != NULL &&
        completer->completionCount() == 1 && ui->shipSearchEdit->text().length() > 0)
    {
            QString shipName = ui->shipSearchEdit->text();

            selectShip(shipName);
    }
}

