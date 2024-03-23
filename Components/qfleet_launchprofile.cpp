#include "qfleet_launchprofile.h"


const QString QFleet_LaunchProfile::field_count="count";
const QString QFleet_LaunchProfile::field_strike="strike";
const QString QFleet_LaunchProfile::field_limited="limited";
const QString QFleet_LaunchProfile::field_assets="assets";

QFleet_LaunchProfile::QFleet_LaunchProfile(const QString setName) : qft_component<QFleet_LaunchProfile>(setName)
{

}

QFleet_LaunchProfile::QFleet_LaunchProfile() : qft_component<QFleet_LaunchProfile>("newLP")
{

}

QFleet_LaunchProfile::QFleet_LaunchProfile(QJsonObject in) : qft_component<QFleet_LaunchProfile>(in.value(field_name).toString())
{
    fieldFromJson(in, field_assets, assetNames);
    fieldFromJson(in, field_count, count);
    fieldFromJson(in, field_limited, limited);
    fieldFromJson(in, field_strike, strike);
}

void QFleet_LaunchProfile::impl_toJson(QJsonObject& json)
{
    fieldToJson(json,field_assets, assetNames);
    fieldToJson(json, field_count, count);
    fieldToJson(json, field_limited, limited);
    fieldToJson(json, field_strike, strike);
}

void QFleet_LaunchProfile::setCount(const unsigned int setCount)
{
    count = setCount;
}

void QFleet_LaunchProfile::setLimited(const unsigned int set)
{
    limited = set;
}

void QFleet_LaunchProfile::setStrike(const bool set)
{
    strike = set;
}


// fuse multiple string-names into a single string seperated by &s
void QFleet_LaunchProfile::setAssetNames(QVector<QString>& set)
{
    assetNames.clear();

    assetNames = set;
}

QVector<QString> QFleet_LaunchProfile::getAssetNames() const
{
    return assetNames;
}

QString QFleet_LaunchProfile::getLimString() const
{
    if (limited)
        return QString("%1").arg(QString::number(limited));
    else
        return "-";
}

QString QFleet_LaunchProfile::getDisplayName() const
{
    QString output;

    if (assetNames.size() == 2)
    {
        bool f1 = assetNames.front().contains("Fighters");
        bool f2 = assetNames.back().contains("Fighters");

        bool b1 = assetNames.front().contains("Bombers");
        bool b2 = assetNames.back().contains("Bombers");

        if ((f1 && b2) || (f2 && b1))
        {
            return "Fighters & Bombers";
        }
    }

    for (auto strItr = assetNames.begin(); strItr != assetNames.end(); strItr++)
    {
        output.append(*strItr);

        if (strItr + 1 != assetNames.end())
            output.append(" & ");
    }

    return output;
}


