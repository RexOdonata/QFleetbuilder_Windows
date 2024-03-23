#include "qfleet_opttype.h"


const QString QFleet_OptType::val_weapon ="weapon";
const QString QFleet_OptType::val_launch ="launch";
const QString QFleet_OptType::val_stat ="stat";
const QString QFleet_OptType::val_special ="special";

const QHash<QString, optType> QFleet_OptType::s2e =
{
    {QFleet_OptType::val_weapon, optType::WEAPONS},
    {QFleet_OptType::val_launch, optType::LAUNCH},
    {QFleet_OptType::val_stat, optType::STAT},
    {QFleet_OptType::val_special, optType::SPECIAL},
};

const QHash<optType, QString> QFleet_OptType::e2s =
    {
        {optType::WEAPONS, QFleet_OptType::val_weapon},
        {optType::LAUNCH, QFleet_OptType::val_launch},
        {optType::STAT, QFleet_OptType::val_stat},
        {optType::SPECIAL, QFleet_OptType::val_special}
    };
