#include "qfleet_data.h"

const QString QFleet_Data::field_launchData="launchData";
const QString QFleet_Data::field_shipData="shipData";

QFleet_Data::QFleet_Data(QJsonObject& json) : qft_component<QFleet_Data>("QFleet Source Data")
{
    QFleet_Ship_Shipyard::shipArrayFromJson(json, field_shipData, shipData);

    fieldFromJson(json, field_launchData, launchData);
}

QFleet_Data::QFleet_Data() : qft_component<QFleet_Data>("QFleet Source Data")
{

}


void QFleet_Data::impl_toJson(QJsonObject& json)
{

    QFleet_Ship_Shipyard::shipArrayToJson(json, field_shipData, shipData);

    fieldToJson(json, field_launchData, launchData);
}
