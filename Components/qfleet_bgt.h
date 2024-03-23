#ifndef QFLEET_BGT_H
#define QFLEET_BGT_H

#include "qft_enum.h"



enum class bgt
{
    PF=0,
    LN=1,
    VG=2,
    FL=3
};

inline uint qHash(bgt key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}


// the type of battlegroup
class QFleet_BGT : public qft_enum<QFleet_BGT, bgt>
{
    friend class qft_enum<QFleet_BGT, bgt>;

public:
    QFleet_BGT(const QString set) : qft_enum<QFleet_BGT, bgt>(set)
    {
    }

    QFleet_BGT(const bgt set) : qft_enum<QFleet_BGT, bgt>(set)
    {
    }

    QFleet_BGT()
    {
    }

    QString toLongString() const
    {
        if (val)
            return e2ls.value(*val);
        else
        {
            qFatal("Opened empty enum instance");
            return "REEEEE!";
        }
    }

    QString toLongStringBase() const
    {
        if (val)
            return e2lbs.value(*val);
        else
        {
            qFatal("Opened empty enum instance");
            return "REEEEE!";
        }
    }

    // get a numerical index 0,1,2,3:PF,LN,VG,FL
    unsigned int convertToIndex() const
    {
        if (val)
        {
            switch (*val)
            {
            case bgt::PF:

                return 0;
                break;

            case bgt::LN:

                return 1;
                break;

            case bgt::VG:

                return 2;
                break;

            case bgt::FL:

                return 3;
                break;
            }
        }
        else
        {
            qFatal("Opened empty enum instance");
            return 0;
        }

        return 0;
    }

protected:


    bgt impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const bgt in) const
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_PF,val_LN,val_VG,val_FL};
    }



private:

    const static QString val_PF;
    const static QString val_LN;
    const static QString val_VG;
    const static QString val_FL;

    const static QString val_long_PF;
    const static QString val_long_LN;
    const static QString val_long_VG;
    const static QString val_long_FL;

    const static QString val_lb_L;
    const static QString val_lb_M;
    const static QString val_lb_H;
    const static QString val_lb_SH;

    const static QHash<QString, bgt> s2e;
    const static QHash<bgt, QString> e2s;
    const static QHash<bgt, QString> e2ls;
    const static QHash<bgt, QString> e2lbs;
};


#endif // QFLEET_BGT_H
