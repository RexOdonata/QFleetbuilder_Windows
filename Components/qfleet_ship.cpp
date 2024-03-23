#include "qfleet_ship.h"

const QString QFleet_Ship::field_points = "points";
const QString QFleet_Ship::field_scan = "scan";
const QString QFleet_Ship::field_signature = "signature";
const QString QFleet_Ship::field_thrust = "thrust";
const QString QFleet_Ship::field_hull = "hull";
const QString QFleet_Ship::field_armor = "armor";
const QString QFleet_Ship::field_passive = "passive";
const QString QFleet_Ship::field_PD = "PD";
const QString QFleet_Ship::field_groupL = "groupL";
const QString QFleet_Ship::field_groupH = "groupH";
const QString QFleet_Ship::field_tonnage = "tonnage";
const QString QFleet_Ship::field_special = "special";
const QString QFleet_Ship::field_weapons = "weapons";
const QString QFleet_Ship::field_launch = "launch";


QFleet_Ship<T>::QFleet_Ship(QJsonObject in) : qft_component<QFleet_Ship>(in.value(field_name()).toString())
{
    fieldFromJson(in, field_points, points);
    fieldFromJson(in, field_scan, scan);
    fieldFromJson(in,field_signature,signature);
    fieldFromJson(in,field_thrust,thrust);
    fieldFromJson(in,field_hull,hull);
    fieldFromJson(in, field_armor, armor);
    fieldFromJson(in, field_passive, passive);
    fieldFromJson(in,field_PD,PD);
    fieldFromJson(in,field_groupL,groupL);
    fieldFromJson(in,field_groupH,groupH);
    fieldFromJson(in, field_tonnage, tonnage);
    fieldFromJson(in, field_special, specialRules);
    fieldFromJson(in, field_weapons, weapons);
    fieldFromJson(in, field_launch, launch);

}

QFleet_Ship::QFleet_Ship(const QString setName) : qft_component<QFleet_Ship>(setName)
{

}

void QFleet_Ship::ShipToJson(QJsonObject& json)
{
    fieldToJson(json, field_points, points);
    fieldToJson(json, field_scan,scan);
    fieldToJson(json, field_signature,signature);
    fieldToJson(json, field_thrust,thrust);
    fieldToJson(json, field_hull,hull);
    enumToJson(json, field_armor, armor);
    enumToJson(json, field_passive, passive);
    fieldToJson(json,field_PD,PD);
    fieldToJson(json,field_groupL,groupL);
    fieldToJson(json,field_groupH,groupH);
    enumToJson(json, field_tonnage, tonnage);
    fieldToJson(json,field_special,specialRules);
    fieldToJson(json,field_weapons,weapons);
    fieldToJson(json,field_launch,launch);
}

void QFleet_Ship::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_points, points);
    fieldToJson(json, field_scan,scan);
    fieldToJson(json, field_signature,signature);
    fieldToJson(json, field_thrust,thrust);
    fieldToJson(json, field_hull,hull);
    enumToJson(json, field_armor, armor);
    enumToJson(json, field_passive, passive);
    fieldToJson(json,field_PD,PD);
    fieldToJson(json,field_groupL,groupL);
    fieldToJson(json,field_groupH,groupH);
    enumToJson(json, field_tonnage, tonnage);
    fieldToJson(json,field_special,specialRules);
    fieldToJson(json,field_weapons,weapons);
    fieldToJson(json,field_launch,launch);
}
