#include "qfleet_armor.h"

const QString QFleet_Armor::val_2 = "2+";
const QString QFleet_Armor::val_3 = "3+";
const QString QFleet_Armor::val_4 = "4+";
const QString QFleet_Armor::val_5 = "5+";
const QString QFleet_Armor::val_6 = "6+";
const QString QFleet_Armor::val_n = "-";


const QHash<armor,QString> QFleet_Armor::e2s =
    {
    {armor::Arm2, val_2},
    {armor::Arm3, val_3},
    {armor::Arm4, val_4},
    {armor::Arm5, val_5},
    {armor::Arm6, val_6},
    {armor::none, val_n}
};

const QHash<QString, armor> QFleet_Armor::s2e =
    {
        {val_2, armor::Arm2},
        {val_3, armor::Arm3},
        {val_4, armor::Arm4},
        {val_5, armor::Arm5},
        {val_6, armor::Arm6},
        {val_n, armor::none}
};
