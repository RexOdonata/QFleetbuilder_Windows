#include "qfleet_cost.h"

const QString QFleet_Cost::field_SR="SR";
const QString QFleet_Cost::field_points="points";
const QString QFleet_Cost::field_LC="LC";

const QString QFleet_Cost::label="cost";

QFleet_Cost::QFleet_Cost(QJsonObject in) : qft_component<QFleet_Cost>(in.value(field_name).toString())
{
    fieldFromJson(in, field_LC, LC);
    fieldFromJson(in, field_points, points);
    fieldFromJson(in, field_SR, SR);
}

QFleet_Cost::QFleet_Cost(const QString setName) :
    qft_component<QFleet_Cost>(setName),
    points(0), LC(0), SR(0)
{
}

QFleet_Cost::QFleet_Cost(const QFleet_Ship_Fleet& srcShip) :
    qft_component<QFleet_Cost>(srcShip.name + " cost"),
    points(srcShip.points),
    SR(srcShip.tonnage.getIntValue()),
    LC(0)

{
    for (auto& launchProfile : srcShip.launch)
    {
        if (launchProfile.getStrike())
            this->LC += launchProfile.getCount();
    }
}

void QFleet_Cost::impl_toJson(QJsonObject& json)
{
    fieldToJson(json, field_LC, LC);
    fieldToJson(json, field_points, points);
    fieldToJson(json, field_SR, SR);
}

void QFleet_Cost::operator+(const QFleet_Cost & obj)
{
    this->SR += obj.SR;
    this->LC += obj.LC;
    this->points += obj.points;
}

void QFleet_Cost::zero()
{
    this->SR = 0;
    this->LC = 0;
    this->points = 0;
}

void QFleet_Cost::operator=(const QFleet_Cost& obj)
{
    this->SR = obj.SR;
    this->LC = obj.LC;
    this->points = obj.points;
}
