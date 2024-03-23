#include "qfleet_statid.h"

const QString QFleet_StatID::val_scan="scan";
const QString QFleet_StatID::val_sig="sig";
const QString QFleet_StatID::val_thrust="thrust";
const QString QFleet_StatID::val_hull="hull";
const QString QFleet_StatID::val_PD="PD";

const QHash<QString, statID> QFleet_StatID::s2e =
{
    {val_scan,statID::scan},
    {val_sig,statID::sig},
    {val_thrust,statID::thrust},
    {val_hull,statID::hull},
    {val_PD,statID::PD}
};

const QHash<statID, QString> QFleet_StatID::e2s =
    {
        {statID::scan,val_scan},
        {statID::sig,val_sig},
        {statID::thrust,val_thrust},
        {statID::hull,val_hull},
        {statID::PD,val_PD}
};

