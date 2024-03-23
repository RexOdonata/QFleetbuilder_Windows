#ifndef OPTSELECT_H
#define OPTSELECT_H

#include <QDialog>

#include "../Components/qfleet_ship_shipyard.h"


#include "../common/dvs_widget.h"

namespace Ui {
class optSelect;
}

class optSelect : public QDialog
{
    Q_OBJECT

public:
    explicit optSelect(QWidget *parent = nullptr, const QFleet_Ship_Shipyard * refShip = NULL , QVector<QFleet_Option> * setOptionList = NULL);
    ~optSelect();

signals:

    void signalCustomName(QString);

private slots:
    void on_addOptionButton_clicked();

    void on_removeOptionButton_clicked();

    void on_saveOptionsButton_clicked();

private:
    Ui::optSelect *ui;

    QStringListModel listModel;

    // I don't know if this is the best way to do this, it does mean iterating across a map quite a bit
    // for now it works, maybe a more clever design can be implemented later
    QMap<QString, unsigned int> selectedOptionsNum;

    QVector<QFleet_Option> * optionList = NULL;

    // stores all options passed in from the source ship, used to get the options from the string that comes back from the table select
    QMap<QString, QFleet_Option> optMap;

    bool checkAdd(const QFleet_Option&, QString&);

    void updateCounts();


    // LIST VIEW FXS

    // add option to list
    void selectOption(const QFleet_Option&);

    // expand
    void expandSelectedOptions(QVector<QFleet_Option>&);

    // regenerate the stringlist for the selection list view
    void refreshSelectionView();

    unsigned int getSelectionCount();

    std::optional<QString> getSelection();

    // VARS

    unsigned int broadsideLimit;
    unsigned int broadsideCount;
    unsigned int minOptions;
    unsigned int maxOptions;

};

#endif // OPTSELECT_H
