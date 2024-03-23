#ifndef QFLEET_FACTION_H
#define QFLEET_FACTION_H



#include "qft_enum.h"


enum class faction
{
    UCM=0,
    SCOURGE=1,
    PHR=2,
    SHALTARI=3,
    RESISTANCE=4
};

inline uint qHash(faction key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}


class QFleet_Faction : public qft_enum<QFleet_Faction, faction>
{
    friend class qft_enum<QFleet_Faction, faction>;

public:
    QFleet_Faction(const QString set) : qft_enum<QFleet_Faction, faction>(set)
    {

    }

    QFleet_Faction(const faction set) : qft_enum<QFleet_Faction, faction>(set)
    {

    }

    QFleet_Faction()
    {

    }


protected:

    faction impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const faction in) const
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_ucm, val_scourge, val_phr, val_shaltari, val_resistance};
    }

private:

    const static QString val_ucm;
    const static QString val_scourge;
    const static QString val_phr;
    const static QString val_shaltari;
    const static QString val_resistance;

    const static QHash<QString, faction> s2e;
    const static QHash<faction, QString> e2s;
};

inline bool operator==(const QFleet_Faction& A, const QFleet_Faction& B)
{
    if ( A.getVal() ==B.getVal())
        return true;
    else
        return false;
}


#endif // QFleet_Faction_H
