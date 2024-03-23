#include "qfleet_ship_shipyard.h"


const QString QFleet_Ship_Shipyard::field_factions="factions";
const QString QFleet_Ship_Shipyard::field_options="options";
const QString QFleet_Ship_Shipyard::field_maxOptions="maxOptions";
const QString QFleet_Ship_Shipyard::field_minOptions="minOptions";
const QString QFleet_Ship_Shipyard::field_maxBroadsides="maxBroadsides";


QFleet_Ship_Shipyard::QFleet_Ship_Shipyard (const QString setName) : QFleet_Ship(setName)
{

}

QFleet_Ship_Shipyard::QFleet_Ship_Shipyard () : QFleet_Ship("newShip")
{

}

QFleet_Ship_Shipyard::QFleet_Ship_Shipyard(QJsonObject in) : QFleet_Ship(in)
{

    enumFromJson(in, field_factions, factions);
    fieldFromJson(in, field_options, options);

    fieldFromJson(in,field_maxOptions,maxOptions);
    fieldFromJson(in,field_minOptions,minOptions);
    fieldFromJson(in,field_maxBroadsides,maxBroadsides);
}



void QFleet_Ship_Shipyard::impl_toJson(QJsonObject& in)
{

    enumToJson(in, field_factions, factions);
    fieldToJson(in, field_options, options);

    fieldToJson(in, field_maxOptions, maxOptions);
    fieldToJson(in, field_minOptions, minOptions);
    fieldToJson(in, field_maxBroadsides, maxBroadsides);
}

void QFleet_Ship_Shipyard::shipArrayToJson(QJsonObject& json, const QString field, QVector<QFleet_Ship_Shipyard>& vec)
{
    QJsonArray namesArray;
    QJsonArray pointsArray;
    QJsonArray scanArray;
    QJsonArray signatureArray;
    QJsonArray altSigArray;
    QJsonArray thrustArray;
    QJsonArray hullArray;
    QJsonArray armorArray;
    QJsonArray passiveArray;
    QJsonArray pdArray;
    QJsonArray groupLArray;
    QJsonArray groupHArray;
    QJsonArray tonnageArray;
    QJsonArray specialsArray;
    QJsonArray uniqueSpecialArray;
    QJsonArray weaponArray;
    QJsonArray launchArray;
    QJsonArray admiralDiscountArray;
    QJsonArray optionsArray;
    QJsonArray factionsArray;
    QJsonArray maxOptionsArray;
    QJsonArray minOptionsArray;
    QJsonArray maxBroadsidesArray;


    for (auto ship : vec)
    {
        namesArray.append(ship.name);

        pointsArray.append(QJsonValue((int)ship.points));

        scanArray.append(QJsonValue((int)ship.scan));

        signatureArray.append(QJsonValue((int)ship.signature));

        altSigArray.append(QJsonValue((int)ship.altSig));

        thrustArray.append(QJsonValue((int)ship.thrust));

        hullArray.append(QJsonValue((int)ship.hull));

        armorArray.append(QJsonValue(ship.armor.toString()));

        passiveArray.append(QJsonValue(ship.passive.toString()));

        pdArray.append(QJsonValue((int)ship.PD));

        groupLArray.append(QJsonValue((int)ship.groupL));

        groupHArray.append(QJsonValue((int)ship.groupH));

        tonnageArray.append(QJsonValue(ship.tonnage.toString()));

        QJsonArray specials;

        for (auto& str : ship.specialRules)
            specials.append(str);

        specialsArray.append(specials);

        uniqueSpecialArray.append(ship.uniqueSpecial);

        // resuing functions for convinience but stripping out the arrays to save text in the output

        QJsonObject weaponObj;
        QFleet_Weapon::weaponArrayToJson(weaponObj, field_weapons, ship.weapons);
        weaponArray.append(weaponObj[field_weapons]);

        QJsonObject launchObj;
        fieldToJson(launchObj, field_launch, ship.launch);
        launchArray.append(launchObj[field_launch]);

        admiralDiscountArray.append(QJsonValue((int)ship.admiralDiscount));

        QJsonObject optionsObj;
        fieldToJson(optionsObj, field_options, ship.options);
        optionsArray.append(optionsObj[field_options]);

        QJsonObject factionsObj;
        enumToJson(factionsObj, field_factions, ship.factions);
        factionsArray.append(factionsObj[field_factions]);

        maxOptionsArray.append(QJsonValue((int)ship.maxOptions));

        minOptionsArray.append(QJsonValue((int)ship.minOptions));

        maxBroadsidesArray.append(QJsonValue((int)ship.maxBroadsides));

    }

    QJsonObject shipArrayObj;
    shipArrayObj.insert(field_name, namesArray);
    shipArrayObj.insert(field_points,pointsArray);
    shipArrayObj.insert(field_scan,scanArray);
    shipArrayObj.insert(field_thrust,thrustArray);
    shipArrayObj.insert(field_signature,signatureArray);
    shipArrayObj.insert(field_altsig,altSigArray);
    shipArrayObj.insert(field_hull,hullArray);
    shipArrayObj.insert(field_armor,armorArray);
    shipArrayObj.insert(field_passive,passiveArray);
    shipArrayObj.insert(field_PD,pdArray);
    shipArrayObj.insert(field_groupL,groupLArray);
    shipArrayObj.insert(field_groupH,groupHArray);
    shipArrayObj.insert(field_tonnage,tonnageArray);
    shipArrayObj.insert(field_special,specialsArray);
    shipArrayObj.insert(field_uniqueSpecial,uniqueSpecialArray);
    shipArrayObj.insert(field_weapons,weaponArray);
    shipArrayObj.insert(field_launch,launchArray);
    shipArrayObj.insert(field_admiralDiscount,admiralDiscountArray);
    shipArrayObj.insert(field_options,optionsArray);
    shipArrayObj.insert(field_factions,factionsArray);
    shipArrayObj.insert(field_maxOptions,maxOptionsArray);
    shipArrayObj.insert(field_minOptions,minOptionsArray);
    shipArrayObj.insert(field_maxBroadsides,maxBroadsidesArray);

    json.insert(field, shipArrayObj);

}
void QFleet_Ship_Shipyard::shipArrayFromJson(QJsonObject& json, const QString field, QVector<QFleet_Ship_Shipyard>& vec)
{
    if (json.contains(field))
    {
        auto shipArrayObj = json.value(field).toObject();

        auto count = shipArrayObj.value(field_name).toArray().size();

        for (int index=0; index < count; index++)
        {
            QJsonObject indexObj;

            indexObj.insert(field_name, shipArrayObj.value(field_name).toArray().at(index));
            indexObj.insert(field_points, shipArrayObj.value(field_points).toArray().at(index));
            indexObj.insert(field_scan, shipArrayObj.value(field_scan).toArray().at(index));
            indexObj.insert(field_signature, shipArrayObj.value(field_signature).toArray().at(index));
            indexObj.insert(field_altsig, shipArrayObj.value(field_altsig).toArray().at(index));
            indexObj.insert(field_thrust, shipArrayObj.value(field_thrust).toArray().at(index));
            indexObj.insert(field_hull, shipArrayObj.value(field_hull).toArray().at(index));
            indexObj.insert(field_armor, shipArrayObj.value(field_armor).toArray().at(index));
            indexObj.insert(field_passive, shipArrayObj.value(field_passive).toArray().at(index));
            indexObj.insert(field_PD, shipArrayObj.value(field_PD).toArray().at(index));
            indexObj.insert(field_groupL, shipArrayObj.value(field_groupL).toArray().at(index));
            indexObj.insert(field_groupH, shipArrayObj.value(field_groupH).toArray().at(index));
            indexObj.insert(field_tonnage, shipArrayObj.value(field_tonnage).toArray().at(index));
            indexObj.insert(field_special, shipArrayObj.value(field_special).toArray().at(index));
            indexObj.insert(field_uniqueSpecial, shipArrayObj.value(field_uniqueSpecial).toArray().at(index));
            indexObj.insert(field_weapons, shipArrayObj.value(field_weapons).toArray().at(index));
            indexObj.insert(field_launch, shipArrayObj.value(field_launch).toArray().at(index));
            indexObj.insert(field_admiralDiscount, shipArrayObj.value(field_admiralDiscount).toArray().at(index));
            indexObj.insert(field_options, shipArrayObj.value(field_options).toArray().at(index));
            indexObj.insert(field_factions, shipArrayObj.value(field_factions).toArray().at(index));
            indexObj.insert(field_maxOptions, shipArrayObj.value(field_maxOptions).toArray().at(index));
            indexObj.insert(field_minOptions, shipArrayObj.value(field_minOptions).toArray().at(index));
            indexObj.insert(field_maxBroadsides, shipArrayObj.value(field_maxBroadsides).toArray().at(index));

            vec.push_back(QFleet_Ship_Shipyard(indexObj));
        }
    }
    else
    {
        qFatal("No field found");
    }
}
