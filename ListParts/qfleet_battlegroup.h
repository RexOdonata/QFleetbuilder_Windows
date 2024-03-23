#ifndef QFLEET_BATTLEGROUP_H
#define QFLEET_BATTLEGROUP_H

#include "../Components/qft_component.h"
#include "../Components/qfleet_bgt.h"
#include "qfleet_group.h"

class QFleet_Battlegroup : public qft_component<QFleet_Battlegroup>
{
    friend class qft_component<QFleet_Battlegroup>;

public:
    QFleet_Battlegroup(QJsonObject);

    QFleet_Battlegroup(const QString, const QFleet_BGT);
   
    // FXS

    void addGroup(const QFleet_Group&);

    // used to add a group during UI->object conversion
    QVector<QFleet_Group> getGroups() const;

    QFleet_Cost getCost() const;

    QFleet_BGT getType() const;

    void updateCost();

    QString getListString();

    void purgeAdmiral();

    void reduceGroups();

    // check whether group reduction is needed
    bool hasMultigroup();

protected:

    QFleet_BGT type;
    QFleet_Cost cost;

    QVector<QFleet_Group> groups;

    void impl_toJson(QJsonObject&);


    const static QString label;


    const static QString field_groups;
    const static QString field_cost;
    const static QString field_type;



};

#endif // QFLEET_BATTLEGROUP_H
