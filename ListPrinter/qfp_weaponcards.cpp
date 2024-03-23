#include "qfp_weaponcards.h"
#include "ui_qfp_weaponcards.h"

QFP_WeaponCards::QFP_WeaponCards(QWidget *parent, std::optional<QFleet_Ship_Fleet> ship) :
    QDialog(parent),
    ui(new Ui::QFP_WeaponCards)
{
    ui->setupUi(this);



    QPalette p;
    p.setColor(QPalette::Window, Qt::white);
    p.setColor(QPalette::WindowText, Qt::black);

    this->setAutoFillBackground(true);
    this->setPalette(p);

    QString labelStr = QString("%1 weapons").arg(ship.value().name);

    ui->nameLabel->setText(labelStr);

    auto weps = ship->weapons;

    for (int row=0; row < weps.size(); row++)
    {
        auto lRow = row+1;

        QLabel * nameLabel = new QLabel(this);
        if (row % 2 == 1)
            nameLabel->setStyleSheet("color: black; background-color: Gainsboro");
        nameLabel->setText(weps.at(row).getName());
        ui->weaponLayout->addWidget(nameLabel, lRow, 0);
        labelVec.push_back(nameLabel);


        QLabel * lockLabel = new QLabel(this);
        if (row % 2 == 1)
            lockLabel->setStyleSheet("color: black; background-color: Gainsboro");
        lockLabel->setText(weps.at(row).lock.toString());
        lockLabel->setAlignment(Qt::AlignHCenter);
        ui->weaponLayout->addWidget(lockLabel, lRow, 1);
        labelVec.push_back(lockLabel);

        QLabel * attackLabel = new QLabel(this);
        if (row % 2 == 1)
            attackLabel->setStyleSheet("color: black; background-color: Gainsboro");
        attackLabel->setText(weps.at(row).attacks);
        attackLabel->setAlignment(Qt::AlignHCenter);
        ui->weaponLayout->addWidget(attackLabel, lRow, 2);
        labelVec.push_back(attackLabel);

        QLabel * damageLabel = new QLabel(this);
        if (row % 2 == 1)
            damageLabel->setStyleSheet("color: black; background-color: Gainsboro");
        damageLabel->setText(weps.at(row).damage);
        damageLabel->setAlignment(Qt::AlignHCenter);
        ui->weaponLayout->addWidget(damageLabel, lRow, 3);
        labelVec.push_back(damageLabel);

        QLabel * arcLabel = new QLabel(this);
        if (row % 2 == 1)
            arcLabel->setStyleSheet("color: black; background-color: Gainsboro");
        arcLabel->setText(weps.at(row).facing.toString());
        arcLabel->setAlignment(Qt::AlignHCenter);
        ui->weaponLayout->addWidget(arcLabel, lRow, 4);
        labelVec.push_back(arcLabel);

        QLabel * specialLabel = new QLabel(this);
        if (row % 2 == 1)
            specialLabel->setStyleSheet("color: black; background-color: Gainsboro");
        specialLabel->setText(weps.at(row).getSpecialString());
        specialLabel->setAlignment(Qt::AlignHCenter);
        ui->weaponLayout->addWidget(specialLabel, lRow, 5);
        labelVec.push_back(specialLabel);

    }

    QFont font("Sans Serif",12,1,false);

    for (auto label : labelVec)
        label->setFont(font);
}

QFP_WeaponCards::~QFP_WeaponCards()
{
    delete ui;

    for (auto ptr: labelVec)
        delete ptr;
}

QPixmap QFP_WeaponCards::getImage()
{
    auto pixmap = this->grab(this->rect() = QRect(QPoint(0, 0), QSize(-1, -1)));

    return pixmap;
}
