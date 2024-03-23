#ifndef QFLEET_GROUP_H
#define QFLEET_GROUP_H


#include "../Components/qft_component.h"
#include "qfleet_cost.h"
#include "../Components/qfleet_ship_fleet.h"

// this object is only used for loading/saving/printing, not manipulated on the fly
class QFleet_Group : public qft_component<QFleet_Group>
{
    friend class qft_component<QFleet_Group>;

public:
    QFleet_Group(QJsonObject);

    QFleet_Group(const QFleet_Ship_Fleet&);

    // set information

    void setCostInfo(unsigned int num, unsigned int admiral);

    // data

    unsigned int getNumber() const;
    QFleet_Cost getCost() const;
    unsigned int getAdmiral() const;
    QFleet_Ship_Fleet getShip() const;

    QString getListString();

    void purgeAdmiral();
    
protected:

    QFleet_Cost cost;

    unsigned int number;

    unsigned int admiral;

    QFleet_Ship_Fleet ship;

    void admiralAdjust();

    const static QString label;
    const static QString field_cost;
    const static QString field_ship;
    const static QString field_number;
    const static QString field_admiral;


    void impl_toJson(QJsonObject&);
};

#endif // QFLEET_GROUP_H
