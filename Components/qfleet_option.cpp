#include "qfleet_option.h"


const QString QFleet_Option::field_weapons="weapons";
const QString QFleet_Option::field_launchProfile="launchProfile";
const QString QFleet_Option::field_specialRule="specialRule";
const QString QFleet_Option::field_statBonus="statBonus";
const QString QFleet_Option::field_broadside="broadside";
const QString QFleet_Option::field_oneOnly="oneOnly";
const QString QFleet_Option::field_statType="statID";
const QString QFleet_Option::field_points="points";
const QString QFleet_Option::field_optType="optType";

QFleet_Option::QFleet_Option(const QString setName) : qft_component<QFleet_Option>(setName), type(QFleet_OptType())
{
    points = 0;
    broadside = false;
    oneOnly = false;
}

QFleet_Option::QFleet_Option() : qft_component<QFleet_Option>("newOption"), type(QFleet_OptType())
{
    points = 0;
    broadside = false;
    oneOnly = false;
}

QFleet_Option::QFleet_Option(QJsonObject in) : qft_component<QFleet_Option>
    (in.value(field_name).toString())
{
    fieldFromJson(in, field_broadside, broadside);
    fieldFromJson(in, field_oneOnly, oneOnly);
    enumFromJson(in, field_optType, type);
    fieldFromJson(in, field_points, points);

    optType lt = type.getVal();
    if (lt == optType::WEAPONS)
    {
        weaponVecPtr = std::make_shared<QVector<QFleet_Weapon>>();
        fieldFromJson(in, field_weapons, *weaponVecPtr);
    }
    else if (lt == optType::LAUNCH)
    {
        launchProfilePtr = std::make_shared<QFleet_LaunchProfile>();
        fieldFromJson(in, field_launchProfile, *launchProfilePtr);
    }
    else if (lt == optType::STAT)
    {
        statBonusPtr = std::make_shared<unsigned int>();
        statTypePtr= std::make_shared<QFleet_StatID>();

        fieldFromJson(in, field_statBonus, *statBonusPtr);
        enumFromJson(in, field_statType, *statTypePtr);
    }
    else if (lt == optType::SPECIAL)
    {
        specialPtr = std::make_shared<QVector<QString>>();
        fieldFromJson(in, field_specialRule, *specialPtr);
    }

}

void QFleet_Option::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_broadside, broadside);
    fieldToJson(json, field_oneOnly, oneOnly);
    enumToJson(json, field_optType, type);
    fieldToJson(json, field_points, points);

    optType lt = type.getVal();
    if (lt == optType::WEAPONS)
    {
        fieldToJson(json, field_weapons, *weaponVecPtr);
    }
    else if (lt == optType::LAUNCH)
    {
        fieldToJson(json,field_launchProfile,*launchProfilePtr);
    }
    else if (lt == optType::STAT)
    {
        fieldToJson(json,field_statBonus,*statBonusPtr);
        enumToJson(json,field_statType,*statTypePtr);
    }
    else if (lt == optType::SPECIAL)
    {
        fieldToJson(json,field_specialRule,*specialPtr);
    }
}
