#ifndef LISTPRINTER_FUNCTIONS_H
#define LISTPRINTER_FUNCTIONS_H

#include "NLTemplate.h"
#include "../ListParts/qfleet_list.h"
#include "../Components/qfleet_launchasset.h"


class listprinter_functions
{
public:
    listprinter_functions() = delete;

    static void fillListHeader(NL::Template::Block&, const QFleet_List&);

    static void fillShip(NL::Template::Block&, const size_t index, const QFleet_Ship_Fleet&);

    static void fillWeaponTable(NL::Template::Block&, const QVector<QFleet_Weapon>&);

    static void fillLaunchTable(NL::Template::Block&, const QVector<QFleet_LaunchProfile>&);

    static void fillLaunchAssets(NL::Template::Block&, const QVector<QFleet_LaunchAsset>&);

    static QVector<QFleet_LaunchAsset> filterLaunchAssets(const QVector<QFleet_LaunchAsset> *, QMap<QString,QFleet_Ship_Fleet>&);

    static std::string getTimeStamp();
};

#endif // LISTPRINTER_FUNCTIONS_H
