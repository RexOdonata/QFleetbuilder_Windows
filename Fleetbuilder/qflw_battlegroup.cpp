#include "qflw_battlegroup.h"
#include "qjsondocument.h"
#include "ui_qflw_battlegroup.h"

#include "mainwindow.h"

#include "qflw_list.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>


const std::array<unsigned int, 16> QFLW_Battlegroup::groupLimitMatrix =
    {
        3,1,0,0,
        2,3,0,0,
        1,1,2,0,
        1,0,0,2
};

QWidget * QFLW_Battlegroup::getListPtr() const
{
    return (QWidget *)listWidgetPtr;
}

QFLW_Battlegroup::QFLW_Battlegroup(QWidget *parent, std::optional<QFleet_BGT> setType) :
    QWidget(parent),
    ui(new Ui::QFLW_Battlegroup),
    cost(QFleet_Cost("Card Cost")),
    type(*setType),
    listWidgetPtr(parent)
{
    ui->setupUi(this);


    QFLW_List * listPtr = (QFLW_List *)listWidgetPtr;
    MainWindow * mainWindowPtr = (MainWindow *) listPtr->getMainWindowPtr();


    QObject::connect(this, &QFLW_Battlegroup::querySelectedShip,
            mainWindowPtr , &MainWindow::slotShipPull);

    QObject::connect(this, &QFLW_Battlegroup::signalDuplicate, listPtr, &QFLW_List::slotCardDuplicated);


    ui->typeLabel->setText(type.toLongString());

    QString tempName = type.toLongString() + " " + QString::number((listPtr->getBGN(*setType)));

    ui->nameEdit->setText(tempName);

    refreshCostLabels();

    unsigned int index = setType.value().convertToIndex();

    {
    allowedL = groupLimitMatrix[4*index];
    allowedM = groupLimitMatrix[4*index + 1];
    allowedH = groupLimitMatrix[4*index + 2];
    allowedSH = groupLimitMatrix[4*index + 3];
    }

    updateGroupCounts();
    updateWarningLabels();


    this->setAttribute(Qt::WA_DeleteOnClose);
}

QString QFLW_Battlegroup::getName() const
{
    return ui->nameEdit->text();
}

unsigned int QFLW_Battlegroup::getcostNoAdmiral() const
{
    unsigned int output = this->cost.points;

    for (auto& group : groups)
    {
    output -= group->getAdmiralCost();
    }

    return output;
}

// update internal group counts
void QFLW_Battlegroup::updateGroupCounts()
{
    countSH = countH= countM = countL = 0;

    for (auto& group : groups)
    incrementTypeCounters(group->getShip().tonnage);

}

// sets warning labels as appropriate to current counts
void QFLW_Battlegroup::updateWarningLabels()
{
    {
        // too many groups
        unsigned int maxgroups = 3;
        if (this->type.getVal() == bgt::FL)
            maxgroups = 2;

        if (groups.size() > maxgroups)
        {
            QString labelStr = QString("! : Too many groups, max is %1").arg(QString::number(maxgroups));
            ui->grpfullWarnLabel->setText(labelStr);
            ui->grpfullWarnLabel->setVisible(true);
        }
        else
            ui->grpfullWarnLabel->setVisible(false);
    }

    {
        // minimum group warning
        if (!checkMandatory())
        {
            QString labelStr = QString("! : No mandatory %1 group").arg(type.toLongStringBase());
            ui->mingrpWarnLabel->setText(labelStr);
            ui->mingrpWarnLabel->setVisible(true);
        }
        else
        {
            ui->mingrpWarnLabel->setVisible(false);
        }
    }

    {
        // check against group lims
        if (!checkGroupLimits())
        {
            QString labelStr = getGroupLimwarnings();
            ui->grplimsWarnLabel->setText(QString("! : Too many %1 groups").arg(labelStr));
            ui->grplimsWarnLabel->setVisible(true);
            ui->trimGroupsButton->setVisible(true);
        }
        else
        {
            ui->grplimsWarnLabel->setVisible(false);
            ui->trimGroupsButton->setVisible(false);
        }
    }

}

// returns true if the battlegroup is valid
bool QFLW_Battlegroup::validityCheck() const
{
    if (ui->grplimsWarnLabel->isVisible() ||
        ui->mingrpWarnLabel->isVisible() ||
        ui->grpfullWarnLabel->isVisible())
        return false;
    else
        return true;
}

QString QFLW_Battlegroup::getGroupLimwarnings() const
{
    unsigned int index = type.convertToIndex();

    std::array<unsigned int, 4> lims = {groupLimitMatrix[4*index],
                                        groupLimitMatrix[4*index+1],
                                        groupLimitMatrix[4*index+2],
                                        groupLimitMatrix[4*index+3]};

    QVector<QString> strVec;

    if (lims[0]<countL)
        strVec.push_back(QFleet_BGT(bgt::PF).toLongStringBase());
    if (lims[1]<countM)
        strVec.push_back(QFleet_BGT(bgt::LN).toLongStringBase());
    if (lims[2]<countH)
        strVec.push_back(QFleet_BGT(bgt::VG).toLongStringBase());
    if (lims[3]<countSH)
        strVec.push_back(QFleet_BGT(bgt::FL).toLongStringBase());

    QString output="";

    for (auto& str : strVec)
    {
        output.append(str);
        if (str != strVec.back())
            output.append(",");
    }

    return output;
}

bool QFLW_Battlegroup::checkGroupLimits() const
{
    unsigned int index = type.convertToIndex();

    std::array<unsigned int, 4> lims = {groupLimitMatrix[4*index],
                                        groupLimitMatrix[4*index+1],
                                        groupLimitMatrix[4*index+2],
                                        groupLimitMatrix[4*index+3]};

    if (lims[0]<countL)
        return false;
    if (lims[1]<countM)
        return false;
    if (lims[2]<countH)
        return false;
    if (lims[3]<countSH)
        return false;

    return true;
}

void QFLW_Battlegroup::dragEnterEvent(QDragEnterEvent * event)
{
    QFLW_Group * srcPtr = (QFLW_Group *) event->source();
    // do I need to put anything here?
    if (event->mimeData()->hasFormat(QFLW_Group::dropGroupText) &&
        srcPtr->getcardWidgetPtr() != this)
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void QFLW_Battlegroup::dropEvent(QDropEvent * event)
{
    if (event->mimeData()->hasFormat(QFLW_Group::dropGroupText))
    {
        QByteArray bytes = event->mimeData()->data(QFLW_Group::dropGroupText);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);

        QJsonObject jsonObj = jsonDoc.object();

        QFleet_Group droppedGroup(jsonObj);

        this->addGroupListPart(droppedGroup);

        updateCost();

        event->setDropAction(Qt::MoveAction);
    }
    else
    {
        event->setDropAction(Qt::IgnoreAction);
    }


    event->acceptProposedAction();
}

QFLW_Battlegroup::~QFLW_Battlegroup()
{
    delete ui;

    for (auto& group : groups)
    {
        delete group;
    }
}

void QFLW_Battlegroup::refreshCostLabels()
{
    ui->pointsLabel->setText(QString::number(cost.points));
    ui->srLabel->setText(QString::number(cost.SR));
}

void QFLW_Battlegroup::updateCost(bool bubbleUp)
{
    cost.zero();

    for (auto groupPtr : groups)
    {
        cost + groupPtr->getCost();
    }

    updateGroupCounts();

    updateWarningLabels();

    refreshCostLabels();    

    if (bubbleUp)
    {
        QFLW_List * list = (QFLW_List *) this->parent();
        list->updateCost();
    }
}

QFleet_Cost QFLW_Battlegroup::getCost() const
{
    return cost;
}

// the idea here is that we remove the widgetPtr from the group then let it delelete itself, which will close it.
// sure hope this works
void QFLW_Battlegroup::removeGroup(QFLW_Group * groupPtr)
{
    auto index = 0;

    for (auto group : groups)
    {
        if (group.data() == groupPtr)
        {
            groups.remove(index);
            break;
        }

        index++;
    }

    updateCost();
}

void QFLW_Battlegroup::on_addGroupButton_clicked()
{
    emit querySelectedShip(this);
}

QFleet_Battlegroup QFLW_Battlegroup::createListPart() const
{
    QFleet_Battlegroup battleGroup(ui->nameEdit->text(), this->getType());

    for (auto group : groups)
        battleGroup.addGroup(group->createListPart());

    battleGroup.updateCost();


    return battleGroup;
}

void QFLW_Battlegroup::recieveSelectedShip(const QFleet_Ship_Fleet& ship)
{

    QPointer<QFLW_Group> newGroup = new QFLW_Group(this, ship);

    groups.push_back(newGroup); 

    ui->groupLayout->addWidget(newGroup.data());

    updateCost();

}

void QFLW_Battlegroup::incrementTypeCounters(const QFleet_Tonnage shipTonnage)
{
    QFleet_BGT shipType = shipTonnage.convertToBGT();

 switch(shipType.getVal())
    {
    case bgt::PF:

        countL++;
        break;

    case bgt::LN:

        countM++;
        break;

    case bgt::VG:

        countH++;
        break;

    case bgt::FL:

        countSH++;
        break;
    }
}

bool QFLW_Battlegroup::checkMandatory() const
{

    unsigned int index = type.convertToIndex();

    std::array<unsigned int, 4> actual{countL, countM, countH, countSH};

    if (actual[index]>0)
        return true;
    else
        return false;

}

QFleet_BGT QFLW_Battlegroup::getType() const
{
    return type;
}

// creates a group list part from a widget
void QFLW_Battlegroup::addGroupListPart(const QFleet_Group& group)
{
    QPointer<QFLW_Group> newGroup = new QFLW_Group(this, &group);

    groups.push_back(newGroup);

    ui->groupLayout->addWidget(newGroup.data());
}

void QFLW_Battlegroup::on_deleteCardButton_clicked()
{
    this->close();

    flagRemoval(this);
}

void QFLW_Battlegroup::flagRemoval(QFLW_Battlegroup * thisPtr)
{
    QFLW_List * list = (QFLW_List *) this->parent();

    list->removeCard(thisPtr);

}


void QFLW_Battlegroup::on_duplicateButton_clicked()
{
    auto listpart = this->createListPart();

    listpart.purgeAdmiral();

    emit signalDuplicate(listpart);


}




void QFLW_Battlegroup::on_trimGroupsButton_clicked()
{
    QVector<QFLW_Group *> tbd;

    if (groups.size() > 3)
    {
        for (auto itr = groups.begin() + 3; itr != groups.end(); itr++)
        {
            tbd.push_back(itr->data());
        }
    }

    for (auto ptr : tbd)
    {
        delete ptr;
    }

    groups.resize(3);

    updateCost();
}

