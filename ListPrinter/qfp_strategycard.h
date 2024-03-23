#ifndef QFP_STRATEGYCARD_H
#define QFP_STRATEGYCARD_H

#include <QDialog>
#include <QLabel>
#include <QPixmap>

#include "../ListParts/qfleet_battlegroup.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QFP_StrategyCard; }
QT_END_NAMESPACE

class QFP_StrategyCard : public QDialog
{
    Q_OBJECT

public:
    QFP_StrategyCard(QWidget *parent = nullptr, std::optional<QFleet_Battlegroup> = {});
    ~QFP_StrategyCard();

    QPixmap getImage();

private:
    Ui::QFP_StrategyCard *ui;

    void setRow(QFleet_Group, unsigned int);

    std::array<QLabel*, 9> labels;

    std::array<QLabel*, 3> getPointers(unsigned int);

    void setEmptyRow(unsigned int);



};
#endif // QFP_STRATEGYCARD_H
