#ifndef LIMITWIDGET_H
#define LIMITWIDGET_H

#include <QWidget>

namespace Ui {
class limitWidget;
}

class limitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit limitWidget(QWidget *parent = nullptr);
    ~limitWidget();

    void setLimit(unsigned int);

    void setValue(unsigned int);

    bool isValid() const;

private:
    Ui::limitWidget *ui;

    unsigned int limit;
    unsigned int value;

};

#endif // LIMITWIDGET_H
