#ifndef QFU_SPECIALRULES_H
#define QFU_SPECIALRULES_H

#include <QString>
#include <QVector>

class qfu_specialRules
{
public:
    qfu_specialRules();

    const QVector<QString> weaponRules;
    const QVector<QString> shipRules;
    const QVector<QString> launchRules;

    static QVector<QString> populateWeaponRules();
    static QVector<QString> populateShipRules();
    static QVector<QString> populateLaunchRules();

};

#endif // QFU_SPECIALRULES_H
