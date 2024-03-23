#ifndef QFLEET_LOCK_H
#define QFLEET_LOCK_H

#include "qft_enum.h"


enum class lock
{
    lkX=0,
    lk2=1,
    lk3=2,
    lk4=3,
    lk5=4,
    lk6=5

};

inline uint qHash(lock key, uint seed)
{
    return qHash(static_cast<uint>(key),seed);
}

class QFleet_Lock : public qft_enum<QFleet_Lock, lock>
{
    friend class qft_enum<QFleet_Lock, lock>;

public:
    QFleet_Lock(const QString set) : qft_enum<QFleet_Lock, lock>(set)
    {
    }

    QFleet_Lock(const lock set) : qft_enum<QFleet_Lock, lock>(set)
    {
    }

    QFleet_Lock()
    {
    }

protected:

    lock impl_string_to_enum(const QString in) const
    {
        return s2e[in];
    }

    QString impl_enum_to_string(const lock in) const
    {
        return e2s[in];
    }

    QVector<QString> impl_getEnumStrings() const
    {
        return QVector<QString>{val_2,val_3,val_4,val_5,val_6,val_x};
       }

private:

    const static QString val_2;
    const static QString val_3;
    const static QString val_4;
    const static QString val_5;
    const static QString val_6;
    const static QString val_x;

    const static QHash<QString, lock> s2e;
    const static QHash<lock, QString> e2s;
};

#endif // QFLEET_TONNAGE_H
