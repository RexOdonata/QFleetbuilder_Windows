#ifndef QFLEET_STATID_H
#define QFLEET_STATID_H

#include "qft_enum.h"


// not putting armor in here because its an enum, not an int
enum class statID
{
    scan=0,
    sig=1,
    thrust=2,
    hull=3,
    PD=4
};

inline uint qHash(statID key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}

class QFleet_StatID : public qft_enum<QFleet_StatID, statID>
{
    friend class qft_enum<QFleet_StatID, statID>;

public:
    QFleet_StatID(const QString set) : qft_enum<QFleet_StatID, statID>(set)
    {

    }

    QFleet_StatID(const statID set) : qft_enum<QFleet_StatID, statID>(set)
    {

    }

    QFleet_StatID()
    {

    }

protected:

    statID impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const statID in) const
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_scan, val_sig, val_thrust, val_hull, val_PD};
    }

private:

    const static QString val_scan;
    const static QString val_sig;
    const static QString val_thrust;
    const static QString val_hull;
    const static QString val_PD;

    const static QHash<QString, statID> s2e;
    const static QHash<statID, QString> e2s;


};

#endif // QFLEET_STATID_H
