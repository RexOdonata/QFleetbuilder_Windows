#ifndef LISTPRINTER_LEGACY_H
#define LISTPRINTER_LEGACY_H

#include "NLTemplate.h"


#include "../ListParts/qfleet_list.h"
#include "../Components/qfleet_launchasset.h"

class listPrinter_Legacy
{
public:
    listPrinter_Legacy() = delete;

    static std::string getHTML(const QFleet_List&, const QVector<QFleet_LaunchAsset>&);

private:


    static void fillGroupBlocks(NL::Template::Block&, const QVector<QFleet_Group>&);



};

#endif // LISTPRINTER_LEGACY_H
