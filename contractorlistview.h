#ifndef CONTRACTORLISTVIEW_H
#define CONTRACTORLISTVIEW_H

#include <QDialog>
#include <QStandardItemModel>
#include "contractorrepository.h"
namespace Ui {
class ContractorListView;
}

class ContractorListView : public QDialog
{
    Q_OBJECT

public:
    explicit ContractorListView(ContractorRepository* contractorRepo, QWidget *parent = nullptr);
    ~ContractorListView();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ContractorListView *ui;
    QStandardItemModel* itemModel=nullptr;
    ContractorRepository* contractorRepository;
    void loadContractorsToTable();
};

#endif // CONTRACTORLISTVIEW_H
