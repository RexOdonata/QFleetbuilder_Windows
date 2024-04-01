#include "qfleet_data.h"

const QString QFleet_Data::field_launchData="launchData";
const QString QFleet_Data::field_shipData="shipData";
const QString QFleet_Data::field_date="date";
const QString QFleet_Data::field_version="version";

QFleet_Data::QFleet_Data(QJsonObject& json) :
    qft_component<QFleet_Data>("QFleet Source Data")
{
    QFleet_Ship_Shipyard::shipArrayFromJson(json, field_shipData, shipData);

    fieldFromJson(json, field_launchData, launchData);

    dateStr = getOptFieldStr(json, field_date);

    versionStr = getOptFieldStr(json, field_version);

}

QFleet_Data::QFleet_Data() :
    qft_component<QFleet_Data>("QFleet Source Data")
{

}

QFleet_Data::QFleet_Data(const QString date, const QString version) :
    qft_component<QFleet_Data>("QFleet Source Data"), dateStr(date), versionStr(version)
{

}

QString QFleet_Data::getOptFieldStr(QJsonObject &json, const QString str)
{
    if (json.contains(str))
        return json.value(str).toString();
    else
        return "";
}

QString QFleet_Data::getVersionStr() const
{
    return versionStr;
}

QString QFleet_Data::getDateStr() const
{
    return dateStr;
}

void QFleet_Data::impl_toJson(QJsonObject& json)
{

    QFleet_Ship_Shipyard::shipArrayToJson(json, field_shipData, shipData);

    fieldToJson(json, field_launchData, launchData);

    fieldToJson(json, field_date, dateStr);

    fieldToJson(json, field_version, versionStr);
}
