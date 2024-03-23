#ifndef QFLEET_LAUNCHPROFILE_H
#define QFLEET_LAUNCHPROFILE_H

#include "qft_component.h"

// Represents a launch profile element of ship stats.
// Does not contain the actual launch stats

class QFleet_LaunchProfile : public qft_component<QFleet_LaunchProfile>
{
    friend class qft_component<QFleet_LaunchProfile>;

public:
    QFleet_LaunchProfile(const QString setName);

    QFleet_LaunchProfile(QJsonObject in);

    QFleet_LaunchProfile();

    void setCount(const unsigned int);

    void setStrike(const bool);

    void setLimited(const unsigned int set);

    void setAssetNames(QVector<QString>&);


    inline bool getStrike() const
    {
        return strike;
    }

    inline unsigned int getCount() const
    {
        return count;
    }

    inline unsigned int getLimited() const
    {
        return limited;
    }

    QVector<QString> getAssetNames() const;

    QString getDisplayName() const;

    QString getLimString() const;



protected:

    // VARS
    unsigned int count = 0;
    bool strike = false;
    unsigned int limited = 0;

    QVector<QString> assetNames;

    const static QString field_count;
    const static QString field_strike;
    const static QString field_limited;
    const static QString field_assets;

     //FXs

    void impl_toJson(QJsonObject& json);

};

#endif // QFLEET_LAUNCHPROFILE_H
