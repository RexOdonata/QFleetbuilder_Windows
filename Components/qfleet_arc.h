#ifndef QFLEET_ARC_H
#define QFLEET_ARC_H

#include "qft_enum.h"


enum class arc
{
    FN=0,
    F=1,
    FS=2,
    FSl=3,
    FSr=4,
    FSR=5,
    L=6,
    R=7,
};

inline uint qHash(arc key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}

class QFleet_Arc : public qft_enum<QFleet_Arc, arc>
{
    friend class qft_enum<QFleet_Arc, arc>;

public:
    QFleet_Arc(const QString set) : qft_enum<QFleet_Arc, arc>(set)
    {

    }

    QFleet_Arc(const arc set) : qft_enum<QFleet_Arc, arc>(set)
    {

    }

    QFleet_Arc()
    {

    }


protected:

    arc impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const arc in) const
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_FN, val_F, val_FS, val_FSl, val_FSr, val_FSR, val_L, val_R};
    }

private:

    const static QString val_FN;
    const static QString val_F;
    const static QString val_FS;
    const static QString val_FSl;
    const static QString val_FSr;
    const static QString val_FSR;
    const static QString val_L;
    const static QString val_R;

    const static QHash<QString, arc> s2e;
    const static QHash<arc, QString> e2s;

};

#endif // QFLEET_ARC_H
