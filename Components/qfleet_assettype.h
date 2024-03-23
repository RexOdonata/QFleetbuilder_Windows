#ifndef QFLEET_ASSETTYPE_H
#define QFLEET_ASSETTYPE_H

#include "qft_enum.h"
#include <QMap>

enum class assetType
{
    fighter=0,
    bomber=1,
    torpedo=2,
    drop=3
};

inline uint qHash(assetType key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}

class QFleet_AssetType : public qft_enum<QFleet_AssetType, assetType>
{
    friend class qft_enum<QFleet_AssetType, assetType>;

public:
    QFleet_AssetType(const QString set) : qft_enum<QFleet_AssetType, assetType>(set)
    {
    }

    QFleet_AssetType(const assetType set) : qft_enum<QFleet_AssetType, assetType>(set)
    {
    }

    QFleet_AssetType()
    {        
    }


protected:


    assetType impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const assetType in) const
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_fighter, val_bomber, val_torpedo, val_drop};
    }

private:

    const static QString val_fighter;
    const static QString val_bomber;
    const static QString val_torpedo;
    const static QString val_drop;

    const static QHash<QString, assetType> s2e;
    const static QHash<assetType, QString> e2s;

};

#endif // QFleet_AssetType_H
