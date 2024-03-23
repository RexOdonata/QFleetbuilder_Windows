#ifndef QFLEET_TONNAGE_H
#define QFLEET_TONNAGE_H



#include "qft_enum.h"
#include <QMap>
#include <optional>

#include "qfleet_bgt.h"

enum class tonnage
{
    L=0,
    L2=1,
    M=2,
    H=3,
    S=4,
    S2=5
};

inline uint qHash(tonnage key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}


class QFleet_Tonnage : public qft_enum<QFleet_Tonnage, tonnage>
{
    friend class qft_enum<QFleet_Tonnage, tonnage>;

public:
    QFleet_Tonnage(const QString set) : qft_enum<QFleet_Tonnage, tonnage>(set)
    {
    }

    QFleet_Tonnage(const tonnage set) : qft_enum<QFleet_Tonnage, tonnage>(set)
    {
    }

    unsigned int getIntValue() const
    {
        if (val)
            return e2u[*val];
        else
            return 0;
    }

    QFleet_Tonnage()
    {        
    }

    // convert raw tonnage to BGT
    QFleet_BGT convertToBGT() const
    {
        if (val)
        {
            switch (*val)
            {
            case tonnage::L:

                return QFleet_BGT(bgt::PF);
                break;

            case tonnage::L2:

                return QFleet_BGT(bgt::PF);
                break;

            case tonnage::M:

                return QFleet_BGT(bgt::LN);
                break;
            case tonnage::H:

                return QFleet_BGT(bgt::VG);
                break;
            case tonnage::S:

                return QFleet_BGT(bgt::FL);
                break;
            case tonnage::S2:

                return QFleet_BGT(bgt::FL);
                break;
            }
        }
        else
        {
            qFatal("Opened empty enum instance");
            return QFleet_BGT(bgt::PF);
        }

        return QFleet_BGT(bgt::PF);
    }

protected:

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_L,val_L2,val_M,val_H,val_S,val_S2};
    }

    tonnage impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const tonnage in) const
    {
        return e2s[in];
    }

private:

    const static QString val_L;
    const static QString val_L2;
    const static QString val_M;
    const static QString val_H;
    const static QString val_S;
    const static QString val_S2;

    const static QMap<QString, tonnage> s2e;
    const static QMap<tonnage, QString> e2s;
    const static QMap<tonnage, unsigned int> e2u;
};

#endif // QFLEET_TONNAGE_H
