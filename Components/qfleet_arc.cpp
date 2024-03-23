#include "qfleet_arc.h"

const QString QFleet_Arc::val_FN = "FN";
const QString QFleet_Arc::val_F = "F";
const QString QFleet_Arc::val_FS = "F/S";
const QString QFleet_Arc::val_FSl = "F/S(l)";
const QString QFleet_Arc::val_FSr = "F/S(r)";
const QString QFleet_Arc::val_FSR = "F/S/R";
const QString QFleet_Arc::val_R = "S(r)";
const QString QFleet_Arc::val_L = "S(l)";

const QHash<arc, QString> QFleet_Arc::e2s =
    {
    {arc::FN, val_FN},
    {arc::F, val_F},
    {arc::FS, val_FS},
    {arc::FSr, val_FSr},
    {arc::FSl, val_FSl},
    {arc::FSR, val_FSR},
    {arc::L, val_L},
    {arc::R, val_R}
};

const QHash<QString,arc> QFleet_Arc::s2e =
    {
        {val_FN, arc::FN},
        {val_F, arc::F},
        {val_FS, arc::FS},
        {val_FSr, arc::FSr},
        {val_FSl, arc::FSl},
        {val_FSR, arc::FSR },
        {val_L, arc::L},
        {val_R, arc::R}
};
