#ifndef QFLEET_DATA_H
#define QFLEET_DATA_H

#include "qft_component.h"

#include "qfleet_ship_shipyard.h"
#include "qfleet_launchasset.h"

// this is a special component used as the product from Shipyard to Fleetbuilder
class QFleet_Data : public qft_component<QFleet_Data>
{
    friend class qft_component<QFleet_Data>;
public:
    QFleet_Data(QJsonObject &json);

    QFleet_Data();

    QVector<QFleet_Ship_Shipyard> shipData;
    QVector<QFleet_LaunchAsset> launchData;

protected:

    // STRINGS

    const static QString field_launchData;
    const static QString field_shipData;

    void impl_toJson(QJsonObject&);



};

#endif // QFLEET_DATA_H
