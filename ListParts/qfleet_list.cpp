#include "qfleet_list.h"


const QString QFleet_List::field_cards="cards";
const QString QFleet_List::field_cost="cost";
const QString QFleet_List::field_pointsLimit="pointsLimit";
const QString QFleet_List::field_faction="faction";
const QString QFleet_List::field_valid="valid";



QFleet_List::QFleet_List(QJsonObject json) :
    qft_component<QFleet_List>(json.value(field_name).toString()), cost(QFleet_Cost("Cost"))
{
    enumFromJson(json, field_faction, listFaction);
    fieldFromJson(json, field_cards, cards);
    fieldFromJson(json, field_pointsLimit, pointsLimit);
    fieldFromJson(json, field_cost, cost);
    fieldFromJson(json, field_valid, validity);



    updateCost();
}

QFleet_List::QFleet_List(const QString setName, QFleet_Faction setFaction, unsigned int setLimit, bool valid) :
    qft_component<QFleet_List>(setName), cost(QFleet_Cost("listCost")),
    listFaction(setFaction), pointsLimit(setLimit), validity(valid)

{
    if (this->name.isEmpty())
        name = QString("Unnamed %1 fleet").arg(listFaction.toString());
}

void QFleet_List::impl_toJson(QJsonObject& json)
{
    enumToJson(json, field_faction, listFaction);
    fieldToJson(json, field_cards, cards);
    fieldToJson(json, field_pointsLimit, pointsLimit);
    fieldToJson(json, field_cost, cost);
    fieldToJson(json, field_valid, validity);
}

// updates cost and included groups
void QFleet_List::updateCost()
{
    QFleet_Cost nc("nc");

    for (auto& element : cards)
    {
        element.updateCost();
        nc + element.getCost();
    }

    cost = nc;
}

void QFleet_List::addCard(QFleet_Battlegroup& newCard)
{
    cards.push_back(newCard);
}



QVector<QFleet_Battlegroup> QFleet_List::getCards() const
{
    return cards;
}


unsigned int QFleet_List::getPointsLimit() const
{
    return pointsLimit;
}

unsigned int QFleet_List::getLaunchLimit() const
{
    if (pointsLimit < 1000)
    {
        return 10;
    }
    else if (pointsLimit < 2000)
    {
        return 15;
    }
    else if (pointsLimit < 3001)
    {
        return 20;
    }
    else
    {
        qFatal("List size too big!");
    }
}

faction QFleet_List::getFaction() const
{
    return listFaction.getVal();
}

bool QFleet_List::getValid() const
{
    return validity;
}

QFleet_Cost QFleet_List::getCost() const
{
    return cost;
}

QString QFleet_List::getListString()
{
    auto ptsStr = QString::number(this->getCost().points);

    auto facStr = QFleet_Faction(this->getFaction()).toString();

    QString nameStr = QString("%1, %2 pts %3").arg(this->name, ptsStr, facStr);


    for (auto& card : cards)
    {

        QString cardStr = "\r\t";

        cardStr.append(card.getListString());

        nameStr.append(cardStr);

    }

    return nameStr;
}
