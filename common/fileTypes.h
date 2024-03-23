#ifndef FILETYPES_H
#define FILETYPES_H

#include <QString>

inline const QString fileType_listData()
{
    return "listData";
}


inline const QString fileType_launchData()
{
    return "launchData";
}

inline const QString fileType_shipData()
{
    return "shipData";
}

inline const QString getExtensionFilter(const QString in)
{
    if (in==fileType_listData())
        return "QFleet List (*.dfc)";
    else if (in==fileType_shipData())
        return "QFleet Ships (*.qfs)";
    else if (in==fileType_launchData())
        return "QFleet Launch (*.qfl)";
    else
        return "";
}

inline const QString getExtension(const QString in)
{
    if (in==fileType_listData())
        return "*.dfc";
    else if (in==fileType_shipData())
        return "*.qfs";
    else if (in==fileType_launchData())
        return "*.qfl";
    else
        return "";
}


#endif // FILETYPES_H
