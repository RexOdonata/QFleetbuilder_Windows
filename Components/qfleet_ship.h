#ifndef QFLEET_SHIP_H
#define QFLEET_SHIP_H

#include "qfleet_launchprofile.h"
#include "qfleet_tonnage.h"
#include "qfleet_weapon.h"
#include "qft_component.h"
#include "qfleet_armor.h"


// this is the base class for:
    // 1. (S)hipyard ship : the inputs to fleetbuilder
    // 2. (F)leet ship: an output object of fleetbuilder created to flatten a list into an output for printing, cards etc.

template<typename T>
class QFleet_Ship : public qft_component<QFleet_Ship<T>>
{
    friend class qft_component<QFleet_Ship<T>>;

public:
    QFleet_Ship(QJsonObject in) : qft_component<QFleet_Ship>(in.value(this->field_name).toString())
    {

    // specialization decode will already have been called

        this->fieldFromJson(in,   field_points, points);
        this->fieldFromJson(in,   field_scan, scan);
        this->fieldFromJson(in,   field_signature,signature);
        this->fieldFromJson(in,   field_altsig,altSig);
        this->fieldFromJson(in,   field_thrust,thrust);
        this->fieldFromJson(in,   field_hull,hull);
        this->enumFromJson(in,   field_armor, armor);
        this->enumFromJson(in,   field_passive, passive);
        this->fieldFromJson(in,   field_PD,PD);
        this->fieldFromJson(in,   field_groupL,groupL);
        this->fieldFromJson(in,   field_groupH,groupH);
        this->enumFromJson(in,   field_tonnage, tonnage);
        this->fieldFromJson(in,   field_special, specialRules);
        this->fieldFromJson(in,   field_uniqueSpecial, uniqueSpecial);
        QFleet_Weapon::weaponArrayFromJson(in,   field_weapons, weapons);
        this->fieldFromJson(in,   field_launch, launch);
        this->fieldFromJson(in,   field_admiralDiscount, admiralDiscount);
    }

    QFleet_Ship(QString setName) : qft_component<QFleet_Ship>(setName)
    {

    }
    // VARS

    unsigned int points;
    unsigned int scan;
    unsigned int signature;
    unsigned int altSig;
    unsigned int thrust;
    unsigned int hull;
    QFleet_Armor armor;
    QFleet_Armor passive;
    unsigned int PD;
    unsigned int groupL;
    unsigned int groupH;
    QFleet_Tonnage tonnage;
    QVector<QString> specialRules;
    QString uniqueSpecial;
    QVector<QFleet_Weapon> weapons;
    QVector<QFleet_LaunchProfile> launch;

    unsigned int admiralDiscount;


protected:
    // FXs

    void impl_toJson(QJsonObject& json)
    {
        this->fieldToJson(json,   field_points, points);
        this->fieldToJson(json,   field_scan,scan);
        this->fieldToJson(json,   field_signature,signature);
        this->fieldToJson(json,   field_altsig,altSig);
        this->fieldToJson(json,   field_thrust,thrust);
        this->fieldToJson(json,   field_hull,hull);
        this->enumToJson(json,   field_armor, armor);
        this->enumToJson(json,   field_passive, passive);
        this->fieldToJson(json,   field_PD,PD);
        this->fieldToJson(json,   field_groupL,groupL);
        this->fieldToJson(json,   field_groupH,groupH);
        this->enumToJson(json,   field_tonnage, tonnage);
        this->fieldToJson(json,   field_special,specialRules);
        this->fieldToJson(json,   field_uniqueSpecial, uniqueSpecial);
        QFleet_Weapon::weaponArrayToJson(json,   field_weapons,weapons);
        this->fieldToJson(json,   field_launch,launch);
        this->fieldToJson(json,   field_admiralDiscount,admiralDiscount);


        // call specialization encode
        static_cast<T*>(this)->impl_toJson(json);
    }    

    // STRINGS


    inline const static QString field_points = "points";
    inline const static QString field_scan = "scan";
    inline const static QString field_signature = "signature";
    inline const static QString field_altsig = "altSignature";
    inline const static QString field_thrust = "thrust";
    inline const static QString field_hull = "hull";
    inline const static QString field_armor = "armor";
    inline const static QString field_passive = "passive";
    inline const static QString field_PD = "PD";
    inline const static QString field_groupL = "groupL";
    inline const static QString field_groupH = "groupH";
    inline const static QString field_tonnage = "tonnage";
    inline const static QString field_special = "special";
    inline const static QString field_uniqueSpecial = "uniqueSpecial";
    inline const static QString field_weapons = "weapons";
    inline const static QString field_launch = "launch";
    inline const static QString field_admiralDiscount = "admiralDiscount";

};

#endif // QFLEET_SHIP_H
