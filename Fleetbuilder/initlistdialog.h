#ifndef INITLISTDIALOG_H
#define INITLISTDIALOG_H

#include <QDialog>
#include "../Components/qfleet_faction.h"

struct listInit
{
    faction listFaction;
    unsigned int listPoints;
};

namespace Ui {
class initListDialog;
}

class initListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit initListDialog(QWidget *parent = nullptr, listInit * data = NULL);
    ~initListDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::initListDialog *ui;

    listInit * dataPtr = NULL;
};

#endif // INITLISTDIALOG_H
