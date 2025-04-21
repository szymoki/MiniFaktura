#ifndef INVOICEFORM_H
#define INVOICEFORM_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QDebug>
#include <QStandardItemModel>
#include <QMessageBox>
#include "invoicerepository.h"
#include "contractorrepository.h"
#include <QDialog>

namespace Ui {
class InvoiceForm;
}

class InvoiceForm : public QDialog
{
    Q_OBJECT

public:
    explicit InvoiceForm(ContractorRepository* contractorRepo,InvoiceRepository* invoiceRepo,QWidget *parent = nullptr);
    ~InvoiceForm();

private slots:
    void on_addButton_clicked();
private:
    QStandardItemModel* itemModel;
    Ui::InvoiceForm *ui;
    ContractorRepository* contractorRepository;
    InvoiceRepository* invoiceRepository;
    void loadContractorsToComboBox();
};

#endif // INVOICEFORM_H
