#ifndef QFLEET_SHIP_FLEET_H
#define QFLEET_SHIP_FLEET_H

#include "qfleet_ship.h"

// note that this component is no different from the base ship class, it just has some helper functions
// keeping these helper functions outside of the base class isn't super important but whatever

// this object is used to store actual ships existing in the fleet, linked to groups
class QFleet_Ship_Fleet : public QFleet_Ship<QFleet_Ship_Fleet>
{
    friend class QFleet_Ship<QFleet_Ship_Fleet>;

public:
    QFleet_Ship_Fleet(QJsonObject);

    QFleet_Ship_Fleet(const QString);


    QString getArmorString() const;

    QString getSigString() const;

    QString getGroupString() const;

    QString getSpecialString() const;

    // translates the desired admiral level to actual cost based on discount
    // returns no value on L ships
    std::optional<unsigned int> admiralCost(unsigned int) const;

protected:

    void impl_toJson(QJsonObject& json);

};

#endif // QFLEET_SHIP_FLEET_H
