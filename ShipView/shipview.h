#ifndef SHIPVIEW_H
#define SHIPVIEW_H

#include <QWidget>
#include "../Components/qfleet_ship_fleet.h"
#include <QStandardItemModel>


namespace Ui {
class shipView;
}

class shipView : public QWidget
{
    Q_OBJECT

public:
    explicit shipView(QWidget *parent = nullptr);
    ~shipView();

    void loadShip(const QFleet_Ship_Fleet&); // ideally this would be const, but getting weird linker error

private:
    Ui::shipView *ui;
};

#endif // SHIPVIEW_H
