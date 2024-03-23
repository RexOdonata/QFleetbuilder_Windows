#ifndef QFP_PROFILECARD_H
#define QFP_PROFILECARD_H

#include <QDialog>
#include <optional>
#include <QLabel>
#include "../Components/qfleet_ship_fleet.h"

namespace Ui {
class QFP_ProfileCard;
}

class QFP_ProfileCard : public QDialog
{
    Q_OBJECT

public:
    explicit QFP_ProfileCard(QWidget *parent = nullptr, std::optional<QFleet_Ship_Fleet> ship = {});
    ~QFP_ProfileCard();

    QPixmap getImage();

private:
    Ui::QFP_ProfileCard *ui;

    QVector<QLabel *> launchLabels;
};

#endif // QFP_PROFILECARD_H
