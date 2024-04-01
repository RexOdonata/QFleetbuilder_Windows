#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "initlistdialog.h"

#include "../common/fileTypes.h"
#include "qmessagebox.h"
#include <iostream>

#include "../ListParts/qfleet_list.h"

#include <QFileDialog>
#include <QJsonParseError>
#include <QClipboard>

#include "../ListPrinter/qfp_strategycard.h"

#include "../ListPrinter/listprinter_legacy.h"
#include "../ListPrinter/listprinter_short.h"

#include "confirmdialog.h"

#include "../compression/compressor.h"
#include "../compression/decompressor.h"

#include "../ListPrinter/qfp_weaponcards.h"
#include "../ListPrinter/qfp_profilecard.h"

#include "../Components/qfleet_data.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setSelectionLabels("");

}

MainWindow::~MainWindow()
{
    if (!listWidget.isNull())
        delete listWidget;

    if (!shipSelectDialog.isNull())
        delete shipSelectDialog;

    delete ui;
}



void MainWindow::on_actionNew_triggered()
{

    // if a list is already loaded, delete it
    if (listWidget)
    {
        delete listWidget;
    }

    if (shipSelectDialog)
    {
        delete shipSelectDialog;
    }

    listInit data;
    initListDialog * newListData = new initListDialog(this,&data);


    newListData->setAttribute(Qt::WA_DeleteOnClose);

    int r = newListData->exec();

    if (r==QDialog::Accepted)
    {
        faction = data.listFaction;

        // load ship Data for the faction of the new list
        if (loadMapFromJsonFile(this))
        {
            setSelectionLabels("");

            listWidget = new QFLW_List(this);

            listWidget->setFaction(data.listFaction);
            listWidget->setPointsLimit(data.listPoints);

            pointsLimit = data.listPoints;

            ui->fleetBox->addWidget(listWidget);
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Couldn't load ship data");
            msg.setWindowTitle("Error");
            msg.exec();
        }

    }

}


// loads ships from a file into the shipdata map and filters out ships from other factions
bool MainWindow::loadMapFromJsonFile(QWidget * parentWindow)
{
    allShipData.clear();

    launchData.clear();

    selectedShip.reset();

    QFleet_Data loadData;

    QString filename = QString("%1%2%3").arg("data",QDir::separator(),"ships.qfs");

    QByteArray bytes;

    if (decompressor::readCompressedFile(bytes,filename))
    {
        QJsonParseError err;

        QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

        QJsonObject wrapperObj = jsonData.object();

        try
        {
            if (wrapperObj.contains(fileType_shipData()))
            {
                QJsonObject loadObj = wrapperObj[fileType_shipData()].toObject();

                loadData = QFleet_Data(loadObj);

                dataDateStr = loadData.getDateStr();

                dataVersionStr = loadData.getVersionStr();

                for (auto& la : loadData.launchData)
                    if (la.factions.contains(*this->faction))
                        launchData.push_back(la);

                for (auto& ship : loadData.shipData)
                    if (ship.factions.contains(*this->faction))
                            allShipData.insert(ship.name, ship);

            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }
        }
        catch (std::invalid_argument)
        {
            QMessageBox msg(this);
            msg.setText("File read Error! file was wrong type or malformed");
            msg.setWindowTitle("Load Error");
            msg.exec();
            return false;
        }


        return true;
    }

    return false;
}

bool MainWindow::loadListFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select QFleet List", QDir::currentPath(),getExtensionFilter(fileType_listData()));

    QByteArray bytes;

    if (decompressor::readCompressedFile(bytes, filename))
    {

        // if a list is already loaded, delete it
        if (listWidget)
        {
            delete listWidget;
        }

        if (shipSelectDialog)
        {
            delete shipSelectDialog;
        }

        QJsonParseError err;

        QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

        QJsonObject wrapperObj = jsonData.object();

        try
        {
            if (wrapperObj.contains(fileType_listData()))
            {
                QFleet_List list(wrapperObj[fileType_listData()].toObject());


                drawGUIFromListPart(list);
            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }
        }
        catch (std::invalid_argument)
        {
            QMessageBox msg(this);
            msg.setText("File read Error! file was wrong type or malformed");
            msg.setWindowTitle("Load Error");
            msg.exec();
        }

        setSelectionLabels("");

        return true;
    }
    else
        return false;
}

// hidden
void MainWindow::on_actionLoad_triggered()
{
    if (loadListFromFile())
    {
        // (-:
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Couldn't open load target for reading");
        msg.exec();
    }
}

void MainWindow::drawGUIFromListPart(const QFleet_List& list)
{
    this->faction = list.getFaction();

    // Load ships for the faction matching the loaded list
    if (loadMapFromJsonFile(this))
    {
        this->pointsLimit = list.getPointsLimit();

        this->listWidget = new QFLW_List(this, list);

        ui->fleetBox->addWidget(listWidget);
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Couldn't load ship data");
        msg.setWindowTitle("Error");
        msg.exec();
    }

}


void MainWindow::on_shipMenuButton_clicked()
{
    // only open if we have actually loaded ships AND there is no open window already
    if (allShipData.size() > 0 && shipSelectDialog.isNull())
    {
        shipSelectDialog = new shipSelect(this, &allShipData);
        shipSelectDialog->setAttribute(Qt::WA_DeleteOnClose);

        connect(shipSelectDialog, &shipSelect::signalSendShip, this, &MainWindow::slotShipSet);

        connect(shipSelectDialog, &shipSelect::signalResetShip, this, &MainWindow::slotShipReset);

        shipSelectDialog->show();
    }
}

void MainWindow::slotShipPull(QFLW_Battlegroup * cardPtr)
{

    if (!selectedShip.has_value())
    {
        QMessageBox msg(this);
        msg.setText("No valid ship selected \n Make a selection in the ship menu.");
        msg.exec();
    }
    else

        cardPtr->recieveSelectedShip(selectedShip.value());


}


bool MainWindow::saveListToFile()
{
    QFleet_List newList = listWidget->createListPart();

    // save dialog goes here

    QString filename = QFileDialog::getSaveFileName(this, "save list", QDir::currentPath(), getExtensionFilter(fileType_listData()));

    QJsonObject json = newList.toJson();

    QJsonObject wrapperObj;

    wrapperObj.insert(fileType_listData(), json);

    QJsonDocument jsonDoc(wrapperObj);

    QByteArray bytes = jsonDoc.toJson(QJsonDocument::Indented);

    if (compressor::writeCompressedFile(bytes,filename))
        return true;
    else
        return false;
}

// hidden
void MainWindow::on_actionSave_triggered()
{

    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;


        if (saveListToFile())
        {

        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Couldn't open save target for writing");
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List to save");
        msg.exec();
    }

}

bool MainWindow::drawProfileCards()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Save strategy cards", QDir::currentPath());

    dir.append(QDir::separator());

    auto cards = listWidget->createListPart().getCards();

    // build a list of all present ships
    QMap<QString, QFleet_Ship_Fleet> shipMap;

    for (auto& card : cards)
    {
        for (auto& group: card.getGroups())
        {
            if (!shipMap.contains(group.getShip().name))
            {
                shipMap.insert(group.getShip().name, group.getShip());
            }
        }
    }

    bool rVal = true;

    for (auto& ship : shipMap)
    {
        {
            QString cardName = QString("%1%2_Weapons.png").arg(dir,ship.name);

            QFP_WeaponCards weaponCard(this, ship);

            weaponCard.show();

            auto px = weaponCard.getImage();

            QFile file(cardName);

            bool r1 = file.open(QIODevice::WriteOnly);

            bool r2 = px.save(&file, "PNG");

            file.close();

            if ((r1 && r2) == false)
                rVal = false;
        }

        {
            QString cardName = QString("%1%2_Profile.png").arg(dir,ship.name);

            QFP_ProfileCard profileCard(this, ship);

            profileCard.show();

            auto px = profileCard.getImage();

            QFile file(cardName);

            bool r1 = file.open(QIODevice::WriteOnly);

            bool r2 = px.save(&file, "PNG");

            file.close();

            if ((r1 && r2) == false)
                rVal = false;
        }


    }

    return rVal;
}

bool MainWindow::drawStrategyCards()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Save strategy cards", QDir::currentPath());

    dir.append(QDir::separator());

    auto cards = listWidget->createListPart().getCards();

    auto index = 0;

    QHash<QString, bool> stringGuard;

    bool rVal = true;

    for (auto& battlegroup : cards)
    {
        QString cardName = QString("%1%2.png").arg(dir,battlegroup.name);

        if (stringGuard.contains(battlegroup.name))
        {
            cardName = dir + "card-" + QString::number(index);
        }

        QFP_StrategyCard card(this, battlegroup);

        card.show();

        auto cardImage = card.getImage();

        QFile file(cardName);

        bool r1 = file.open(QIODevice::WriteOnly);

        bool r2 = cardImage.save(&file, "PNG");

        file.close();

        index++;

        if ((r1 && r2) == false)
            rVal = false;
    }

    return rVal;

}


void MainWindow::on_actionStrategy_Cards_triggered()
{
    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        if (drawStrategyCards())
        {
            QMessageBox msg(this);
            msg.setText("Strategy Card images written to directory");
            msg.setWindowTitle("Success");
            msg.exec();
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("One or more cards files could not be opened for writing");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to print");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}


void MainWindow::on_actionSimple_List_triggered()
{    

    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        auto listPart = listWidget->createListPart();
        QString listStr = listPart.getListString();

        QClipboard * clipboard = QGuiApplication::clipboard();

        clipboard->setText(listStr);

        QMessageBox msg(this);
        msg.setText("List copied to clipboard");
        msg.setWindowTitle("Success");
        msg.exec();

    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to print");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}

bool MainWindow::writeHTML_Legacy()
{
    QString filename = QFileDialog::getSaveFileName(this, "save list", QDir::currentPath(),"HTML (*.html)");

    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        auto listObj = listWidget->createListPart();

        QString stub;

        std::string htmlString = listPrinter_Legacy::getHTML(listObj, launchData);

        QByteArray bytes = htmlString.c_str();

        QTextStream istream(&file);

        istream << bytes;

        file.close();

        return true;
    }
    else return false;
}

bool MainWindow::writeHTML_Short()
{
    QString filename = QFileDialog::getSaveFileName(this, "save list", QDir::currentPath(),"HTML (*.html)");

    QFile file(filename);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        auto listObj = listWidget->createListPart();

        QString stub;

        std::string htmlString = listPrinter_Short::getHTML(listObj, launchData);

        QByteArray bytes = htmlString.c_str();

        QTextStream istream(&file);

        istream << bytes;

        file.close();

        return true;
    }
    else return false;
}


void MainWindow::on_actionFleet_List_triggered()
{
    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        if (writeHTML_Legacy())
        {
            QMessageBox msg(this);
            msg.setText("Fleet written to HTML file");
            msg.setWindowTitle("Success");
            msg.exec();
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Cannot write list file");
            msg.setWindowTitle("Error");
            msg.exec();
        }

    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to export");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}

// checks is the user is okay with doing an action if their list is invalid
bool MainWindow::checkListValidity()
{
    if (listWidget->checkValid())
        return true;
    {
        confirmDialog msg(this);
        msg.setMsg("One or more list validty checks has failed, print/save anyways?");
        int r = msg.exec();

        if (r == QDialog::Accepted)
            return true;
        else
            return false;

    }
}


void MainWindow::on_actionCompact_Fleet_List_triggered()
{
    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        if (writeHTML_Short())
        {
            QMessageBox msg(this);
            msg.setText("Fleet written to HTML file");
            msg.setWindowTitle("Success");
            msg.exec();
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Cannot write list file");
            msg.setWindowTitle("Error");
            msg.exec();
        }

    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to export");
        msg.setWindowTitle("Error");
        msg.exec();
    }

}


void MainWindow::on_actionSave_Compressed_triggered()
{
    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;


        if (saveCompressedListToFile())
        {

        }
        else
        {
            QMessageBox msg(this);
            msg.setText("Couldn't open save target for writing");
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to save");
        msg.exec();
    }
}


void MainWindow::on_actionLoad_compressed_triggered()
{
    if (loadCompressedListFromFile())
    {
        // (-:
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("Couldn't open load target for reading");
        msg.exec();
    }
}

bool MainWindow::loadCompressedListFromFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Select QFleet List", QDir::currentPath(),getExtensionFilter(fileType_listData()));

    QByteArray bytes;

    if (decompressor::readCompressedFile(bytes, filename))
    {
        // if a list is already loaded, delete it
        if (listWidget)
        {
            delete listWidget;
        }

        QJsonParseError err;

        QJsonDocument jsonData = QJsonDocument::fromJson(bytes, &err);

        QJsonObject wrapperObj = jsonData.object();

        QClipboard * clip = QGuiApplication::clipboard();
        QString str(bytes.constData());
        clip->setText(str);

        try
        {
            if (wrapperObj.contains(fileType_listData()))
            {
                QFleet_List list(wrapperObj[fileType_listData()].toObject());


                drawGUIFromListPart(list);
            }
            else
            {
                throw std::invalid_argument("Invalid File Type");
            }
        }
        catch (std::invalid_argument err)
        {
            QMessageBox msg(this);
            msg.setText(QString("File read Error! %1").arg(err.what()));
            msg.setWindowTitle("Load Error");
            msg.exec();
            return false;
        }
    }
    else return false;

    return true;
}

bool MainWindow::saveCompressedListToFile()
{
    QFleet_List newList = listWidget->createListPart();

    // save dialog goes here

    QString filename = QFileDialog::getSaveFileName(this, "Save List", QDir::currentPath(),getExtensionFilter(fileType_listData()));

    QJsonObject json = newList.toJson();

    QJsonObject wrapperObj;

    wrapperObj.insert(fileType_listData(), json);

    QJsonDocument jsonDoc(wrapperObj);

    QByteArray bytes = jsonDoc.toJson(QJsonDocument::Indented);

    return compressor::writeCompressedFile(bytes, filename);

}


void MainWindow::on_actionProfile_Cards_triggered()
{
    if (!listWidget.isNull())
    {
        if (!checkListValidity())
            return;

        if (drawProfileCards())
        {
            QMessageBox msg(this);
            msg.setText("Profile card images written to directory");
            msg.setWindowTitle("Success");
            msg.exec();
        }
        else
        {
            QMessageBox msg(this);
            msg.setText("One or more cards files could not be opened for writing");
            msg.setWindowTitle("Error");
            msg.exec();
        }
    }
    else
    {
        QMessageBox msg(this);
        msg.setText("No List Loaded to print");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}

void MainWindow::setSelectionLabels(const QString str)
{
    if (str.isEmpty())
    {
        ui->selectedShipLabel->setText("No Selected Ship");
        ui->selectedShipNameLabel->setVisible(false);
    }
    else if (str.isEmpty() && !selectedShip.has_value())
    {
        ui->selectedShipLabel->setText(str);
        ui->selectedShipNameLabel->setVisible(false);
    }
    else
    {
        ui->selectedShipLabel->setText("Selected Ship:");
        ui->selectedShipNameLabel->setVisible(true);
        ui->selectedShipNameLabel->setText(str);
    }
}

void MainWindow::slotShipSet(QFleet_Ship_Fleet& ship)
{
    selectedShip = ship;

    setSelectionLabels(ship.name);
}

void MainWindow::slotShipReset(const QString str)
{
    selectedShip.reset();

    setSelectionLabels(str);
}


void MainWindow::on_actionFleetbuilder_triggered()
{
    QMessageBox msg(this);
    msg.setWindowTitle("Build");
    msg.setText("Build Date: " + QString(__DATE__));
    msg.exec();
}


void MainWindow::on_actionShip_Data_triggered()
{
    QMessageBox msg(this);

    QString dateStr = dataDateStr;

    QString versionStr = dataVersionStr;

    if (dateStr.isEmpty())
        dateStr = "???";

    if (versionStr.isEmpty())
        versionStr = "???";

    QString str = QString("Stats version %1 - encode date %2").arg(versionStr,dateStr);
    msg.setText(str);

    msg.setWindowTitle("Ship Data Info");

    msg.exec();
}

