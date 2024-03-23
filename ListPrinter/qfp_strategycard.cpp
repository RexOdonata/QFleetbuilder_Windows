#include "qfp_strategycard.h"
#include "./ui_qfp_strategycard.h"

#include <QPalette>

#define NUM 0
#define NAME 1
#define ADMIRAL 2

QFP_StrategyCard::QFP_StrategyCard(QWidget *parent,std::optional<QFleet_Battlegroup> battlegroup)
    : QDialog(parent)
    , ui(new Ui::QFP_StrategyCard)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

    labels[NUM] = ui->g1NumLabel;
    labels[NAME] = ui->g1NameLabel;
    labels[ADMIRAL] = ui->g1AdmiralLabel;

    labels[NUM +3] = ui->g2NumLabel;
    labels[NAME +3] = ui->g2NameLabel;
    labels[ADMIRAL +3] = ui->g2AdmiralLabel;

    labels[NUM + 6] = ui->g3NumLabel;
    labels[NAME +6] = ui->g3NameLabel;
    labels[ADMIRAL +6] = ui->g3AdmiralLabel;

    auto index = 0;

    for (auto& group : battlegroup->getGroups())
    {
        setRow(group, index);
        index++;
    }

    for (; index < 3; index++)
    {
        setEmptyRow(index);
    }

    ui->srLabel->setText(QString::number(battlegroup->getCost().SR));

    ui->nameLabel->setText(battlegroup->getName());

    QPalette p;
    p.setColor(QPalette::Window, Qt::white);
    p.setColor(QPalette::WindowText, Qt::black);

    this->setAutoFillBackground(true);
    this->setPalette(p);
}

QFP_StrategyCard::~QFP_StrategyCard()
{
    delete ui;
}

std::array<QLabel*, 3> QFP_StrategyCard::getPointers(unsigned int i)
{
    std::array<QLabel*, 3> newArr = {labels[3*i + NUM],labels[3*i + NAME],labels[3*i + ADMIRAL]};
    return newArr;
}


void QFP_StrategyCard::setRow(QFleet_Group group, unsigned int row)
{
    auto widgetPtrs = getPointers(row);

    QString numStr="";

    if (group.getNumber() > 1)
    {
        numStr.append(QString::number(group.getNumber()));
        numStr.append("x");
    }
    else
        numStr = "1";


    widgetPtrs[NUM]->setText(numStr);

    widgetPtrs[NAME]->setText(group.getShip().name);

    QString admStr = "";

    if (group.getAdmiral())
    {
        admStr.append("Lvl");
        admStr.append(QString::number(group.getAdmiral()));
    }

    widgetPtrs[ADMIRAL]->setText(admStr);
}

void QFP_StrategyCard::setEmptyRow(unsigned int row)
{
    labels[NUM + row * 3]->clear();
    labels[NAME + row * 3]->clear();
    labels[ADMIRAL + row * 3]->clear();
}

QPixmap QFP_StrategyCard::getImage()
{
    auto pixmap = this->grab(this->rect() = QRect(QPoint(0, 0), QSize(-1, -1)));

    return pixmap;
}
