#include "listprinter_short.h"

#include "listprinter_functions.h"


std::string listPrinter_Short::getHTML(const QFleet_List& listObj, const QVector<QFleet_LaunchAsset>& launchAssets)
{

    NL::Template::LoaderFile templateLoader;

    NL::Template::Template listTemplate(templateLoader);

    listTemplate.load("htmlTemplates/shortList.txt");

    NL::Template::Block& headerBlock = listTemplate.block("listHeader");

    // DRAW HEADER
    listprinter_functions::fillListHeader(headerBlock, listObj);

    // prepare data

    QMap<QString, QFleet_Ship_Fleet> shipMap;
    auto cards = listObj.getCards();

    // DRAW SIMPLE LIST TREE

    NL::Template::Block& listTreeBlock = listTemplate.block("listTree");

    listTreeBlock.block("battlegroupLine").repeat(cards.size());

    for (int cardIndex = 0; cardIndex < cards.size(); cardIndex++)
    {
        auto card = cards.at(cardIndex);

        listTreeBlock.block("battlegroupLine")[cardIndex].set("cardName",card.name.toStdString());
        listTreeBlock.block("battlegroupLine")[cardIndex].set("SR",QString::number(card.getCost().SR).toStdString());

        if (card.hasMultigroup())
            card.reduceGroups();

        auto groups = card.getGroups();

        NL::Template::Block& groupBlockRef = listTreeBlock.block("battlegroupLine")[cardIndex].block("groupLine");

        fillGroupLines(groupBlockRef, groups);

        // build present groups
        for (auto& group : groups)
            if (!shipMap.contains(group.getShip().name))
                shipMap.insert(group.name, group.getShip());

    }

    // DRAW SHIP PROFILES

    NL::Template::Block& shipsBlock = listTemplate.block("ship");

    shipsBlock.repeat(shipMap.size());

    auto index = 0;
    for (auto& ship : shipMap)
    {
        listprinter_functions::fillShip(shipsBlock,index,ship);

        index++;
    }

    // DRAW LAUNCH ASSET TABLE

    {

        NL::Template::Block& launchAssetBlock = listTemplate.block("launchAssets");

        auto launchVec = listprinter_functions::filterLaunchAssets(&launchAssets,shipMap);

        listprinter_functions::fillLaunchAssets(launchAssetBlock,launchVec);

    }


    std::stringbuf buffer;

    std::ostream sout(&buffer);

    listTemplate.render(sout);

    std::ostringstream oss;

    oss << buffer.str();

    return oss.str();
}



void listPrinter_Short::fillGroupLines(NL::Template::Block& block, const QVector<QFleet_Group>& groups)
{
    block.repeat(groups.size());

    for (int i = 0; i<groups.size(); i++)
    {
        auto group = groups.at(i);
        block[i].set("count",QString::number(group.getNumber()).toStdString());
        block[i].set("shipName",group.name.toStdString());

        QString admStr = "";

        if (group.getAdmiral())
            admStr=QString(" + Lv%1 admiral").arg(QString::number(group.getAdmiral()));

        block[i].set("admiral",admStr.toStdString());
    }
}
