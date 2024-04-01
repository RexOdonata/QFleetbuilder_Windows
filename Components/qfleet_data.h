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

    QFleet_Data(const QString, const QString);

    QFleet_Data();

    QVector<QFleet_Ship_Shipyard> shipData;
    QVector<QFleet_LaunchAsset> launchData;

    QString getVersionStr() const;

    QString getDateStr() const;

protected:

    QString versionStr;

    QString dateStr;

    // STRINGS

    const static QString field_launchData;
    const static QString field_shipData;
    const static QString field_version;
    const static QString field_date;

    void impl_toJson(QJsonObject&);

    static QString getOptFieldStr(QJsonObject&, const QString);

};

#endif // QFLEET_DATA_H
