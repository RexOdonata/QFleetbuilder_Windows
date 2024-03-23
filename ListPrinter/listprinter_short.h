#ifndef LISTPRINTER_SHORT_H
#define LISTPRINTER_SHORT_H

#include "../ListParts/qfleet_list.h"
#include "../Components/qfleet_launchasset.h"

#include "NLTemplate.h"


class listPrinter_Short
{

public:
    listPrinter_Short() = delete;

    static std::string getHTML(const QFleet_List&, const QVector<QFleet_LaunchAsset>&);

private:

    static std::string getTimeStamp();

    static void fillGroupLines(NL::Template::Block&, const QVector<QFleet_Group>&);

};

#endif // LISTPRINTER_SHORT_H
