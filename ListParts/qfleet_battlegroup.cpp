#include "qfleet_battlegroup.h"

const QString QFleet_Battlegroup::label="Battlegroup";
const QString QFleet_Battlegroup::field_groups="groups";
const QString QFleet_Battlegroup::field_cost="cost";
const QString QFleet_Battlegroup::field_type="type";

QFleet_Battlegroup::QFleet_Battlegroup(QJsonObject in) :
    qft_component<QFleet_Battlegroup>(in.value(field_name).toString()),
    type(in[field_type].toString()),
    cost(in[field_cost].toObject())
{
    fieldFromJson(in, field_groups, groups);
    fieldFromJson(in, field_cost, cost);
    enumFromJson(in, field_type, type);

    updateCost();
}


QFleet_Battlegroup::QFleet_Battlegroup(QString setName, QFleet_BGT type) : qft_component<QFleet_Battlegroup>(setName),
    type(type),
    cost(QFleet_Cost("battlegroupCost"))
{
    // creating an empty group
}

void QFleet_Battlegroup::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_groups, groups);
    fieldToJson(json, field_cost, cost);
    enumToJson(json, field_type, type);
}

QVector<QFleet_Group> QFleet_Battlegroup::getGroups() const
{
    return groups;
}

void QFleet_Battlegroup::updateCost()
{
    this->cost.zero();

    // sum costs of battlegroups
    for (auto groupPtr : groups)
    {
        cost + groupPtr.getCost();
    }
}

QFleet_Cost QFleet_Battlegroup::getCost() const
{
    return this->cost;
}

void QFleet_Battlegroup::addGroup(const QFleet_Group& newGroup)
{
    groups.push_back(newGroup);
}

QFleet_BGT QFleet_Battlegroup::getType() const
{
    return type;
}

QString QFleet_Battlegroup::getListString()
{
    QString nameStr = this->name;

    nameStr.append(", ");

    nameStr.append(QString::number(this->cost.SR));

    nameStr.append(" SR");

    for (auto& group : groups)
    {
        QString groupStr = "\r\t\t";

        groupStr.append(group.getListString());

        nameStr.append(groupStr);
    }

    return nameStr;
}

void QFleet_Battlegroup::purgeAdmiral()
{
    for (auto& group : groups)
    {
        if (group.getAdmiral())
            group.purgeAdmiral();
    }
}

bool QFleet_Battlegroup::hasMultigroup()
{
    std::vector<QString> strs;

    for (auto& group : groups)
    {
        strs.push_back(group.getShip().name);
    }

    auto strs2 = strs;

    std::sort(strs.begin(), strs.end());

    auto last = std::unique(strs.begin(), strs.end());

    strs.erase(last,strs.end());

    if (strs2.size() == strs.size())
        return false;
    else
        return true;

}

void QFleet_Battlegroup::reduceGroups()
{
    // count how many of each ship there is in the entire battlegroup and if any has an admiral
    QMap<QString, unsigned int> countMap;
    QMap<QString, QFleet_Ship_Fleet> shipMap;

    QString admiral = "";
    unsigned int admiralLevel=0;

    for (auto& group : groups)
    {
        if (countMap.contains(group.getShip().name))
        {
            countMap[group.getShip().name]+=group.getNumber();
        }
        else
        {
            countMap.insert(group.getShip().name, group.getNumber());
            shipMap.insert(group.getShip().name, group.getShip());
        }

        if (group.getAdmiral())
        {
            admiral = group.getShip().name;
            admiralLevel=group.getAdmiral();
        }

    }

    // build new groups

    this->groups.clear();

    for (auto& ngs : shipMap)
    {
        QFleet_Group ng(ngs);

        auto AV = 0;

        if (ngs.name == admiral)
            AV = admiralLevel;

        ng.setCostInfo(countMap.value(ngs.name), AV);

        this->groups.push_back(ng);
    }

    updateCost();
}
