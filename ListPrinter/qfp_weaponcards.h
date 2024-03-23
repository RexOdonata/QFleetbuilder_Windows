#ifndef QFP_WEAPONCARDS_H
#define QFP_WEAPONCARDS_H

#include <QDialog>
#include <optional>
#include "../Components/qfleet_ship_fleet.h"

#include <QLabel>

namespace Ui {
class QFP_WeaponCards;
}

class QFP_WeaponCards : public QDialog
{
    Q_OBJECT

public:
    explicit QFP_WeaponCards(QWidget *parent = nullptr, std::optional<QFleet_Ship_Fleet> = {});
    ~QFP_WeaponCards();

    QPixmap getImage();

private:
    Ui::QFP_WeaponCards *ui;

    QVector<QLabel *> labelVec;
};

#endif // QFP_WEAPONCARDS_H
