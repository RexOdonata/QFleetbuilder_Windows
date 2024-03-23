#include "qfleet_assettype.h"

const QString QFleet_AssetType::val_fighter="fighter";
const QString QFleet_AssetType::val_bomber="bomber";
const QString QFleet_AssetType::val_torpedo="torpedo";
const QString QFleet_AssetType::val_drop="drop";

const QHash<assetType, QString> QFleet_AssetType::e2s =
    {
    {assetType::fighter, val_fighter},
    {assetType::bomber, val_bomber},
    {assetType::torpedo, val_torpedo},
    {assetType::drop, val_drop}
};

const QHash<QString,assetType> QFleet_AssetType::s2e =
    {
        {val_fighter, assetType::fighter},
        {val_bomber, assetType::bomber},
        {val_torpedo, assetType::torpedo},
        {val_drop, assetType::drop}
};
