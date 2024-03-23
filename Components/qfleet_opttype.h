#ifndef QFLEET_OPTTYPE_H
#define QFLEET_OPTTYPE_H

#include "qft_enum.h"

enum class optType
{
    WEAPONS=0,
    LAUNCH=1,
    STAT=2,
    SPECIAL=3
};

inline uint qHash(optType key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}

class QFleet_OptType : public qft_enum<QFleet_OptType, optType>
{
    friend class qft_enum<QFleet_OptType, optType>;

public:
    QFleet_OptType() : qft_enum<QFleet_OptType, optType>()
    {

    }

    QFleet_OptType(const QString set) : qft_enum<QFleet_OptType, optType>(set)
    {
    }

    QFleet_OptType(const optType set) : qft_enum<QFleet_OptType, optType>(set)
    {
    }

protected:

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_weapon,val_launch,val_stat,val_special};
    }

    optType impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const optType in) const
    {
        return e2s[in];
    }

private:

    const static QString val_weapon;
    const static QString val_launch;
    const static QString val_stat;
    const static QString val_special;

    const static QHash<QString, optType> s2e;
    const static QHash<optType, QString> e2s;

};

#endif // QFLEET_OPTTYPE_H
