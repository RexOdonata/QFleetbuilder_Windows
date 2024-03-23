#include "qfp_profilecard.h"
#include "ui_qfp_profilecard.h"

QFP_ProfileCard::QFP_ProfileCard(QWidget *parent, std::optional<QFleet_Ship_Fleet> shipOpt) :
    QDialog(parent),
    ui(new Ui::QFP_ProfileCard)
{
    ui->setupUi(this);

    auto ship = *shipOpt;

    ui->nameLabel->setText(ship.name);

    ui->scanLabel->setText(QString::number(ship.scan));

    ui->sigLabel->setText(ship.getSigString());

    ui->thrustLabel->setText(QString::number(ship.thrust));

    ui->armorLabel->setText(ship.getArmorString());

    ui->pdLabel->setText(QString::number(ship.PD));

    ui->hullLabel->setText(QString::number(ship.hull));

    ui->groupLabel->setText(ship.getGroupString());

    ui->tonnageLabel->setText(ship.tonnage.toString());

    ui->specialLabel->setText(ship.getSpecialString());

    ui->pointsLabel->setText( QString::number(ship.points));

    auto lps = ship.launch;

    if (lps.size() == 0)
    {
        ui->launchLabel->setVisible(false);
        ui->countLaunchLabel->setVisible(false);
        ui->launchLimitedLabel->setVisible(false);
    }
    else
    for (int row=0; row < lps.size(); row++)
    {
        auto lRow = row + 1;

        QLabel * nameLabel = new QLabel(this);
        if (row % 2 == 1)
            nameLabel->setStyleSheet("color: black; background-color: Gainsboro");
        nameLabel->setText(lps.at(row).getDisplayName());
        nameLabel->setAlignment(Qt::AlignHCenter);
        ui->launchLayout->addWidget(nameLabel, lRow, 0);
        launchLabels.push_back(nameLabel);

        QLabel * numLabel = new QLabel(this);
        if (row % 2 == 1)
            numLabel->setStyleSheet("color: black; background-color: Gainsboro");
        numLabel->setText(QString::number(lps.at(row).getCount()));
        numLabel->setAlignment(Qt::AlignHCenter);
        ui->launchLayout->addWidget(numLabel, lRow, 1);
        launchLabels.push_back(numLabel);

        QLabel * limLabel = new QLabel(this);
        if (row % 2 == 1)
            limLabel->setStyleSheet("color: black; background-color: Gainsboro");
        limLabel->setText(lps.at(row).getLimString());
        limLabel->setAlignment(Qt::AlignHCenter);
        ui->launchLayout->addWidget(limLabel, lRow, 2);
        launchLabels.push_back(limLabel);

    }

    QPalette p;
    p.setColor(QPalette::Window, Qt::white);
    p.setColor(QPalette::WindowText, Qt::black);

    this->setAutoFillBackground(true);
    this->setPalette(p);

}

QPixmap QFP_ProfileCard::getImage()
{
    auto pixmap = this->grab(this->rect() = QRect(QPoint(0, 0), QSize(-1, -1)));

    return pixmap;
}

QFP_ProfileCard::~QFP_ProfileCard()
{
    delete ui;

    for (auto ptr : launchLabels)
        delete ptr;
}
