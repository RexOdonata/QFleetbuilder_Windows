#ifndef QFLW_LIST_H
#define QFLW_LIST_H

#include "limitwidget.h"

#include <QWidget>
#include <QPointer>

#include "../Components/qfleet_faction.h"
#include "../ListParts/qfleet_cost.h"


#include "qflw_battlegroup.h"

#include "../ListParts/qfleet_list.h"


namespace Ui {
class QFLW_List;
}

class QFLW_List : public QWidget
{
    Q_OBJECT

public:
    explicit QFLW_List(QWidget *parent = nullptr, std::optional<QFleet_List> = {});
    ~QFLW_List();

    void setFaction(QFleet_Faction);

    void setPointsLimit(unsigned int);

    void updateHeader();

    void updateCost();

    void removeCard(QFLW_Battlegroup *);

    QWidget * getMainWindowPtr() const;

    unsigned int getBGN(QFleet_BGT) const;

    QFleet_List createListPart() const;

    bool checkValid() const;

signals:



public slots:

    void slotAdmiralSet(QFLW_Group *);

    void slotAdmiralDeleted();

    void slotCardDuplicated(QFleet_Battlegroup);


private slots:
    void on_addPF_Button_clicked();

    void on_addLN_Button_clicked();

    void on_addVG_Button_clicked();

    void on_addFL_Button_clicked();




private:
    Ui::QFLW_List *ui;

    // FXs


    void addBGT(QFleet_BGT);

    void removeBGT(QFleet_BGT);

    void setupWidgets();

    // update launch/point displays based on current value
    void setListLimits();

    // count types of battlegroup cards
    void updateCardLimits();


    void updateValidityLabels();


    bool checkMinimumcards() const;

    QString getCardRequirementLabels() const;


    // UI ELEMENTS

    limitWidget * pointsStatusWidget;

    limitWidget * launchStatusWidget;

    limitWidget * pfStatusWidget;

    limitWidget * lnStatusWidget;

    limitWidget * vgStatusWidget;

    limitWidget * flStatusWidget;

    QVector<QPointer<QFLW_Battlegroup>> cards;


    // DATA ELEMENTS

    const QWidget * mainWindowPtr;

    std::optional<QFleet_Faction> listFaction;

    QFleet_Cost cost;

    unsigned int maxBattleGroups = 0;

    unsigned int pointsLimit = 0;

    unsigned int launchLimit = 0;

    const static std::array<unsigned int, 12> cardLimitMatrix;

    std::optional<QFLW_Group *> admiralGroup = {};

    // allowed/actual
    unsigned int allowedL=0;
    unsigned int allowedM=0;
    unsigned int allowedH=0;
    unsigned int allowedSH=0;

    unsigned int countL=0;
    unsigned int countM=0;
    unsigned int countH=0;
    unsigned int countSH=0;

};

#endif // QFLW_LIST_H
