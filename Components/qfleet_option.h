#ifndef QFLEET_OPTION_H
#define QFLEET_OPTION_H
#include <memory>

#include "qft_component.h"

#include "qfleet_weapon.h"
#include "qfleet_launchprofile.h"
#include "qfleet_statid.h"
#include "qfleet_opttype.h"

class QFleet_Option : public qft_component<QFleet_Option>
{
    friend class qft_component<QFleet_Option>;

public:
    QFleet_Option(const QString);

    QFleet_Option(QJsonObject);

    QFleet_Option();

    // MANDATORY VARS

    QFleet_OptType type;

    bool broadside;
    bool oneOnly;

    unsigned int points;

    // OPT VARS

    std::shared_ptr<QVector<QFleet_Weapon>> weaponVecPtr = NULL;

    std::shared_ptr<QFleet_LaunchProfile> launchProfilePtr = NULL;

    std::shared_ptr<unsigned int> statBonusPtr = NULL;
    std::shared_ptr<QFleet_StatID> statTypePtr = NULL;

    std::shared_ptr<QVector<QString>> specialPtr = NULL;




private:


    // STRINGS
    const static QString field_weapons;
    const static QString field_launchProfile;
    const static QString field_specialRule;
    const static QString field_statBonus;
    const static QString field_broadside;
    const static QString field_oneOnly;
    const static QString field_statType;
    const static QString field_points;
    const static QString field_optType;

    // FX

    void impl_toJson(QJsonObject& json);



};

#endif // QFLEET_OPTION_H
