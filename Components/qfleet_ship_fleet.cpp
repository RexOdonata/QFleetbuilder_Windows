#include "qfleet_ship_fleet.h"




QFleet_Ship_Fleet::QFleet_Ship_Fleet(QJsonObject in) : QFleet_Ship(in)
{

}

QFleet_Ship_Fleet::QFleet_Ship_Fleet (const QString setName) : QFleet_Ship(setName)
{

}

void QFleet_Ship_Fleet::impl_toJson(QJsonObject& in)
{

}

QString QFleet_Ship_Fleet::getArmorString() const
{
    QString str=this->armor.toString();

    if (this->passive.getVal() != armor::none)
    {
        str.append("/");
        str.append(this->passive.toString());
    }

    return str;
}

QString QFleet_Ship_Fleet::getSigString() const
{
    QString str = QString::number(this->signature);

    if (this->altSig > 0)
    {
        str.append("/");
        str.append(QString::number(this->altSig));
    }

    return str;
}

QString QFleet_Ship_Fleet::getGroupString() const
{
    QString str = QString::number(this->groupL);

    if (this->groupL != this->groupH)
    {
        str.append("-");
        str.append(QString::number(this->groupH));
    }

    return str;
}

QString QFleet_Ship_Fleet::getSpecialString() const
{
    QString str;

    for (auto& special : specialRules)
    {
        str.append(special);

        if (special != specialRules.back())
            str.append(", ");
    }

    return str;
}

std::optional<unsigned int> QFleet_Ship_Fleet::admiralCost(unsigned int level) const
{
    // return empty value if light - no admiral allowed
    // likewise an AV1 admiral isn't allowed
    if (this->tonnage.getIntValue() < 5)
        return {};
    else if (level == 0 || level == 1)
        return 0;
    // free admiral discount for UCM dreads
    else if (this->admiralDiscount == 5)
        return 0;
    else
    {
        std::array<unsigned int, 4> costs{20,40,80,100};
        unsigned int adjustedIndex = level - 2;

        unsigned int discountCounter = this->admiralDiscount;

        // decrement the cost of the admiral down one rank until it reaches base cost or the discount is expended
        while (discountCounter > 0 && adjustedIndex > 0)
        {
            adjustedIndex --;
            discountCounter --;
        }
        return costs[adjustedIndex];
    }
}
