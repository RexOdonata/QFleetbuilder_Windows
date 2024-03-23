#ifndef QFLEET_WEAPON_H
#define QFLEET_WEAPON_H

#include "qfleet_lock.h"
#include "qfleet_arc.h"
#include "qft_component.h"

class QFleet_Weapon : public qft_component<QFleet_Weapon>
{

    friend class qft_component<QFleet_Weapon>;

public:
    QFleet_Weapon(const QString);

    QFleet_Weapon(QJsonObject);

    QFleet_Weapon();

    // VARS

    QFleet_Lock lock;
    QString attacks;
    QString damage;
    QFleet_Arc facing;
    QVector<QString> specials;

    QString getSpecialString() const;

    static void weaponArrayToJson(QJsonObject&, const QString, QVector<QFleet_Weapon>&);
    static void weaponArrayFromJson(QJsonObject&, const QString, QVector<QFleet_Weapon>&);

protected:

    // STRINGS

    const static QString field_lock;
    const static QString field_attacks;
    const static QString field_damage;
    const static QString field_arc;
    const static QString field_specials;


    // FX

    void impl_toJson(QJsonObject& json);



};

#endif // QFLEET_WEAPON_H
