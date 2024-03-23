#include "listprinter_legacy.h"

#include "NLTemplate.h"

#include "listprinter_functions.h"



std::string listPrinter_Legacy::getHTML(const QFleet_List& listObj, const QVector<QFleet_LaunchAsset>& launchAssets)
{

    NL::Template::LoaderFile templateLoader;

    NL::Template::Template listTemplate(templateLoader);

    listTemplate.load("htmlTemplates/legacyList.txt");

    // DRAW HEADER

    NL::Template::Block& headerBlock = listTemplate.block("listHeader");

    listprinter_functions::fillListHeader(headerBlock, listObj);


    // START BATTLEGROUPS

    auto cards = listObj.getCards();

    listTemplate.block("battlegroupHeader").repeat(cards.size());

    QMap<QString,QFleet_Ship_Fleet> shipMap;

    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++)
    {
        auto card = cards.at(cardIndex);

        // check if the card has group profiles that can be compressed
        if (card.hasMultigroup())
            card.reduceGroups();

        // set header info for the battlegroup

        listTemplate.block("battlegroupHeader")[cardIndex].set("cardName",card.name.toStdString());

        listTemplate.block("battlegroupHeader")[cardIndex].set("cardSR",std::to_string(card.getCost().SR));

        // get a reference to to the current group block
        NL::Template::Block& groupProfiles = listTemplate.block("battlegroupHeader")[cardIndex].block("groupHeader");

        auto groups = card.getGroups();

        // fill out the group
        fillGroupBlocks(groupProfiles, groups);

        for (auto& group : groups)
        {
            if (!shipMap.contains(group.getShip().name))
                shipMap.insert(group.getShip().name, group.getShip());
        }

    }

    // DRAW LAUNCH ASSETS    

    {
        auto launchVec = listprinter_functions::filterLaunchAssets(&launchAssets, shipMap);

        NL::Template::Block& launchAssetBlock = listTemplate.block("launchAssets");

        listprinter_functions::fillLaunchAssets(launchAssetBlock,launchVec);

    }

    std::stringbuf buffer;

    std::ostream sout(&buffer);

    listTemplate.render(sout);

    std::ostringstream oss;

    oss << buffer.str();

    return oss.str();
}


void listPrinter_Legacy::fillGroupBlocks(NL::Template::Block& groupBlockRef, const QVector<QFleet_Group>& groups)
{
    groupBlockRef.repeat(groups.size());

    for (int groupIndex = 0; groupIndex < groups.size(); groupIndex++)
    {
        auto group = groups.at(groupIndex);

        groupBlockRef[groupIndex].set("count", std::to_string(group.getNumber()));

        groupBlockRef[groupIndex].set("shipName", group.getShip().name.toStdString());

        std::string admiralStr = "";

        if (group.getAdmiral())
        {
            admiralStr = "- Lvl ";
            admiralStr.append(std::to_string(group.getAdmiral()));
            admiralStr.append(" Admiral");
        }

        groupBlockRef[groupIndex].set("admiral", admiralStr);

        groupBlockRef[groupIndex].block("ship").repeat(1);

        listprinter_functions::fillShip(groupBlockRef[groupIndex].block("ship"), 0, group.getShip());
    }
}
