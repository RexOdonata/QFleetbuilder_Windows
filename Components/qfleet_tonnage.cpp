#include "qfleet_tonnage.h"

const QString QFleet_Tonnage::val_L = "L";
const QString QFleet_Tonnage::val_L2 = "L2";
const QString QFleet_Tonnage::val_M = "M";
const QString QFleet_Tonnage::val_H = "H";
const QString QFleet_Tonnage::val_S = "S";
const QString QFleet_Tonnage::val_S2 = "S2";

const QMap<QString, tonnage> QFleet_Tonnage::s2e =
{
    {val_L,     tonnage::L},
    {val_L2,    tonnage::L2},
    {val_M,     tonnage::M},
    {val_H,     tonnage::H},
    {val_S,     tonnage::S},
    {val_S2,    tonnage::S2}
};

const QMap<tonnage, QString> QFleet_Tonnage::e2s =
{
        {tonnage::L,    val_L},
        {tonnage::L2,   val_L2},
        {tonnage::M,    val_M},
        {tonnage::H,    val_H},
        {tonnage::S,    val_S},
        {tonnage::S2,   val_S2}
};

const QMap<tonnage, unsigned int> QFleet_Tonnage::e2u =
{
    {tonnage::L, 1},
    {tonnage::L2, 2},
    {tonnage::M, 5},
    {tonnage::H, 10},
    {tonnage::S, 15},
    {tonnage::S2, 30}
};
