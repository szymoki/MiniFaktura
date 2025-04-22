#ifndef CONTRACTORLISTVIEW_H
#define CONTRACTORLISTVIEW_H

#include <QDialog>
#include <QStandardItemModel>
#include "contractorrepository.h"

/**
 * @file contractorlistview.h
 * @brief Definition of the ContractorListView class
 */

namespace Ui {
class ContractorListView;
}

/**
 * @brief The ContractorListView class represents a dialog for managing contractors
 */
class ContractorListView : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the ContractorListView class
     * @param contractorRepo A pointer to the ContractorRepository
     * @param parent The parent widget (default is nullptr)
     */
    explicit ContractorListView(ContractorRepository* contractorRepo, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the ContractorListView class
     */
    ~ContractorListView();

private slots:
    /**
     * @brief Slot triggered when the push button is clicked
     */
    void on_pushButton_clicked();

private:
    Ui::ContractorListView *ui; /**< The UI object for the ContractorListView */
    QStandardItemModel* itemModel = nullptr; /**< The item model for the table */
    ContractorRepository* contractorRepository; /**< Pointer to the ContractorRepository */

    /**
     * @brief Load contractors to the table
     */
    void loadContractorsToTable();

    /**
     * @brief Handle the context menu for the invoice table
     * @param pos The position of the context menu
     */
    void onInvoiceTableContextMenu(const QPoint& pos);

    /**
     * @brief Delete a contractor by ID
     * @param contractorId The ID of the contractor to delete
     */
    void deleteContractor(int contractorId);
};

#endif // CONTRACTORLISTVIEW_H

