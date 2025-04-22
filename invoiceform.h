/**
 * @file invoiceform.h
 * @brief Definition of the InvoiceForm class
 */
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







namespace Ui {
class InvoiceForm;
}

/**
 * @brief The InvoiceForm class represents a dialog for managing invoices
 */
class InvoiceForm : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the InvoiceForm class
     * @param contractorRepo A pointer to the ContractorRepository
     * @param invoiceRepo A pointer to the InvoiceRepository
     * @param parent The parent widget (default is nullptr)
     */
    explicit InvoiceForm(ContractorRepository* contractorRepo, InvoiceRepository* invoiceRepo, QWidget *parent = nullptr);
    
    /**
     * @brief Destructor for the InvoiceForm class
     */
    ~InvoiceForm();

private slots:
    /**
     * @brief Slot triggered when the add button is clicked
     */
    void on_addButton_clicked();
    
    /**
     * @brief Slot triggered when the button box is accepted
     */
    void on_buttonBox_accepted();

private:
    QStandardItemModel* itemModel;
    Ui::InvoiceForm *ui;
    ContractorRepository* contractorRepository;
    InvoiceRepository* invoiceRepository;
    /**
     * @brief Load contractors to the combo box
     */
    void loadContractorsToComboBox();
};

#endif // INVOICEFORM_H

