/**
 * @file contractorform.h
 * @brief Definition of the ContractorForm class
 */

#ifndef CONTRACTORFORM_H
#define CONTRACTORFORM_H

#include <QDialog>
#include "contractorrepository.h"
namespace Ui {
class ContractorForm;
}

/**
 * @brief The ContractorForm class represents a dialog for managing contractors
 */
class ContractorForm : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for the ContractorForm class
     * @param contractorRepo A pointer to the ContractorRepository
     * @param parent The parent widget (default is nullptr)
     */
    explicit ContractorForm(ContractorRepository* contractorRepo, QWidget *parent = nullptr);

    /**
     * @brief Destructor for the ContractorForm class
     */
    ~ContractorForm();

private slots:
    /**
     * @brief Slot triggered when the button box is accepted
     */
    void on_buttonBox_accepted();

private:
    Ui::ContractorForm *ui; /**< The UI object for the ContractorForm */
    ContractorRepository* contractorRepository; /**< Pointer to the ContractorRepository */
};

#endif // CONTRACTORFORM_H

