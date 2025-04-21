#ifndef CONTRACTORFORM_H
#define CONTRACTORFORM_H

#include <QDialog>
#include "contractorrepository.h"
namespace Ui {
class ContractorForm;
}

class ContractorForm : public QDialog
{
    Q_OBJECT

public:
    explicit ContractorForm(ContractorRepository* contractorRepo, QWidget *parent = nullptr);
    ~ContractorForm();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ContractorForm *ui;
    ContractorRepository* contractorRepository;

};

#endif // CONTRACTORFORM_H
