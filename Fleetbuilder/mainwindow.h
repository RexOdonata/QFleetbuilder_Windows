#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shipselect.h"

#include "../Components/qfleet_ship_shipyard.h"

#include <QPointer>

#include "qflw_list.h"
#include "qflw_battlegroup.h"

#include "../Components/qfleet_launchasset.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void slotShipPull(QFLW_Battlegroup *);

    void slotShipSet(QFleet_Ship_Fleet&);

    void slotShipReset(const QString);


private slots:
    void on_actionNew_triggered();   

    void on_actionLoad_triggered();

    void on_shipMenuButton_clicked();

    void on_actionSave_triggered();

    void on_actionStrategy_Cards_triggered();

    void on_actionSimple_List_triggered();

    void on_actionFleet_List_triggered();

    void on_actionCompact_Fleet_List_triggered();

    void on_actionSave_Compressed_triggered();

    void on_actionLoad_compressed_triggered();

    void on_actionProfile_Cards_triggered();

private:
    Ui::MainWindow *ui;

    // UI ELEMENTS
    QPointer<shipSelect> shipSelectDialog;


    QPointer<QFLW_List> listWidget;


    // VARS

    std::optional<QFleet_Faction> faction;

    unsigned int pointsLimit;

    QMap<QString,QFleet_Ship_Shipyard> allShipData;
    QVector<QFleet_LaunchAsset> launchData;

    std::optional<QFleet_Ship_Fleet> selectedShip;

    // FXs


    void drawGUIFromListPart(const QFleet_List&);

    // UTILITY FXs

    void loadShipData();

    bool loadMapFromJsonFile(QWidget * parentWindow);

    bool loadListFromFile();

    bool saveListToFile();

    bool loadCompressedListFromFile();

    bool saveCompressedListToFile();

    bool drawStrategyCards();

    bool drawProfileCards();

    bool writeHTML_Legacy();

    bool writeHTML_Short();

    bool checkListValidity();

    void setSelectionLabels(const QString);



};
#endif // MAINWINDOW_H
