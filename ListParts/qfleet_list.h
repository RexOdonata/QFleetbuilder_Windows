#ifndef QFLEET_LIST_H
#define QFLEET_LIST_H

#include "qfleet_battlegroup.h"
#include "../Components/qfleet_faction.h"

#include "../Components/qft_component.h"

// represent a fleet list saved to file or loaded from file, or for printing
class QFleet_List : public qft_component<QFleet_List>
{
    friend class qft_component<QFleet_List>;
public:
    QFleet_List(QJsonObject);

    // used during UI->object encoding
    QFleet_List(const QString, QFleet_Faction, unsigned int, bool valid);

    void addCard(QFleet_Battlegroup&);


    unsigned int getPointsLimit() const;

    unsigned int getLaunchLimit() const;

    faction getFaction() const;

    QFleet_Cost getCost() const;

    bool getValid() const;

    QVector<QFleet_Battlegroup> getCards() const;


    void updateCost();

    QString getListString();

protected:

    void impl_toJson(QJsonObject&);


private:

    unsigned int pointsLimit;

    QFleet_Faction listFaction;

    QFleet_Cost cost;

    QVector<QFleet_Battlegroup> cards;

    bool validity;

    const static QString field_pointsLimit;
    const static QString field_cost;
    const static QString field_cards;
    const static QString field_faction;
    const static QString field_valid;

};

#endif // QFLEET_LIST_H
