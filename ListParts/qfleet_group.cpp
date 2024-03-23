#include "qfleet_group.h"

const QString QFleet_Group::label="";
const QString QFleet_Group::field_cost="cost";
const QString QFleet_Group::field_ship="ship";
const QString QFleet_Group::field_number="number";
const QString QFleet_Group::field_admiral="admiral";

// creates a group with the given ship, but no admiral/cost/num info
QFleet_Group::QFleet_Group(const QFleet_Ship_Fleet& setShip) :
    qft_component<QFleet_Group>(setShip.name), cost(QFleet_Cost("GroupCost")),
    ship(setShip), number(0), admiral(0)
{

}

// updates cost based on number of ships in group and presence of admiral
void QFleet_Group::setCostInfo(unsigned int num, unsigned int setAdmiral)
{
    number = num;

    admiral = setAdmiral;

    QFleet_Cost shipCost(ship);

    for (int i = 0; i < num; i++)
        cost + shipCost;


    if (setAdmiral > 0 && ship.admiralCost(setAdmiral))
        cost.points += *ship.admiralCost(setAdmiral);

}

QFleet_Group::QFleet_Group(QJsonObject json) :
    qft_component<QFleet_Group>(json.value(field_name).toString()), cost(QFleet_Cost("GroupCost")),
    ship(json.value(field_ship).toObject())
{
    fieldFromJson(json, field_cost, cost);
    fieldFromJson(json, field_number, number);
    fieldFromJson(json, field_admiral, admiral);


}

void QFleet_Group::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_cost, cost);
    fieldToJson(json, field_ship, ship);
    fieldToJson(json, field_number, number);
    fieldToJson(json, field_admiral, admiral);
}


QFleet_Cost QFleet_Group::getCost() const
{
    return this->cost;
}

unsigned int QFleet_Group::getNumber() const
{
    return this->number;
}

unsigned int QFleet_Group::getAdmiral() const
{
    return admiral;
}

QFleet_Ship_Fleet QFleet_Group::getShip() const
{
    return ship;
}

void QFleet_Group::admiralAdjust()
{
    auto admiralPoints = ship.admiralCost(admiral);

    if (admiralPoints)
        cost.points +=  *admiralPoints;
}

QString QFleet_Group::getListString()
{
    QString numStr = "";
    if (this->number > 1)
    {
        numStr.append(QString::number(this->number));
        numStr.append("x");
    }
    else
        numStr.append("1");

    numStr.append(" ");

    numStr.append(this->ship.name);

    numStr.append("\r");

    if (this->admiral)
    {
        numStr.append("\t\t\t");
        numStr.append("Adm Lvl");
        numStr.append(QString::number(this->admiral));
        numStr.append("\r");
    }

    return numStr;
}

void QFleet_Group::purgeAdmiral()
{
    admiral = 0;
}
