#include "dvs_widget.h"
#include <QLineEdit>
#include <QLabel>
#include "ui_dvs_widget.h"


dvs_WidgetBase::dvs_WidgetBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dvs_WidgetBase)
{
    ui->setupUi(this);

    // model-list of data IDs
    listModel = new QStandardItemModel(this);

    ui->treeView->setModel(listModel);

}

void dvs_WidgetBase::setMultiSelect()
{
    ui->treeView->setSelectionMode(QAbstractItemView::MultiSelection);
}

dvs_WidgetBase::~dvs_WidgetBase()
{
    if (completer)
        delete completer;

    if (searchLinePtr)
        delete searchLinePtr;

    if (factionFilter)
        delete factionFilter;

    delete listModel;

    delete ui;
}

void dvs_WidgetBase::setLabel(const QString in)
{
    ui->label->setText(in);
}

std::optional<QString> dvs_WidgetBase::hasSearchResult() const
{
    return {};
}


QString dvs_WidgetBase::getSelectedStr() const
{
    auto sr = this->hasSearchResult();
    if (sr)
    {
        return *sr;
    }
    else if (ui->treeView->selectionModel()->selectedIndexes().size() > 0)
    {
        return ui->treeView->selectionModel()->selectedIndexes().front().data().toString();
    }

    return "";
}

QVector<QString> dvs_WidgetBase::getMultiSelectStr() const
{
    if (ui->treeView->selectionModel()->selectedIndexes().size() > 0)
    {
        auto selectedIndices = ui->treeView->selectionModel()->selectedIndexes();

        QVector<QString> strs;
        for (auto index : selectedIndices)

            strs.push_back(index.data().toString());

        return strs;
    }
    else
        return QVector<QString>();
}

void dvs_WidgetBase::addSearchWidget(QWidget * widget)
{
    ui->searchBoxLayout->addWidget(widget);
}

void dvs_WidgetBase::addFilterWidget(QWidget * widget)
{
    ui->factionFilterLayout->addWidget(widget);
}

