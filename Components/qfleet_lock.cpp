#include "qfleet_lock.h"


const QString QFleet_Lock::val_2 = "2+";
const QString QFleet_Lock::val_3 = "3+";
const QString QFleet_Lock::val_4 = "4+";
const QString QFleet_Lock::val_5 = "5+";
const QString QFleet_Lock::val_6 = "6+";
const QString QFleet_Lock::val_x = "X+";

const QHash<lock,QString> QFleet_Lock::e2s =
    {
        {lock::lk2, val_2},
        {lock::lk3, val_3},
        {lock::lk4, val_4},
        {lock::lk5, val_5},
        {lock::lk6, val_6},
        {lock::lkX, val_x}
};

const QHash<QString, lock> QFleet_Lock::s2e =
    {
        {val_2, lock::lk2},
        {val_3, lock::lk3},
        {val_4, lock::lk4},
        {val_5, lock::lk5},
        {val_6, lock::lk6},
        {val_x, lock::lkX}
};
