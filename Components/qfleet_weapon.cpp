#include "qfleet_weapon.h"

const QString QFleet_Weapon::field_arc="arc";
const QString QFleet_Weapon::field_lock="lock";
const QString QFleet_Weapon::field_attacks="attacks";
const QString QFleet_Weapon::field_damage="damage";
const QString QFleet_Weapon::field_specials="specials";

QFleet_Weapon::QFleet_Weapon(const QString setName) : qft_component<QFleet_Weapon>(setName), lock(QFleet_Lock()), facing(QFleet_Arc())
{

}

QFleet_Weapon::QFleet_Weapon() : qft_component<QFleet_Weapon>("new weapon"), lock(QFleet_Lock()), facing(QFleet_Arc())
{

}

QFleet_Weapon::QFleet_Weapon(QJsonObject in) : qft_component<QFleet_Weapon>(in.value(field_name).toString())
{
    enumFromJson(in, field_arc, facing);
    enumFromJson(in, field_lock, lock);
    fieldFromJson(in, field_attacks, attacks);
    fieldFromJson(in, field_damage, damage);
    fieldFromJson(in, field_specials, specials);

}

void QFleet_Weapon::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_attacks, attacks);
    fieldToJson(json, field_damage, damage);
    fieldToJson(json, field_specials, specials);
    enumToJson(json, field_arc, facing);
    enumToJson(json, field_lock, lock);
}

QString QFleet_Weapon::getSpecialString() const
{
    QString str;

    for (auto& special : specials)
    {
        str.append(special);

        if (special != specials.back())
            str.append(", ");
    }

    return str;
}

void QFleet_Weapon::weaponArrayToJson(QJsonObject& json, const QString field, QVector<QFleet_Weapon>& vec)
{
    QJsonArray namesArray;
    QJsonArray lockArray;
    QJsonArray attacksArray;
    QJsonArray damageArray;
    QJsonArray arcArray;
    QJsonArray specialArray;

    for (auto& weapon : vec)
    {
        namesArray.append(weapon.name);
        lockArray.append(weapon.lock.toString());
        attacksArray.append(weapon.attacks);
        damageArray.append(weapon.damage);
        arcArray.append(weapon.facing.toString());

        QJsonArray specials;

        for (auto& str : weapon.specials)
            specials.append(str);

        specialArray.append(specials);
    }

    QJsonObject weaponArrayObj;

    weaponArrayObj.insert(field_name, namesArray);
    weaponArrayObj.insert(field_lock, lockArray);
    weaponArrayObj.insert(field_attacks, attacksArray);
    weaponArrayObj.insert(field_damage, damageArray);
    weaponArrayObj.insert(field_arc, arcArray);
    weaponArrayObj.insert(field_specials, specialArray);

    json.insert(field, weaponArrayObj);
}
void QFleet_Weapon::weaponArrayFromJson(QJsonObject& json, const QString field, QVector<QFleet_Weapon>& vec)
{
    if (json.contains(field))
    {
        auto weaponArrayObj = json.value(field).toObject();

        auto count = weaponArrayObj.value(field_name).toArray().size();

        for (int i = 0; i < count ; i++)
        {
            QJsonObject indexObj;

            indexObj.insert(field_name, weaponArrayObj.value(field_name).toArray().at(i));
            indexObj.insert(field_lock, weaponArrayObj.value(field_lock).toArray().at(i));
            indexObj.insert(field_attacks, weaponArrayObj.value(field_attacks).toArray().at(i));
            indexObj.insert(field_damage, weaponArrayObj.value(field_damage).toArray().at(i));
            indexObj.insert(field_arc, weaponArrayObj.value(field_arc).toArray().at(i));
            indexObj.insert(field_specials, weaponArrayObj.value(field_specials).toArray().at(i));

            vec.push_back(QFleet_Weapon(indexObj));
        }

    }
    else
    {
        qFatal("No field found");
    }
}


