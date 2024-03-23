#include "listprinter_functions.h"

#include <iomanip>


std::string listprinter_functions::getTimeStamp()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;

    oss<<std::put_time(&tm, "%d-%m-%Y %H-%M-%S");

    return oss.str();
}

void listprinter_functions::fillListHeader(NL::Template::Block& headerBlock, const QFleet_List& listObj)
{
    // set list name in header

    headerBlock.set("listName",listObj.name.toStdString());

    // set points fraction in header

    std::string pointsStr = QString::number(listObj.getCost().points).toStdString() + "/" + QString::number(listObj.getPointsLimit()).toStdString();

    headerBlock.set("listPoints",pointsStr);

    // set launch fraction in header

    std::string launchStr = QString::number(listObj.getCost().LC).toStdString() + "/" + QString::number(listObj.getLaunchLimit()).toStdString();

    headerBlock.set("listLaunch",launchStr);

    // set faction in header

    std::string factionStr = QFleet_Faction(listObj.getFaction()).toString().toStdString();

    headerBlock.set("listFaction",factionStr);

    // set creation time

    std::string timestampStr = getTimeStamp();

    headerBlock.set("listCreated",timestampStr);

    // set Validity Tag (NEEDS WORK!)

    std::string validStr = (listObj.getValid()) ? "True" : "FALSE!";

    headerBlock.set("listValid",validStr);
}

void listprinter_functions::fillShip(NL::Template::Block& shipsBlock, const size_t index, const QFleet_Ship_Fleet& ship)
{

    shipsBlock[index].set("shipPoints", QString::number(ship.points).toStdString());

    shipsBlock[index].set("shipName", ship.name.toStdString());

    shipsBlock[index].set("shipScan", QString::number(ship.scan).toStdString());

    shipsBlock[index].set("shipSignature", ship.getSigString().toStdString());

    shipsBlock[index].set("shipThrust", QString::number(ship.thrust).toStdString());

    shipsBlock[index].set("shipHull", QString::number(ship.hull).toStdString());

    shipsBlock[index].set("shipArmor", ship.getArmorString().toStdString());

    shipsBlock[index].set("shipPD", QString::number(ship.PD).toStdString());

    shipsBlock[index].set("shipGroup", ship.getGroupString().toStdString());

    shipsBlock[index].set("shipTonnage", ship.tonnage.toString().toStdString());

    shipsBlock[index].set("shipSpecial", ship.getSpecialString().toStdString());


    if (ship.uniqueSpecial.isEmpty())
    {
        shipsBlock[index].block("uniqueSpecialBlock").repeat(0);
    }
    else
    {
        shipsBlock[index].block("uniqueSpecialBlock").set("uniqueSpecial", ship.uniqueSpecial.toStdString());
    }

    NL::Template::Block& weaponRowBlock = shipsBlock[index].block("weaponRow");

    NL::Template::Block& launchTableBlock = shipsBlock[index].block("launchTable");

    fillWeaponTable(weaponRowBlock, ship.weapons);

    fillLaunchTable(launchTableBlock, ship.launch);
}

void listprinter_functions::fillWeaponTable(NL::Template::Block& weaponRowBlock, const QVector<QFleet_Weapon>& weapons)
{
    weaponRowBlock.repeat(weapons.size());

    for (int weaponIndex = 0; weaponIndex < weapons.size(); weaponIndex++)
    {
        auto weapon = weapons.at(weaponIndex);

        weaponRowBlock[weaponIndex].set("weaponName",weapon.name.toStdString());

        weaponRowBlock[weaponIndex].set("weaponArc",weapon.facing.toString().toStdString());

        weaponRowBlock[weaponIndex].set("weaponDamage",weapon.damage.toStdString());

        weaponRowBlock[weaponIndex].set("weaponAttack",weapon.attacks.toStdString());

        weaponRowBlock[weaponIndex].set("weaponLock",weapon.lock.toString().toStdString());

        weaponRowBlock[weaponIndex].set("weaponSpecial", weapon.getSpecialString().toStdString());
    }
}

QVector<QFleet_LaunchAsset> listprinter_functions::filterLaunchAssets(const QVector<QFleet_LaunchAsset> * srcAssets, QMap<QString,QFleet_Ship_Fleet>& srcShips)
{
    QMap<QString, bool> assetStrings;

    QMap<QString, QFleet_LaunchAsset> assetMap;

    for (auto& asset : *srcAssets)
    {
        assetMap.insert(asset.name, asset);
    }

    for (auto& ship : srcShips)
    {
        for (auto& lp : ship.launch)
        {
            for (auto laStr : lp.getAssetNames())
            {
                if (!assetStrings.contains(laStr))
                    assetStrings.insert(laStr, true);
            }
        }
    }

    QVector<QFleet_LaunchAsset> output;

    for (auto& laStr : assetStrings.keys())
    {
        output.push_back(assetMap.value(laStr));
    }

    return output;
}

void listprinter_functions::fillLaunchTable(NL::Template::Block& launchTableBlock, const QVector<QFleet_LaunchProfile>& launch)
{
    if (launch.size() == 0)
    {
        launchTableBlock.disable();
        launchTableBlock.block("launchRow").disable();
    }
    else
    {

        launchTableBlock.block("launchRow").repeat(launch.size());

        for (int launchIndex = 0; launchIndex < launch.size(); launchIndex++)
        {
            auto lp = launch.at(launchIndex);

            launchTableBlock.block("launchRow")[launchIndex].set("launchName",lp.getDisplayName().toStdString());

            launchTableBlock.block("launchRow")[launchIndex].set("launchCount",QString::number(lp.getCount()).toStdString());

            std::string limStr = "-";

            if (lp.getLimited())
                limStr = QString::number(lp.getLimited()).toStdString();

            launchTableBlock.block("launchRow")[launchIndex].set("launchLimited",limStr);
        }
    }
}

void listprinter_functions::fillLaunchAssets(NL::Template::Block& assetTableBlock, const QVector<QFleet_LaunchAsset>& launchAssets)
{
    assetTableBlock.block("launchAssetRow").repeat(launchAssets.size());

    auto index = 0;
    for (auto& la : launchAssets)
    {
        NL::Template::Node& rowBlock = assetTableBlock.block("launchAssetRow")[index];

        rowBlock.set("assetName",la.getName().toStdString());

        rowBlock.set("assetThrust",std::to_string(la.thrust)+"\"");

        std::string pdstr="-";
        if (la.type.getVal()==assetType::fighter)
            pdstr = std::to_string(la.PD);
        rowBlock.set("assetPD",pdstr);

        std::string lockstr="-";
        if (la.type.getVal()==assetType::bomber || la.type.getVal()==assetType::torpedo)
            lockstr = la.lock.toString().toStdString();
        rowBlock.set("assetLock",lockstr);

        std::string attackstr="-";
        if (la.type.getVal()==assetType::bomber || la.type.getVal()==assetType::torpedo)
            attackstr = std::to_string(la.attacks);
        rowBlock.set("assetAttack",attackstr);

        std::string damagestr="-";
        if (la.type.getVal()==assetType::bomber || la.type.getVal()==assetType::torpedo)
            damagestr = std::to_string(la.damage);
        rowBlock.set("assetDamage",damagestr);

        rowBlock.set("assetSpecial", la.getSpecialString().toStdString());

        index++;
    }
}
