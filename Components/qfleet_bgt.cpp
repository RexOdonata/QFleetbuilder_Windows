#include "qfleet_bgt.h"

const QString QFleet_BGT::val_PF="PF";
const QString QFleet_BGT::val_LN="LN";
const QString QFleet_BGT::val_VG="VG";
const QString QFleet_BGT::val_FL="FL";

const QString QFleet_BGT::val_long_PF="Pathfinder";
const QString QFleet_BGT::val_long_LN="Line";
const QString QFleet_BGT::val_long_VG="Vanguard";
const QString QFleet_BGT::val_long_FL="Flag";

const QString QFleet_BGT::val_lb_L="Light";
const QString QFleet_BGT::val_lb_M="Medium";
const QString QFleet_BGT::val_lb_H="Heavy";
const QString QFleet_BGT::val_lb_SH="SuperHeavy";

const QHash<bgt, QString> QFleet_BGT::e2s =
{
    {bgt::PF,val_PF},
    {bgt::LN,val_LN},
    {bgt::VG,val_VG},
    {bgt::FL,val_FL}
};

const QHash<bgt, QString> QFleet_BGT::e2ls =
{
        {bgt::PF,val_long_PF},
        {bgt::LN,val_long_LN},
        {bgt::VG,val_long_VG},
        {bgt::FL,val_long_FL}
};

const QHash<bgt, QString> QFleet_BGT::e2lbs =
    {
        {bgt::PF,val_lb_L},
        {bgt::LN,val_lb_M},
        {bgt::VG,val_lb_H},
        {bgt::FL,val_lb_SH}
};

const QHash<QString, bgt> QFleet_BGT::s2e =
    {
        {val_PF, bgt::PF},
        {val_LN, bgt::LN},
        {val_VG, bgt::VG},
        {val_FL, bgt::FL}
};
